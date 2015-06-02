#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "../tof_sensor.h"
#include <cstring>

TEST_GROUP(VL6180XRegisterTestGroup)
{
    vl6180x_t dev;
    I2CDriver i2c;

    void setup(void) {
        memset(&dev, 0, sizeof(dev));
    }
};

TEST(VL6180XRegisterTestGroup, CanInitDriver)
{
    vl6180x_init(&dev, &i2c, VL6180X_DEFAULT_ADDRESS);
    POINTERS_EQUAL(&i2c, dev.i2c);
    CHECK_EQUAL(0x29, dev.address);
}

