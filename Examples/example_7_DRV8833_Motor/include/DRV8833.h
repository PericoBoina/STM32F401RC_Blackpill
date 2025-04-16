#ifndef DRV8833_H
#define DRV8833_H

#include "stm32f4xx_hal.h"
#include <cstdint>
#include <cstdlib> 

class DRV8833_Motor
{
public:
    DRV8833_Motor(TIM_HandleTypeDef *htim, uint32_t pwm_channel,
                  uint16_t in1_pin, GPIO_TypeDef *in1_port,
                  uint16_t in2_pin, GPIO_TypeDef *in2_port);

    void begin();
    void setSpeed(int8_t speed);
    void brake();
    void coast();

private:
    TIM_HandleTypeDef *htim_;
    uint32_t pwm_channel1_;
    uint32_t pwm_channel2_;
    uint16_t in1_pin_;
    GPIO_TypeDef *in1_port_;
    uint16_t in2_pin_;
    GPIO_TypeDef *in2_port_;
    uint32_t pwm_resolution_;
};

#endif // MOTORCONTROLLER_H