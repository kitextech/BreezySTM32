/*
   mpu6500read.c : report acc

   Copyright (C) 2016 James Jackson

   This file is part of BreezySTM32.

   BreezySTM32 is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   BreezySTM32 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with BreezySTM32.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <breezystm32.h>
#include <drivers/mpu6500.h>

#define BOARD_REV 6


float accel_scale;
float gyro_scale;

int16_t accel_data[3];
int16_t gyro_data[3];
volatile int16_t temp_data;
// int16_t mag_data[3];


volatile uint8_t accel_status = 0;
volatile uint8_t gyro_status = 0;
volatile uint8_t temp_status = 0;
volatile bool mpu_new_measurement = false;
volatile uint32_t interruptCount = 0;

void interruptCallback(void)
{
 mpu_new_measurement = true;
 interruptCount++;
 mpu6500_request_async_accel_read(accel_data, &accel_status);
 mpu6500_request_async_gyro_read(gyro_data, &gyro_status);
 // mpu6500_request_async_temp_read(&temp_data, &temp_status);
}



void setup(void)
{
   i2cInit(I2CDEV); // I2CDEV defined in makefile.f*

   i2cWrite(0, 0, 0);

   //Init IMU (has to come last because of the ISR)
   mpu6500_register_interrupt_cb(&interruptCallback);
   uint16_t acc1G;
   mpu6500_init(true, &acc1G, &gyro_scale, BOARD_REV);
   accel_scale = 9.80665f / acc1G;
}

void loop(void)
{

  if (accel_status == I2C_JOB_COMPLETE)
  {
    printf("%d\t %d\t %d\n",
      (int32_t)(accel_data[0]*accel_scale*1000.0f),
      (int32_t)(accel_data[1]*accel_scale*1000.0f),
      (int32_t)(accel_data[2]*accel_scale*1000.0f));
  }
  delay(10);

  // delay(100);
  // printf("InterruptCount: %d\n", interruptCount);
}
