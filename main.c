#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define PUMP_NUM 3

// 0 para não tem problema
// 1 para problema no petróleo
// 2 para problema no gás
struct Pump {
    int sensor400;
    int sensor800;
    int sensor1200;
    bool sensor_operating;
};

//os sensore são inicializados sem problema, sendo os sensores int inicializados em 0 eo sensor bool inicializado em false
void initialize_pumps(struct Pump pumps[PUMP_NUM]){
    for(int i=0;i<3; i++){
        pumps[i].sensor400=0;
        pumps[i].sensor800=0;
        pumps[i].sensor1200=0;
        pumps[i].sensor_operating=false;
    }
}

void display() {}

void menu() {

}

int main() {
    struct Pump pumps[3];
    initialize_pumps(pumps);


    return 0;
}
