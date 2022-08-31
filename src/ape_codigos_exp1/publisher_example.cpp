void vTaskLocalControl(void *pvParameters){
    int i=0;
    CustomEventHandler* context = (CustomEventHandler*)pvParameters;
    cout<<("Task Local Control");
    while(1){
        if(context->isMQTTConnected()){
            string message("");
            if (gpio_get_level(GPIO_INPUT_IO_0) == 1){
                message += "{\
                    \"message\": \"Acionado\",\
                    \"sequence\": 1\
                }";
            }
            else{
                i++;
                if (i == 5){
                    i=0;
                    message += "{\
                        \"message\": \"Desligado\",\
                        \"sequence\": "+to_string(i)+"\
                    }";
                }
            }
            context->postData("lem/valve",message.c_str());
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};