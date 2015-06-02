#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "../tof_sensor.h"
#include <cstring>

uint8_t vl6180x_read_register(vl6180x_t *dev, uint16_t reg)
{
    return mock().actualCall(__FUNCTION__)
                 .withIntParameter("reg", reg)
                 .returnIntValue();
}

void vl6180x_write_register(vl6180x_t *dev, uint16_t reg, uint8_t val)
{
    mock().actualCall(__FUNCTION__)
          .withIntParameter("reg", reg)
          .withIntParameter("val", val);
}

TEST_GROUP(VL6180XRegisterTestGroup)
{
    vl6180x_t dev;
    I2CDriver i2c;

    void setup(void)
    {
        vl6180x_init(&dev, &i2c, VL6180X_DEFAULT_ADDRESS);
    }

    void teardown(void)
    {
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(VL6180XRegisterTestGroup, CanInitDriver)
{
    POINTERS_EQUAL(&i2c, dev.i2c);
    CHECK_EQUAL(0x29, dev.address);
}

TEST(VL6180XRegisterTestGroup, CanReadRegister)
{
    uint8_t ret;

    mock().expectOneCall("vl6180x_read_register")
          .withIntParameter("reg", 0xaabb)
          .andReturnValue(42);

    ret = vl6180x_read_register(&dev, 0xaabb);

    CHECK_EQUAL(ret, 42);
}

TEST(VL6180XRegisterTestGroup, CanWriteRegister)
{
    mock().expectOneCall("vl6180x_write_register")
          .withIntParameter("reg", 0xaabb)
          .withIntParameter("val", 0xff);

    vl6180x_write_register(&dev, 0xaabb, 0xff);
}

