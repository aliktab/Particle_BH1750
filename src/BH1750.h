#pragma once

/*
  Based on: https://github.com/davidegironi/spark-bh1750lib
  DataSheet:

  Copyright (C) 2014 Alik <aliktab@gmail.com> All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

// this will load the definition for common Particle variable types
#include <Particle.h>


#define BH1750_BLINK_OFF       0
#define BH1750_BLINK_2HZ       1
#define BH1750_BLINK_1HZ       2
#define BH1750_BLINK_HALFHZ    3


class BH1750
{
public:

  enum SensMode
  {
    power_down            = 0x00,
    power_on              = 0x01,

    // start measurement at 1lx resolution. measurement time is approx 120ms.
    continuous_high_res   = 0x10,

    // start measurement at 0.5lx resolution. measurement time is approx 120ms.
    continuous_high_res2  = 0x11,

    // start measurement at 4lx resolution. measurement time is approx 16ms.
    continuous_low_res    = 0x13,

    // start measurement at 1lx resolution. measurement time is approx 120ms.
    // device is automatically set to power down after measurement.
    one_time_high_res     = 0x20,

    // start measurement at 0.5lx resolution. measurement time is approx 120ms.
    // device is automatically set to power down after measurement.
    one_time_high_res2    = 0x21,

    // start measurement at 1lx resolution. measurement time is approx 120ms.
    // device is automatically set to power down after measurement.
    one_time_low_res      = 0x23
  };

  // Constructor: I2C address, I2C interface
  BH1750(
      uint8_t   _addr = 0x23,
      TwoWire & _i2c  = Wire
    );

  bool begin();

  // setup sensor with given parameters / settings
  void setup_sensor(
      SensMode _mode = continuous_high_res2
    );

  // make a new measurement (only possible in forced mode)
  void make_forced_measurement();

  float get_light_level();

protected:

  void wait_for_measurement();

  SensMode   m_mode;

  uint8_t    m_i2c_addr;
  TwoWire &  m_i2c;
};

