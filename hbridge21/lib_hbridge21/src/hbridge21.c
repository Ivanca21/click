/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file hbridge21.c
 * @brief H-Bridge 21 Click Driver.
 */

#include "hbridge21.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief SPI MSB mask.
 * @details Definition of the MSB mask used during CRC8 calculation.
 */
#define MSB_MASK          0x80

/**
 * @brief H-Bridge 21 calculate CRC8 function.
 * @details This function calculates the AUTOSAR SAE J1850 CRC8 checksum of the
 * H-bridge driver SPI frame ( polynomial 0x1D, init 0xFF, final XOR 0xFF ).
 * @param[in] data_buf : Buffer on which the CRC8 is calculated.
 * @param[in] len : Number of bytes to calculate the CRC8 over.
 * @return Calculated CRC8 byte.
 * @note None.
 */
static uint8_t hbridge21_calculate_crc ( uint8_t *data_buf, uint8_t len );

void hbridge21_cfg_setup ( hbridge21_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HBRIDGE21_EXPANDER_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hbridge21_init ( hbridge21_t *ctx, hbridge21_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return HBRIDGE21_OK;
}

err_t hbridge21_default_cfg ( hbridge21_t *ctx ) 
{
    err_t error_flag = HBRIDGE21_OK;
    
    /* This will put motor in a coast state */
    hbridge21_reset_device( ctx );
    
    /* PCA9538A I2C expander maping:
     *     P3 -> IH2 (active low)
     *     P2 -> IH1 (active low)
     *     P1 -> IL2 (active high)
     *     P0 -> IL1 (active high)
     * 
     * Output port default value is 0xFF which would set motor in a brake state.
     * => writing 0x0C to output port puts motor in coast state. */
    error_flag |= hbridge21_expander_write_reg( ctx, HBRIDGE21_EXPANDER_CMD_OUTPUT_PORT, 
                                                     HBRIDGE21_EXPANDER_OUT_COAST );
    /* Configure all pins as outputs */
    error_flag |= hbridge21_expander_write_reg( ctx, HBRIDGE21_EXPANDER_CMD_CONFIG, 
                                                     HBRIDGE21_EXPANDER_CONFIG_OUTPUT );
    Delay_10ms( );

    /* PWR_MOD_CFG register:
     *     bit[14]  = 1  -> clear all SPI status registers
     *     bit[1:0] = 10 -> power-up mode */
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_PWR_MOD_CFG, 
                                          ( HBRIDGE21_GEN_PWR_CLEAR_STAT | 
                                            HBRIDGE21_MODE_POWER_UP ) );
    /* CONFIG_SECURED register:
     *     bit[11]  = 1  -> 3-stage charge pump enabled
     *     bit[7:6] = 01 -> keep the in-frame SPI response
     *     bit[5:4] = 10 -> VIO(current sense amplifier reference voltage) supply level 3.3 V */
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_CONFIG_SECURED,
                                          ( HBRIDGE21_CONFIG_SECURED_VIO_3V3 |
                                            HBRIDGE21_CONFIG_SECURED_RSP_IFR |
                                            HBRIDGE21_CONFIG_SECURED_CP_3STAGE ) );                
    /* GEN_CFG1 register:
     *     bit[15]    = 1 -> charge pump enabled(supplies the CSA)
     *     bit[14:13] = 01 -> forced double charge pump mode
     *     bit[6]     = 1 -> half-bridge 2 enabled
     *     bit[5]     = 1 -> half-bridge 1 enabled
     *     bit[3]     = 1 -> Current sense amplifier enabled */ 
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_GEN_CFG1, HBRIDGE21_GEN_CFG1_FORCED_CP_DEF );

    Delay_10ms( );

    /* PWR_MOD_CFG register: Request normal operation mode
     *     bit[1:0] = 01 -> normal mode */
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_PWR_MOD_CFG, HBRIDGE21_MODE_NORMAL );

    /* Clear any POR / under-voltage status latched during the power-up transition */
    error_flag |= hbridge21_clear_status( ctx );

    return error_flag;
}                                         

