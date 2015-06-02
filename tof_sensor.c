#include "tof_sensor.h"

void vl6180x_init(vl6180x_t *dev, I2CDriver *i2c_dev, uint8_t address)
{
    dev->i2c = i2c_dev;
    dev->address = address;
}
