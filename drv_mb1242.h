/*
   drv_mb1242.h : driver for MaxBotix MB1242 sonar

   Copyright (C) 2016 Simon D. Levy 

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

#pragma once

typedef struct {
    uint8_t  address;
    uint32_t time;
    uint8_t state;
} mb1242_t;


/**
  * Use addr=0 to default to factory-set address.
  */
bool mb1242_init();

int32_t mb1242_poll();
