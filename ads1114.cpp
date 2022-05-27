#include <ads1114.h>
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/i2c.h"


ADS1114::ADS1114(i2c_port_t port, uint8_t address) : port(port), address(address) {
}


int ADS1114::setDataRegister(void)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd,0x90,I2C_MASTER_ACK);
  i2c_master_write_byte(cmd,0x00,I2C_MASTER_ACK);
  i2c_master_stop(cmd); 
  i2c_master_cmd_begin(port, cmd, i2c_timeout_ms / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return 0;
}


ADCReading ADS1114::read(void) {   
  setDataRegister();

  ADCReading reading;
  uint8_t data1, data0;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd,0x91,I2C_MASTER_ACK);
  i2c_master_read_byte(cmd,&data1,I2C_MASTER_ACK);
  i2c_master_read_byte(cmd,&data0,I2C_MASTER_ACK);
  i2c_master_stop(cmd); 
  i2c_master_cmd_begin(port, cmd, i2c_timeout_ms / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);

  reading.value = (int)data0+(int)(data1<<8);
  reading.good = true;
  return reading;
}


int ADS1114::init(void) {

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
