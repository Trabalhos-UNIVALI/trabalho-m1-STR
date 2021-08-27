#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define PUMP_NUM 3

// 0 para não tem problema
// 1 para problema no petróleo
// 2 para problema no gás
struct Pump {
    bool sensor0; // o sensor 0 é o sensor da própria pump
    int sensor400;
    int sensor800;
    int sensor1200;
};

//os sensore são inicializados sem problema, sendo os sensores int inicializados em 0 eo sensor bool inicializado em false
void initialize_pumps(struct Pump pumps[PUMP_NUM]){
    for(int i=0;i<PUMP_NUM; i++){
        pumps[i].sensor0=false;
        pumps[i].sensor400=0;
        pumps[i].sensor800=0;
        pumps[i].sensor1200=0;
    }
}

void insere_falha(struct Pump pumps[PUMP_NUM]){
    time_t t;
    srand((unsigned) time(&t)); //inicializa o gerador de números randomicos para as pumps
    switch(rand() % 4) { //switch randomico entre as 3 opções de erro
        case 0:
            pumps[rand() % PUMP_NUM].sensor0 = true;
        case 1:
            pumps[rand() % PUMP_NUM].sensor400 = 1;
        case 2:
            pumps[rand() % PUMP_NUM].sensor800 = 1;
        case 3:
            pumps[rand() % PUMP_NUM].sensor1200 = 1;
    }
}

void localiza_falha(struct Pump pumps[PUMP_NUM]){
    for(int i=0; i<PUMP_NUM; i++){
        if(pumps[i].sensor0==true){
            printf("Falha detectada na bomba: %d\n", i);
        }
        else if(pumps[i].sensor400 == 1){
            printf("Falha detectada no sensor de 400m da bomba: %d\n", i);
        }
        else if(pumps[i].sensor800 == 1){
            printf("Falha detectada no sensor de 800m da bomba: %d\n", i);
        }
        else if(pumps[i].sensor1200 == 1){
            printf("Falha detectada no sensor de 1200m da bomba: %d\n", i);
        }
    }
}

void display() {}

void menu() {

}

int main() {
    struct Pump pumps[PUMP_NUM];

    initialize_pumps(pumps);
    insere_falha(pumps);
    localiza_falha(pumps);
    return 0;
}
