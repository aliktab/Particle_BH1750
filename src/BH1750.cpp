/*
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

#include "BH1750.h"
#include <math.h>


BH1750::BH1750(uint8_t _addr, TwoWire & _i2c) :
  m_i2c(_i2c)
{
  m_i2c_addr = _addr;
}

bool BH1750::begin()
{
  if (!m_i2c.isEnabled())
  {
    m_i2c.begin();
  }

  setup_sensor(); // use defaults

  return true;
}

void BH1750::setup_sensor(SensMode _mode)
{
  m_i2c.beginTransmission(m_i2c_addr);
  m_i2c.write((uint8_t)_mode);
  m_i2c.endTransmission();

  m_mode = _mode;

  wait_for_measurement();
}

void BH1750::make_forced_measurement()
{
  // If we are in forced mode, the BH sensor goes back to sleep after each
  // measurement and we need to set it to forced mode once at this point, so
  // it will take the next measurement and then return to sleep again.
  // In normal mode simply does new measurements periodically.

  if (m_mode == one_time_high_res  ||
      m_mode == one_time_high_res2 ||
      m_mode == one_time_low_res)
  {
    m_i2c.beginTransmission(m_i2c_addr);
    m_i2c.write((uint8_t)m_mode);
    m_i2c.endTransmission();

    wait_for_measurement();
  }
}

float BH1750::get_light_level()
{
  m_i2c.beginTransmission(m_i2c_addr);
  m_i2c.requestFrom(m_i2c_addr, 2);
  const uint16_t level = (m_i2c.read() << 8) | m_i2c.read();
  m_i2c.endTransmission();

  return (float)level / 1.2f; // convert to lux
}

void BH1750::wait_for_measurement()
{
  delay((m_mode == one_time_low_res ||
         m_mode == continuous_low_res) ? 24 : 180); // max measurement time 24 for low res and 180 for high res
}




