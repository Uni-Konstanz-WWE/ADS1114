
    #include <ads1114.h>
    #include <stdio.h>
    #include <string.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
    #include "driver/i2c.h"

int ADS1114::i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
 
       i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        //.master.clk_speed = I2C_MASTER_FREQ_HZ,
        {
         I2C_MASTER_FREQ_HZ
        },
        .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL,
    };

    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    return 0;
}

int ADS1114::setDataRegister(void)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,0x90,I2C_MASTER_ACK);
    i2c_master_write_byte(cmd,0x00,I2C_MASTER_ACK);
    i2c_master_stop(cmd); 
    i2c_master_cmd_begin(I2C_NUM_0,cmd,1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return 0;
}

int ADS1114::read(void)
{   
    setDataRegister();

    int data=0;
    uint8_t data1,data0;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,0x91,I2C_MASTER_ACK);
    i2c_master_read_byte(cmd,&data1,I2C_MASTER_ACK);
    i2c_master_read_byte(cmd,&data0,I2C_MASTER_ACK);
    i2c_master_stop(cmd); 
    i2c_master_cmd_begin(I2C_NUM_0,cmd,1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    data = (int)data0+(int)(data1<<8);
    return data;
}

int ADS1114::init(void)
{
    ADS1114::i2c_master_init();

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,0x90,I2C_MASTER_ACK);
    i2c_master_write_byte(cmd,0x01,I2C_MASTER_ACK);
    i2c_master_write_byte(cmd,0x8E,I2C_MASTER_ACK);
    i2c_master_write_byte(cmd,0x43,I2C_MASTER_ACK);
    i2c_master_stop(cmd); 
    i2c_master_cmd_begin(I2C_NUM_0,cmd,1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return 0;
}