err_t hbridge21_write_reg ( hbridge21_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    /* Write frame : CS_LOW | 7bit_addr + 1b | data_MSB | data_LSB | CRC8 | CS_HIGH */
    uint8_t data_buf[ HBRIDGE21_FRAME_LEN ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( ( reg << 1 ) | HBRIDGE21_CMD_WRITE );
    data_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 2 ] = ( uint8_t ) data_in;
    data_buf[ 3 ] = hbridge21_calculate_crc( data_buf, HBRIDGE21_MOSI_CRC_LEN );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, HBRIDGE21_FRAME_LEN );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t hbridge21_read_reg ( hbridge21_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    /* Read frame : CS_LOW | 7bit_addr + 0b | dummy | dummy | MOSI_CRC8 | CS_HIGH
     *              MOSI_CRC8 is calculated over the 3 bytes of the frame.
     *
     * Device responds in the same frame : global_statu(8bit) | read_data_MSB | read_data_LSB | MISO_CRC8 
     *     MISO_CRC8 includes SPI register address even tho its not int the received frame(TLE92102QVW datatsheet page 50) */
    uint8_t tx_buf[ HBRIDGE21_FRAME_LEN - 1 ] = { 0 };
    uint8_t rx_buf[ HBRIDGE21_FRAME_LEN ] = { 0 };
    uint8_t crc_buf[ HBRIDGE21_FRAME_LEN ] = { 0 };

    /* MOSI payload */
    tx_buf[ 0 ] = ( uint8_t ) ( ( reg << 1 ) | HBRIDGE21_CMD_READ );
    tx_buf[ 1 ] = DUMMY;
    tx_buf[ 2 ] = DUMMY;
    uint8_t mosi_crc = hbridge21_calculate_crc( tx_buf, HBRIDGE21_MOSI_CRC_LEN );

    /* In-frame response */
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    err_t error_flag = spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf[ 1 ], 2 );
    spi_master_set_default_write_data( &ctx->spi, mosi_crc );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf[ 3 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );

    /* MISO CRC */
    crc_buf[ 0 ] = reg;
    crc_buf[ 1 ] = rx_buf[ 0 ];
    crc_buf[ 2 ] = rx_buf[ 1 ];
    crc_buf[ 3 ] = rx_buf[ 2 ];
    if ( rx_buf[ 3 ] != hbridge21_calculate_crc( crc_buf, HBRIDGE21_MISO_CRC_LEN ) ) 
    {
        error_flag = HBRIDGE21_ERROR;
    }

    *data_out = ( ( uint16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 2 ];

    return error_flag;
}

err_t hbridge21_expander_write_reg ( hbridge21_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    /* Write frame: S | sl_addr + W | A | command_bye | A | data_byte | A | P */
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = HBRIDGE21_OK;

    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;

    i2c_master_set_slave_address( &ctx->i2c, HBRIDGE21_EXPANDER_ADDRESS );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );

    return error_flag;
}

err_t hbridge21_expander_read_reg ( hbridge21_t *ctx, uint8_t cmd, uint8_t *data_out ) 
{
    /* Read frame: S | sl_addr + W | A | command_byte | A | RS | sl_addr + R | A | data_1 | A | ... data_N | NA | P */
    i2c_master_set_slave_address( &ctx->i2c, HBRIDGE21_EXPANDER_ADDRESS );
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, 1 );

    return error_flag;
}

err_t hbridge21_adc_read ( hbridge21_t *ctx, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    /* A 2-byte read starts the conversion and returns the result MSB first. */
    i2c_master_set_slave_address( &ctx->i2c, HBRIDGE21_ADC_ADDRESS );
    err_t error_flag = i2c_master_read( &ctx->i2c, data_buf, 2 );

    *data_out = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & HBRIDGE21_ADC_RESOLUTION;

    return error_flag;
}

