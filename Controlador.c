
//Amanda de souza martins 22.120.0041
//Pedro henrique braga 22.120.064-5
//Gustavo velecico 22.120.044-7








#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <webots/position_sensor.h>
#include <webots/supervisor.h>



#define TIME_STEP 256
#define QtddSensoresProx 8
#define QtddLeds 10
#define TOLERANCIA 0.0050

int main(int argc, char **argv) {
    int i = 0;
    char texto[256];
    double LeituraSensorProx[QtddSensoresProx];
    double AceleradorDireito = 1.0; 
    double AceleradorEsquerdo = 1.0;

    // Inicialização do Webots
    wb_robot_init();

    // Configuração dos motores
    WbDeviceTag MotorEsquerdo, MotorDireito;
    MotorEsquerdo = wb_robot_get_device("left wheel motor");
    MotorDireito = wb_robot_get_device("right wheel motor");
    wb_motor_set_position(MotorEsquerdo, INFINITY);
    wb_motor_set_position(MotorDireito, INFINITY);
    wb_motor_set_velocity(MotorEsquerdo, 0);
    wb_motor_set_velocity(MotorDireito, 0);

    // Configuração dos sensores de proximidade
    WbDeviceTag SensorProx[QtddSensoresProx];
    
    //double leiturasAnteriores[QtddSensoresProx] = {0};

    SensorProx[0] = wb_robot_get_device("ps0");
    SensorProx[1] = wb_robot_get_device("ps1");
    SensorProx[2] = wb_robot_get_device("ps2");
    SensorProx[3] = wb_robot_get_device("ps3");
    SensorProx[4] = wb_robot_get_device("ps4");
    SensorProx[5] = wb_robot_get_device("ps5");
    SensorProx[6] = wb_robot_get_device("ps6");
    SensorProx[7] = wb_robot_get_device("ps7");

    wb_distance_sensor_enable(SensorProx[0], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[1], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[2], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[3], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[4], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[5], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[6], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[7], TIME_STEP);

    // Configuração dos LEDs
    WbDeviceTag Leds[QtddLeds];
    Leds[0] = wb_robot_get_device("led0");
    Leds[1] = wb_robot_get_device("led1"); // Novos LEDS
    Leds[2] = wb_robot_get_device("led2"); // Novo LED 2
    Leds[3] = wb_robot_get_device("led3"); 
    Leds[4] = wb_robot_get_device("led4"); 
    Leds[5] = wb_robot_get_device("led5"); 
    Leds[6] = wb_robot_get_device("led6"); 
    Leds[7] = wb_robot_get_device("led7"); 
    Leds[8] = wb_robot_get_device("led8"); 

   
    
    
    // Configuraçao dos sensores das rodas.
    /*
    WbDeviceTag SensorRodaDireita;
    WbDeviceTag SensorRodaEsquerda;
    SensorRodaDireita = wb_robot_get_device("right wheel sensor");
    SensorRodaEsquerda = wb_robot_get_device("left wheel sensor");
    wb_position_sensor_enable(SensorRodaDireita, TIME_STEP);
    wb_position_sensor_enable(SensorRodaEsquerda, TIME_STEP);
    */

    //configurando nodes de supervisão
    WbNodeRef supervisor_node = wb_supervisor_node_get_from_def("caixa");
    const double *posicao_anterior =  wb_supervisor_node_get_position(/*WbNodeRef*/supervisor_node);
    if (supervisor_node != NULL) {
    const double *posicao = wb_supervisor_node_get_position(/*WbNodeRef*/supervisor_node);
    printf("Posição: %f %f %f\n", posicao[0], posicao[1], posicao[2]);
    } else {
    printf("Nó do Supervisor não encontrado.\n");
    }

    // Loop principal
    while (wb_robot_step(TIME_STEP) != -1) {
        for (i = 0; i < 256; i++) texto[i] = 0;
        WbNodeRef supervisor_node = wb_supervisor_node_get_from_def("caixa");
        /*double posicaoDireita = wb_position_sensor_get_value(SensorRodaDireita);
        double posicaoEsquerda = wb_position_sensor_get_value(SensorRodaEsquerda);
        
        printf(" = %f\n",posicaoDireita);
        printf(" = %f\n",posicaoEsquerda);
        */
        int objetoBorda = 0;
        int objetoMovimento = 0;
        
         const double *posicao = wb_supervisor_node_get_position(/*WbNodeRef*/supervisor_node);
         if (supervisor_node != NULL) {
         
         printf("Posição: %f %f %f\n", posicao[0], posicao[1], posicao[2]);
         } else {
         printf("Nó do Supervisor não encontrado.\n");
         }
         
          if ( posicao_anterior[1] - posicao[1]  > TOLERANCIA /*|| posicao[1] - posicao_anterior[1] > TOLERANCIA /* || posicao[2] - posicao_anterior[2] > TOLERANCIA */) {
          // Houve mudança na posição
          // Faça algo...
          printf("Objeto leve indentificado.\n");
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);
          wb_led_set(Leds[4], 1);
          wb_led_set(Leds[5], 1);
          wb_led_set(Leds[6], 1);
          wb_led_set(Leds[7], 1);
          wb_led_set(Leds[8], 1);
          //printf("%d\n",objetoMovimento);
          AceleradorDireito = 0;
          AceleradorEsquerdo = 0;
          objetoMovimento = 1;
          
         }
        
        
        
        // Leitura dos sensores de proximidade
        for (i = 0; i < QtddSensoresProx; i++) {
            LeituraSensorProx[i] = wb_distance_sensor_get_value(SensorProx[i]) - 60;
            sprintf(texto,"%s|%d: %5.2f  ",texto,i,LeituraSensorProx[i]);
            // Verifica se houve uma mudança significativa na leitura do sensor
            if (LeituraSensorProx[i] > 1300) {
            printf("Sensor %d está em borda\n", i);
            objetoBorda = 1;
            printf("%d\n",objetoBorda);
            }
                
            /*else if (fabs(LeituraSensorProx[i] - leiturasAnteriores[i]) > 1050) {
                // O objeto associado ao sensor está se movendo
                printf("Objeto %d está em movimento\n", i);
                }
            */
            /*
            else if (LeituraSensorProx[i] > 800 && LeituraSensorProx[i] < 1000) {
                // O objeto associado ao sensor está se movendo
                objetoMovimento = 1;
                printf("Objeto %d está se movimentando\n", i);

                }
            // Armazena a leitura atual para a próxima iteração
            leiturasAnteriores[i] = LeituraSensorProx[i];
            sprintf(texto, "%s|%d: %5.2f  ", texto, i, LeituraSensorProx[i]);
            */
        }
        

        printf("%s\n", texto);
        wb_led_set(Leds[0], wb_led_get(Leds[0]) * -1);

        // Controle dos sensores das rodas
        int objetoDetectado = 0;
        for (i = 0; i < QtddSensoresProx; i++) {
            if (LeituraSensorProx[i] > 100) {
                objetoDetectado = 1;
                //break;
                //double posicaoDireitaN = wb_position_sensor_get_value(SensorRodaDireita);
                //double posicaoEsquerdaN = wb_position_sensor_get_value(SensorRodaEsquerda);
                //printf("Loop detectou objeto");
                //printf(" DN = %f\n",posicaoDireitaN);
                //printf(" EN = %f\n",posicaoEsquerdaN);
                //if(posicaoDireita != posicaoDireitaN && posicaoEsquerda != posicaoEsquerdaN){
                //}
                
            }
        }
         
        //MOVIMENTO DO ROBO CONDIÇÕES
        if (objetoDetectado == 1 && objetoMovimento == 0 ) {
            // Se um objeto foi detectado, pare os motores
            AceleradorDireito = -1.0;
            AceleradorEsquerdo = 0.4;
            printf("Objeto detectado\n");      
        } 
        else if(objetoBorda == 1 && objetoMovimento == 0){
                AceleradorDireito = -0.9;
                AceleradorEsquerdo = -0.9;
                printf("%d\n",objetoBorda);    
        }
        
        else if(objetoMovimento == 1){
                AceleradorDireito = 0;
                AceleradorEsquerdo = 0;
                break;
            
        }
        
        else if (objetoDetectado == 0 && objetoMovimento == 0) {
            // Caso contrário, mantenha os motores ligados
            AceleradorDireito = 0.9;
            AceleradorEsquerdo = 0.9;
        }
        
         



        wb_motor_set_velocity(MotorEsquerdo, 6.28 * AceleradorEsquerdo);
        wb_motor_set_velocity(MotorDireito, 6.28 * AceleradorDireito);
    }
    
    wb_motor_set_velocity(MotorEsquerdo, 6.28 * AceleradorEsquerdo * 0);
    wb_motor_set_velocity(MotorDireito, 6.28 * AceleradorDireito * 0);

    // Limpeza dos recursos do Webots
    wb_robot_cleanup();

    return 0;
}
