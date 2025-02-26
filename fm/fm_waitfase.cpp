#include "pico/stdlib.h"
#include <vector>


void fall_fase(){
    std::vector<std::vector<double>> bno_data = bno055.read();//{accel,grv,mag}の順番で入っている想定
    double accel_abs = abs(bno_data[0]) + abs(bno_data[1]) + abs(bno_data[2]);
    if(accel_abs > 10/*[m/s^2]*/){
        //ここにフェーズを変えるコードを書く
    }
}