import random

from paho.mqtt import client as mqtt_client


broker = 'mapl-iot.cloud.shiftr.io'
port = 1883
topicValveA = "lem/#"
client_id = f'python-mqtt-{random.randint(0, 100)}'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set('mapl-iot','NgJlVBYOkeNK2GIw')
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        if (msg.topic == 'lem/sensorB'):
            if (msg.payload.decode() == 'Desacionado'):
                client.publish('lem/valveA', "Acionado")
            if (msg.payload.decode() == 'Acionado'):
                client.publish('lem/valveA', "Desacionado")
        if (msg.topic == 'lem/sensorA'):
            if (msg.payload.decode() == 'Acionado'):
                client.publish('lem/valveB', "Acionado")
            if (msg.payload.decode() == 'Desacionado'):
                client.publish('lem/valveB', "Desacionado")
            


    client.subscribe(topicValveA)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()