void hbridge21_set_rst_pin ( hbridge21_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

void hbridge21_reset_device ( hbridge21_t *ctx ) 
{
    /* RST low resets PCA9538A i2c expander => all pins are configured as input(high-z) by default.
     * TLE92102QVW IHx(active low) have internal pull ups, ILx(active high) have internal pull downs
     * => motor off. */
    digital_out_high( &ctx->rst );
    Delay_1ms( );
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_1ms( );
}

uint8_t hbridge21_get_int_pin ( hbridge21_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

err_t hbridge21_set_motor_state ( hbridge21_t *ctx, uint8_t state ) 
{
    uint8_t out_val  = 0;
    uint8_t port_val = 0;

    switch ( state ) 
    {
        case HBRIDGE21_MOTOR_STATE_FORWARD: 
            out_val = HBRIDGE21_EXPANDER_OUT_FORWARD;
            break;
        case HBRIDGE21_MOTOR_STATE_REVERSE: 
            out_val = HBRIDGE21_EXPANDER_OUT_REVERSE;
            break;
        case HBRIDGE21_MOTOR_STATE_COAST: 
            out_val = HBRIDGE21_EXPANDER_OUT_COAST;
            break;
        default: 
            return HBRIDGE21_ERROR;
    }

    /* Read-modify-write through the PCA9538A i2c expander Output Port register so the unused pins are preserved */
    err_t error_flag = hbridge21_expander_read_reg( ctx, HBRIDGE21_EXPANDER_CMD_OUTPUT_PORT, &port_val );
    port_val &= ~HBRIDGE21_EXPANDER_PIN_MOTOR_MASK;
    port_val |= out_val;
    error_flag |= hbridge21_expander_write_reg( ctx, HBRIDGE21_EXPANDER_CMD_OUTPUT_PORT, port_val );

    return error_flag;
}

err_t hbridge21_get_current ( hbridge21_t *ctx, float *current ) 
{
    /* TLE92102QVW page 45 -> bidirectional CSA(current sense amplifier) : 
     *                              VCSO = VCSO_REF_Unidir + ( VCSIP - VCSIN ) × GDIFF
     *                           => VCSIP - VCSIN = ( VCSO - VCSO_REF ) / GDIFF
     *
     * Schematic -> Vshunt(R16) = VCSIP - VCSIN, R16 = 1 mOhm
     *              Ishunt = Vshunt / Rshunt
     *                  => Ishunt = ( VCSIP - VCSIN ) / Rshunt
     *
     * =>  Ishunt = ( VCSO - VCSO_REF ) / ( GDIFF * Rshunt ) */
    uint16_t adc_code = 0;
    float cso_voltage = 0;
    float shunt_voltage = 0;
    
    err_t error_flag = hbridge21_adc_read( ctx, &adc_code );
    
    /* Current sense amplifier output = raw * LSB, LSB = Vref / resolution */
    cso_voltage = ( float ) adc_code * HBRIDGE21_VREF_3V3 / HBRIDGE21_ADC_RESOLUTION_FLOAT;

    /* Bidirectional CSA mode -> VCSO_REF = 0.5 * Vref(TLE92102QVW datasheet page 48) */
    shunt_voltage = ( cso_voltage - ( HBRIDGE21_CSA_VREF_COEFF_BIDIR * HBRIDGE21_VREF_3V3 ) ) / HBRIDGE21_CSA_GAIN;

    *current = shunt_voltage / HBRIDGE21_SHUNT_RES;

    return error_flag;
}

err_t hbridge21_clear_status ( hbridge21_t *ctx )
{
    err_t error_flag = HBRIDGE21_OK;
    
    /* Clear SUP_STAT, DEV_STAT2, DEV_STAT1, and LF_STAT status registers */
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_SUP_STAT, HBRIDGE21_GEN_SUP_STAT_CLEAR );
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_DEV_STAT2, HBRIDGE21_GEN_DEV_STAT2_CLEAR );
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_DEV_STAT1, HBRIDGE21_GEN_DEV_STAT1_CLEAR );
    error_flag |= hbridge21_write_reg( ctx, HBRIDGE21_REG_LF_STAT, HBRIDGE21_GEN_LF_STAT_CLEAR );

    Delay_5ms( );

    return error_flag;
}

static uint8_t hbridge21_calculate_crc ( uint8_t *data_buf, uint8_t len ) 
{
    uint8_t crc = HBRIDGE21_CRC_INIT;

    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        crc ^= data_buf[ cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( MSB_MASK == ( crc & MSB_MASK ) ) 
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ HBRIDGE21_CRC_POLY );
            }
            else 
            {
                crc = ( uint8_t ) ( crc << 1 );
            }
        }
    }

    return crc ^ HBRIDGE21_CRC_XOR;
}

// ------------------------------------------------------------------------ END
