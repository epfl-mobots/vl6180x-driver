#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#include "hal.h"


/* Default address of the sensor after powerup. */
#define VL6180X_DEFAULT_ADDRESS 0x29

typedef struct {
    I2CDriver *i2c;
    uint8_t address;
} vl6180x_t;

void vl6180x_init(vl6180x_t *dev, I2CDriver *i2c_dev, uint8_t address);
uint8_t vl6180x_read_register(vl6180x_t *dev, uint16_t reg);
void vl6180x_write_register(vl6180x_t *dev, uint16_t reg, uint8_t val);

/** Returns 0 if the distance was measured correctly, the error code otherwise. */
uint8_t vl6180x_measure_distance(vl6180x_t *dev, uint8_t *out_mm);

/** Sends initial configuration to device. */
void vl6180x_configure(vl6180x_t *dev);

#ifdef __cplusplus
}
#endif
#endif
