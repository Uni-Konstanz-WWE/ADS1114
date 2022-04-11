
#ifndef ADS114_H
#define ADS114_H

#define I2C_MASTER_SCL_IO           3                           /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           5                           /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                           /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000                      /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000                    
#define ADS1114_ADDR                0x48    


class ADS1114{
    public:
        int read(void);
        int init(void);

    private:
        int setDataRegister(void);
        int i2c_master_init(void);


};

#endif /* ifndef ADS114_H */
