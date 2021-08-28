#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include <unistd.h>

#define MILISSECOND_UNITY 1/1000

clock_t start, end;

struct Pipe{
    bool isOk_sensor400;
    bool isOk_sensor800;
    bool isOk_sensor1200;
};

struct Pump {
    int id;
    bool is_operating;
    bool operational_problem;
    struct Pipe oil;
    struct Pipe gas;

};

bool rand_bool() {
    time_t t;
    srand((unsigned) time(&t));
    return rand() & 1;
}

double calculate_time() {
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

//os sensore são inicializados como funcionais
struct Pump new_pump(int id){
    struct Pump pump;

    pump.id = id;
    pump.is_operating = true;
    pump.operational_problem = false;

    pump.gas.isOk_sensor400 = true;
    pump.gas.isOk_sensor800 = true;
    pump.gas.isOk_sensor1200 = true;

    pump.oil.isOk_sensor400 = true;
    pump.oil.isOk_sensor800 = true;
    pump.oil.isOk_sensor1200 = true;

    return pump;

}

double verify_400m_pipe(bool* pipe400) {
    start = clock();
    // Delay da amostra
    sleep(1*MILISSECOND_UNITY);

    // Gera um erro randomico
    bool error = rand_bool();

    // Simulação da propagação da amostragem
    if(error) {
        for (int i = 0; i < 4; ++i) {
            sleep(5*MILISSECOND_UNITY);
        }
    }

    // Atualiza se existe erro na struct
    *pipe400 = error;

    end = clock();

    // Retorna o tempo de execução
    return calculate_time();
}





//void insere_falha(struct Pump pumps[PUMP_NUM]){
//    time_t t;
//    srand((unsigned) time(&t)); //inicializa o gerador de números randomicos para as pumps
//    switch(rand() % 4) { //switch randomico entre as 3 opções de erro
//        case 0:
//            pumps[rand() % PUMP_NUM].sensor0 = true;
//        case 1:
//            pumps[rand() % PUMP_NUM].sensor400 = 1;
//        case 2:
//            pumps[rand() % PUMP_NUM].sensor800 = 1;
//        case 3:
//            pumps[rand() % PUMP_NUM].sensor1200 = 1;
//    }
//}

//void localiza_falha(struct Pump pumps[PUMP_NUM]){
//    for(int i=0; i<PUMP_NUM; i++){
//        if(pumps[i].sensor0==true){
//            printf("Falha detectada na bomba: %d\n", i);
//        }
//        else if(pumps[i].sensor400 == 1){
//            printf("Falha detectada no sensor de 400m da bomba: %d\n", i);
//        }
//        else if(pumps[i].sensor800 == 1){
//            printf("Falha detectada no sensor de 800m da bomba: %d\n", i);
//        }
//        else if(pumps[i].sensor1200 == 1){
//            printf("Falha detectada no sensor de 1200m da bomba: %d\n", i);
//        }
//    }
//}

void display() {}

void menu() {

}

int main() {
    struct Pump pump1 = new_pump(1);
    struct Pump pump2 = new_pump(2);
    struct Pump pump3 = new_pump(3);

    start = clock();

    sleep(500*MILISSECOND_UNITY);

    end = clock();

    double val = calculate_time(start, end);

    printf("%f", val);
    printf("\n");
    printf("%d", 500 * 1000);
//    printf("%f", val+MILISSECOND);


//    initialize_pumps(pumps);
//    insere_falha(pumps);
//    localiza_falha(pumps);
    return 0;
}
