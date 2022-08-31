void vTaskLocalControl(void *pvParameters){
    CustomEventHandler* context = (CustomEventHandler*)pvParameters;
    cout<<("Task Local Control");
    context->subscribeTo("lem/valveA",[](string pay){
        cout<<"Received: "<<pay<<endl;
        cout<<("Valvula Acionada no local control")<<endl;
    });
    while(1){
        if(context->isMQTTConnected()){
            cout<<"MQTT Connected"<<endl;
            context->subscribeTo("lem/valveA",[](string pay){
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
        if (gpio_get_level(GPIO_INPUT_IO_0) == 1){    
            cout<<"Auto"<<endl;
            context->postData("lem/sensorA","Acionado");
        }
        if (gpio_get_level(GPIO_INPUT_IO_1) == 1){    
            cout<<"Auto"<<endl;
            context->postData("lem/sensorA","Desacionado");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};  
