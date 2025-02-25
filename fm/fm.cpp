#include "fm.hpp"

enum class Fase
{
    Wait,
    Fall,
    Goal,
} fase;

int fm_main()
{
    // ************************************************** //
    //                       setup                        //
    // ************************************************** //
    S35 s35_left(18,50);//左のサーボ
    S35 s35_right(18,50);//右のサーボ
    //I2Cのセットアップ
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(6, GPIO_FUNC_I2C);
    gpio_set_function(7, GPIO_FUNC_I2C);
    gpio_pull_up(6);
    gpio_pull_up(7);
    //BNO055のセットアップ
    BNO055 bno055();


    // ************************************************** //
    //                        loop                        //
    // ************************************************** //
    while(true){



    }
}

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    printf("init_ok\n");
    while(true) 
        fm_main();
}