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
    return rand() & 1;
}

double calculate_time() {
    return ((double) (end - start));
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

double verify_800m_pipe(bool* pipe800) {
    start = clock();
    // Delay da amostra
    sleep(1*MILISSECOND_UNITY);

    // Gera um erro randomico
    bool error = rand_bool();

    // Simulação da propagação da amostragem
    if(error) {
        for (int i = 0; i < 8; ++i) {
            sleep(5*MILISSECOND_UNITY);
        }
    }

    // Atualiza se existe erro na struct
    *pipe800 = error;

    end = clock();

    // Retorna o tempo de execução
    return calculate_time();
}

double verify_1200m_pipe(bool* pipe1200) {
    start = clock();
    // Delay da amostra
    sleep(1*MILISSECOND_UNITY);

    // Gera um erro randomico
    bool error = rand_bool();

    // Simulação da propagação da amostragem
    if(error) {
        for (int i = 0; i < 12; ++i) {
            sleep(5*MILISSECOND_UNITY);
        }
    }

    // Atualiza se existe erro na struct
    *pipe1200 = error;

    end = clock();

    // Retorna o tempo de execução
    return calculate_time();
}

bool verify_pump(struct Pump pump) {
    bool *refGas400 = &pump.gas.isOk_sensor400;
    double timeGas400 = verify_400m_pipe(refGas400);

    bool *refGas800 = &pump.gas.isOk_sensor800;
    double timeGas800 = verify_800m_pipe(refGas800);

    bool *refGas1200 = &pump.gas.isOk_sensor1200;
    double timeGas1200 = verify_1200m_pipe(refGas1200);

    bool *refOil400 = &pump.oil.isOk_sensor400;
    double timeOil400 = verify_400m_pipe(refOil400);

    bool *refOil800 = &pump.oil.isOk_sensor800;
    double timeOil800 = verify_800m_pipe(refOil800);

    bool *refOil1200 = &pump.oil.isOk_sensor1200;
    double timeOil1200 = verify_1200m_pipe(refOil1200);

    printf("GAS 400 - Time: %f --> Value: %d \n", timeGas400, pump.gas.isOk_sensor400);
    printf("GAS 800 - Time: %f --> Value: %d \n", timeGas800, pump.gas.isOk_sensor800);
    printf("GAS 1200 - Time: %f --> Value: %d \n", timeGas1200, pump.gas.isOk_sensor1200);

    printf("OIL 400 - Time: %f --> Value: %d \n", timeOil400, pump.oil.isOk_sensor400);
    printf("OIL 800 - Time: %f --> Value: %d \n", timeOil800, pump.oil.isOk_sensor800);
    printf("OIL 1200 - Time: %f --> Value: %d \n", timeOil1200, pump.oil.isOk_sensor1200);

    return true;
}

int main() {
    srand( time(NULL) );

    struct Pump pump1 = new_pump(1);
    struct Pump pump2 = new_pump(2);
    struct Pump pump3 = new_pump(3);

    verify_pump(pump1);


//    initialize_pumps(pumps);
//    insere_falha(pumps);
//    localiza_falha(pumps);
    return 0;
}
