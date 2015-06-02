#include "tof_sensor.h"
#include "vl6180x_registers.h"

void vl6180x_init(vl6180x_t *dev, I2CDriver *i2c_dev, uint8_t address)
{
    dev->i2c = i2c_dev;
    dev->address = address;
}

uint8_t vl6180x_measure_distance(vl6180x_t *dev, uint8_t *out_mm)
{
    uint8_t status, mm;

    /* Start measurement. */
    vl6180x_write_register(dev, VL6180X_SYSRANGE_START, 0x01);

    /* Wait for measurement ready. */
    do {
        status = vl6180x_read_register(dev, VL6180X_RESULT_INTERRUPT_STATUS_GPIO);
    } while ((status & (1 << 2)) == 0);

    /* Read result. */
    mm = vl6180x_read_register(dev, VL6180X_RESULT_RANGE_VAL);

    /* Clear interrupt flag. */
    vl6180x_write_register(dev, VL6180X_SYSTEM_INTERRUPT_CLEAR, 0x01);

    do {
        status = vl6180x_read_register(dev, VL6180X_RESULT_RANGE_STATUS);
    } while ((status & (1 << 0)) == 0);

    return (status >> 4);
}
