#ifndef ADS114_H
#define ADS114_H

#include "driver/i2c.h"
#include "adcbase.h"

#define I2C_MASTER_SCL_IO           3                           /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           5                           /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                           /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000                      /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000                    
#define ADS1114_ADDR                0x48    


class ADS1114 : public ADCBase {
  public:
    ADS1114 (i2c_port_t port, uint8_t address=0);
    ADCReading read(void) override;
    int init(void);

  private:
    int setDataRegister(void);

    i2c_port_t port; ///< I2C-Interface Port
    uint8_t address; ///< I2C-Address of the sensor
    int i2c_timeout_ms = 100; ///< I2C Timeout in ms


};

#endif /* ifndef ADS114_H */
