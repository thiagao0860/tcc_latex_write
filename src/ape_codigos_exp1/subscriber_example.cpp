void vTaskLocalControl(void *pvParameters){
    CustomEventHandler* context = (CustomEventHandler*)pvParameters;
    cout<<("Task Local Control");
    context->subscribeTo("lem/valve",[](string pay){
        cout<<"Received: "<<pay<<endl;
        cout<<("Valvula Acionada no local control")<<endl;
    });
    while(1){
        if(context->isMQTTConnected()){
            cout<<"MQTT Connected"<<endl;
            context->subscribeTo("lem/valve",[](string pay){
                cout<<"Received: "<<pay<<endl;
                cout<<("Valvula Acionada no local control")<<endl;
                if (pay == "Acionado"){
                    gpio_set_level(GPIO_OUTPUT_IO_0, 1);
                }
                if (pay == "Desacionado"){
                    gpio_set_level(GPIO_OUTPUT_IO_0, 0);
                }
            });
            break;
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    while(1){
        cout<<"Waiting Data..."<<endl;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};