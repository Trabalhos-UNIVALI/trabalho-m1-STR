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
    return ((double) (end - start)) ;
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
