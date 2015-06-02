#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include "tests/testhal.h"
#else
#include "hal.h"
#endif

/* Default address of the sensor after powerup. */
#define VL6180X_DEFAULT_ADDRESS 0x29

typedef struct {
    I2CDriver *i2c;
    uint8_t address;
} vl6180x_t;

void vl6180x_init(vl6180x_t *dev, I2CDriver *i2c_dev, uint8_t address);
uint8_t vl6180x_read_register(vl6180x_t *dev, uint16_t reg);
void vl6180x_write_register(vl6180x_t *dev, uint16_t reg, uint8_t val);

#ifdef __cplusplus
}
#endif
#endif
