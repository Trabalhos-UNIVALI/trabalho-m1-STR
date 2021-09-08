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
    bool operational_problem_oil;
    bool operational_problem_gas;
    struct Pipe oil;
    struct Pipe gas;
};

bool rand_bool() {
    time_t t;
    int val = rand() % 20; // 5% chance of getting an error
    if(val == 0) {
        return true;
    }

    return false;
}

double calculate_time() {
    return ((double) (end - start)) ;
}

//os sensore são inicializados como funcionais
struct Pump new_pump(int id){
    struct Pump pump;

    pump.id = id;
    pump.is_operating = true;
    pump.operational_problem_oil = false;
    pump.operational_problem_gas = false;

    pump.gas.isOk_sensor400 = true;
    pump.gas.isOk_sensor800 = true;
    pump.gas.isOk_sensor1200 = true;

    pump.oil.isOk_sensor400 = true;
    pump.oil.isOk_sensor800 = true;
    pump.oil.isOk_sensor1200 = true;

    return pump;

}

double verify_400m_pipe(bool* pipe400, bool* isOpereating, bool* opProblem) {
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
        *isOpereating = 0;
        *opProblem = 1;
    }

    // Atualiza se existe erro na struct
    *pipe400 = !error;

    end = clock();

    // Retorna o tempo de execução
    return calculate_time();
}

double verify_800m_pipe(bool* pipe800, bool* isOpereating, bool* opProblem) {
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
        *isOpereating = 0;
        *opProblem = 1;
    }

    // Atualiza se existe erro na struct
    *pipe800 = !error;

    end = clock();

    // Retorna o tempo de execução
    return calculate_time();
}

double verify_1200m_pipe(bool* pipe1200, bool* isOpereating, bool* opProblem) {
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
        *isOpereating = 0;
        *opProblem = 1;
    }

    // Atualiza se existe erro na struct
    *pipe1200 = !error;

    end = clock();

    // Retorna o tempo de execução
    return calculate_time();
}

bool verify_pump(struct Pump pump) {
    bool *refIsOperating = &pump.is_operating;
    bool *refOpProblemGas = &pump.operational_problem_gas;
    bool *refOpProblemOil = &pump.operational_problem_oil;

    bool *refGas400 = &pump.gas.isOk_sensor400;
    double timeGas400 = verify_400m_pipe(refGas400, refIsOperating, refOpProblemGas);

    bool *refGas800 = &pump.gas.isOk_sensor800;
    double timeGas800 = verify_800m_pipe(refGas800, refIsOperating, refOpProblemGas);

    bool *refGas1200 = &pump.gas.isOk_sensor1200;
    double timeGas1200 = verify_1200m_pipe(refGas1200, refIsOperating, refOpProblemGas);

    bool *refOil400 = &pump.oil.isOk_sensor400;
    double timeOil400 = verify_400m_pipe(refOil400, refIsOperating, refOpProblemOil);

    bool *refOil800 = &pump.oil.isOk_sensor800;
    double timeOil800 = verify_800m_pipe(refOil800, refIsOperating, refOpProblemOil);

    bool *refOil1200 = &pump.oil.isOk_sensor1200;
    double timeOil1200 = verify_1200m_pipe(refOil1200, refIsOperating, refOpProblemOil);

    int returnVal = pump.is_operating;

    double timeGas = timeGas400 + timeGas800 + timeGas1200;
    double timeOil = timeOil400 + timeOil800 + timeOil1200;
    double timeFinal = timeGas + timeOil;

    start = clock();

    if(!pump.is_operating) {
        printf("Pump %d is not operating! SHUTTING DOWN!!!\n", pump.id);
    } else {
        printf("Pump %d is operating!\n", pump.id);
    }

    if(pump.operational_problem_gas) {
        printf("Gas pipe is not functional!\n");
    } else {
        printf("Gas pipe is functional!\n");
    }

    if(pump.operational_problem_oil) {
        printf("Oil pipe is not functional!\n");
    } else {
        printf("Oil pipe is functional!\n");
    }


    printf("GAS SENSOR 400m - Time: %dms --> OK?(0 = No, 1 = Yes): %d \n", (int) timeGas400, pump.gas.isOk_sensor400);
    printf("GAS SENSOR 800m - Time: %dms --> OK?(0 = No, 1 = Yes): %d \n", (int) timeGas800, pump.gas.isOk_sensor800);
    printf("GAS SENSOR 1200m - Time: %dms --> OK?(0 = No, 1 = Yes): %d \n \n", (int) timeGas1200, pump.gas.isOk_sensor1200);
    printf("OIL SENSOR 400m - Time: %dms --> OK?(0 = No, 1 = Yes): %d \n", (int) timeOil400, pump.oil.isOk_sensor400);
    printf("OIL SENSOR 800m - Time: %dms --> OK?(0 = No, 1 = Yes): %d \n", (int) timeOil800, pump.oil.isOk_sensor800);
    printf("OIL SENSOR 1200m - Time: %dms --> OK?(0 = No, 1 = Yes): %d \n", (int) timeOil1200, pump.oil.isOk_sensor1200);

    printf("Final execution time measurement for Gas pipe: %dms \n", (int) timeGas);
    printf("Final execution time measurement for Oil pipe: %dms \n", (int) timeOil);
    printf("Final execution time measurement for all pump: %dms \n", (int) timeFinal);

    end = clock();
    printf("Display execution time measurement: %dms \n\n", (int) calculate_time());

    return returnVal;
}

int main() {
    srand(time(NULL));
    
    struct Pump pump1 = new_pump(1);
    struct Pump pump2 = new_pump(2);
    struct Pump pump3 = new_pump(3);

    int ok1 = 1;
    int ok2 = 1;
    int ok3 = 1;
    while(true) {

        if(ok1) {
            ok1 = verify_pump(pump1);
        }
        if(ok2) {
            ok2 = verify_pump(pump2);
        }

        if(ok3) {
            ok3 = verify_pump(pump3);
        }


        if(!ok1 && !ok2 && !ok3) {
            break;
        }

    }

    return 0;
}
