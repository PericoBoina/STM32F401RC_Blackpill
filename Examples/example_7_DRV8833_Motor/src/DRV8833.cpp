#include "DRV8833.h"
#include <cstdlib> // Añadido para la función abs()

DRV8833_Motor::DRV8833_Motor(TIM_HandleTypeDef *htim, uint32_t pwm_channel,
                             uint16_t in1_pin, GPIO_TypeDef *in1_port,
                             uint16_t in2_pin, GPIO_TypeDef *in2_port)
    : htim_(htim), pwm_channel1_(TIM_CHANNEL_3),
      pwm_channel2_(TIM_CHANNEL_4),
      in1_pin_(in1_pin), in1_port_(in1_port),
      in2_pin_(in2_pin), in2_port_(in2_port)
{
    pwm_resolution_ = htim_->Init.Period;
}

void DRV8833_Motor::begin()
{
    HAL_TIM_PWM_Start(htim_, pwm_channel1_);
    HAL_TIM_PWM_Start(htim_, pwm_channel2_);
    coast();
}

void DRV8833_Motor::setSpeed(int8_t speed)
{
    speed = (speed > 100) ? 100 : (speed < -100) ? -100
                                                 : speed;
    uint32_t pwm_value = (uint32_t)((abs(speed) * pwm_resolution_) / 100);

    if (speed > 0)
    {
        __HAL_TIM_SET_COMPARE(htim_, pwm_channel1_, pwm_value);
        __HAL_TIM_SET_COMPARE(htim_, pwm_channel2_, 0);
    }
    else if (speed < 0)
    {
        __HAL_TIM_SET_COMPARE(htim_, pwm_channel1_, 0);
        __HAL_TIM_SET_COMPARE(htim_, pwm_channel2_, pwm_value);
    }
    else
    {
        brake();
    }
}

void DRV8833_Motor::brake()
{
    __HAL_TIM_SET_COMPARE(htim_, pwm_channel1_, pwm_resolution_);
    __HAL_TIM_SET_COMPARE(htim_, pwm_channel2_, pwm_resolution_);
}

void DRV8833_Motor::coast()
{
    __HAL_TIM_SET_COMPARE(htim_, pwm_channel1_, 0);
    __HAL_TIM_SET_COMPARE(htim_, pwm_channel2_, 0);
}