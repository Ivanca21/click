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
 * @file hbridge20.h
 * @brief This file contains API for H-Bridge 20 Click Driver.
 */

#ifndef HBRIDGE20_H
#define HBRIDGE20_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup hbridge20 H-Bridge 20 Click Driver
 * @brief API for configuring and manipulating H-Bridge 20 Click driver.
 * @{
 */

/**
 * @defgroup hbridge20_reg H-Bridge 20 Registers List
 * @brief List of registers of H-Bridge 20 Click driver.
 */

/**
 * @addtogroup hbridge20_reg
 * @{
 */

/**
 * @brief H-Bridge 20 register list.
 * @details Specified register list of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_REG_CONFIG_SECURED                 0x01
#define HBRIDGE20_REG_PWR_MOD_CFG                    0x02
#define HBRIDGE20_REG_WD_CFG                         0x03
#define HBRIDGE20_REG_GEN_CFG1                       0x04
#define HBRIDGE20_REG_GEN_CFG2                       0x05
#define HBRIDGE20_REG_GDRV_CFG1                      0x07
#define HBRIDGE20_REG_GDRV_CFG2                      0x08
#define HBRIDGE20_REG_GDRV_CFG3                      0x09
#define HBRIDGE20_REG_GDRV_TON_HS                    0x0A
#define HBRIDGE20_REG_GDRV_TON_LS                    0x0B
#define HBRIDGE20_REG_GDRV_TOFF_HS                   0x0C
#define HBRIDGE20_REG_GDRV_TOFF_LS                   0x0D
#define HBRIDGE20_REG_GDRV_T3OFF                     0x0E
#define HBRIDGE20_REG_GDRV_ION_HS1                   0x0F
#define HBRIDGE20_REG_GDRV_ION_LS1                   0x10
#define HBRIDGE20_REG_GDRV_ION_HS2                   0x11
#define HBRIDGE20_REG_GDRV_ION_LS2                   0x12
#define HBRIDGE20_REG_GDRV_I3ON                      0x15
#define HBRIDGE20_REG_GDRV_ION_IOFF_DIDT             0x16
#define HBRIDGE20_REG_GDRV_IOFF_HS1                  0x17
#define HBRIDGE20_REG_GDRV_IOFF_LS1                  0x18
#define HBRIDGE20_REG_GDRV_IOFF_HS2                  0x19
#define HBRIDGE20_REG_GDRV_IOFF_LS2                  0x1A
#define HBRIDGE20_REG_CSA_CFG                        0x1D
#define HBRIDGE20_REG_FAILURE_CFG                    0x1E
#define HBRIDGE20_REG_SELF_TEST_CFG                  0x1F
#define HBRIDGE20_REG_SUP_STAT                       0x25
#define HBRIDGE20_REG_SPI_STAT                       0x26
#define HBRIDGE20_REG_DEV_STAT1                      0x27
#define HBRIDGE20_REG_DEV_STAT2                      0x28
#define HBRIDGE20_REG_LF_STAT                        0x29
#define HBRIDGE20_REG_SH_LEVEL_STAT                  0x2A
#define HBRIDGE20_REG_BD_STAT                        0x2B
#define HBRIDGE20_REG_WD_CLK_CNT                     0x2C
#define HBRIDGE20_REG_PHASE1_CNT                     0x2D
#define HBRIDGE20_REG_PHASE2_CNT                     0x2E
#define HBRIDGE20_REG_TDON_TDOFF_HS1                 0x30
#define HBRIDGE20_REG_TDON_TDOFF_LS1                 0x31
#define HBRIDGE20_REG_TDON_TDOFF_HS2                 0x32
#define HBRIDGE20_REG_TDON_TDOFF_LS2                 0x33
#define HBRIDGE20_REG_TSLEW_ON_OFF_HS1               0x36
#define HBRIDGE20_REG_TSLEW_ON_OFF_LS1               0x37
#define HBRIDGE20_REG_TSLEW_ON_OFF_HS2               0x38
#define HBRIDGE20_REG_TSLEW_ON_OFF_LS2               0x39

/*! @} */ // hbridge20_reg

/**
 * @defgroup hbridge20_set H-Bridge 20 Registers Settings
 * @brief Settings for registers of H-Bridge 20 Click driver.
 */

/**
 * @addtogroup hbridge20_set
 * @{
 */

/**
 * @brief H-Bridge 20 port expander command setting.
 * @details Specified setting for port expander command of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_EXPANDER_CMD_INPUT_PORT            0x00
#define HBRIDGE20_EXPANDER_CMD_OUTPUT_PORT           0x01
#define HBRIDGE20_EXPANDER_CMD_POLARITY_INV          0x02
#define HBRIDGE20_EXPANDER_CMD_CONFIG                0x03

/**
 * @brief H-Bridge 20 hbridge SPI frame setting.
 * @details Specified setting for H-bridge SPI frame of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_FRAME_LEN                          4
#define HBRIDGE20_CMD_READ                           0x00
#define HBRIDGE20_CMD_WRITE                          0x01

/**
 * @brief H-Bridge 20 CONFIG_SECURED register setting.
 * @details Specified setting for CONFIG_SECURED register of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_CONFIG_SECURED_CP_3STAGE           0x0800

/**
 * @brief H-Bridge 20 CRC8 setting.
 * @details Specified setting for CRC8 of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_CRC_POLY                           0x1D
#define HBRIDGE20_CRC_INIT                           0xFF
#define HBRIDGE20_CRC_XOR                            0xFF

/**
 * @brief H-Bridge 20 GEN_CFG1 register setting.
 * @details Specified setting for GEN_CFG1 register of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_GEN_CFG1_FORCED_CP_DEF             0xA96C
#define HBRIDGE20_GEN_CFG1_DEFAULT                   0x6904
#define HBRIDGE20_GEN_CFG1_CSA_EN                    0x0008
#define HBRIDGE20_GEN_CFG1_HB1_EN                    0x0020
#define HBRIDGE20_GEN_CFG1_HB2_EN                    0x0040
#define HBRIDGE20_GEN_CFG1_CP_EN                     0x8000

/**
 * @brief H-Bridge 20 CONFIG_SECURED register setting.
 * @details Specified setting for CONFIG_SECURED register of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_CONFIG_SECURED_VIO_3V3             0x0020
#define HBRIDGE20_CONFIG_SECURED_RSP_IFR             0x0040

/**
 * @brief H-Bridge 20 status registers clear masks setting.
 * @details Specified setting for status registers clear masks of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_GEN_SUP_STAT_CLEAR                 0x81CF
#define HBRIDGE20_GEN_DEV_STAT2_CLEAR                0x367F
#define HBRIDGE20_GEN_DEV_STAT1_CLEAR                0x0004
#define HBRIDGE20_GEN_LF_STAT_CLEAR                  0x021E
#define HBRIDGE20_GEN_PWR_CLEAR_STAT                 0x4000

/**
 * @brief H-Bridge 20 CRC length setting.
 * @details Specified setting for CRC length of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_MOSI_CRC_LEN                       3
#define HBRIDGE20_MISO_CRC_LEN                       4                                 

/**
 * @brief H-Bridge 20 operation mode setting.
 * @details Specified setting for operation mode of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_MODE_NORMAL                        0x0001
#define HBRIDGE20_MODE_POWER_UP                      0x0002

/**
 * @brief H-Bridge 20 port expander pin bit mask setting.
 * @details Specified setting for port expander pin bit mask of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_EXPANDER_PIN_IL1                   0x01
#define HBRIDGE20_EXPANDER_PIN_IL2                   0x02
#define HBRIDGE20_EXPANDER_PIN_IH1                   0x04
#define HBRIDGE20_EXPANDER_PIN_IH2                   0x08
#define HBRIDGE20_EXPANDER_PIN_MOTOR_MASK            0x0F
#define HBRIDGE20_EXPANDER_PIN_NONE                  0x00
#define HBRIDGE20_EXPANDER_PIN_ALL                   0xFF

/**
 * @brief H-Bridge 20 port expander configuration setting.
 * @details Specified setting for port expander configuration of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_EXPANDER_CONFIG_OUTPUT             0x00

/**
 * @brief H-Bridge 20 motor output state value setting.
 * @details Specified setting for motor output state value of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_EXPANDER_OUT_COAST                 0x0C
#define HBRIDGE20_EXPANDER_OUT_FORWARD               0x0A
#define HBRIDGE20_EXPANDER_OUT_REVERSE               0x05

/**
 * @brief H-Bridge 20 motor state selection setting.
 * @details Specified setting for motor state selection of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_MOTOR_STATE_COAST                  0
#define HBRIDGE20_MOTOR_STATE_FORWARD                1
#define HBRIDGE20_MOTOR_STATE_REVERSE                2

/**
 * @brief H-Bridge 20 current measurement setting.
 * @details Specified setting for current measurement of H-Bridge 20 Click driver.
 */
#define HBRIDGE20_ADC_RESOLUTION                     0x0FFF
#define HBRIDGE20_ADC_RESOLUTION_FLOAT               4096.0f
#define HBRIDGE20_VREF_3V3                           3.3f
#define HBRIDGE20_CSA_GAIN                           8.0f
#define HBRIDGE20_SHUNT_RES                          0.001f
#define HBRIDGE20_CSA_VREF_COEFF_UNIDIR              0.15f
#define HBRIDGE20_CSA_VREF_COEFF_BIDIR               0.5f

/**
 * @brief H-Bridge 20 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 20 Click driver.
 */
#define HBRIDGE20_EXPANDER_ADDRESS                   0x70
#define HBRIDGE20_ADC_ADDRESS                        0x4D

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge20_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE20_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE20_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge20_set

/**
 * @defgroup hbridge20_map H-Bridge 20 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 20 Click driver.
 */

/**
 * @addtogroup hbridge20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 20 Click to the selected MikroBUS.
 */
#define HBRIDGE20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge20_map
/*! @} */ // hbridge20

/**
 * @brief H-Bridge 20 Click context object.
 * @details Context object definition of H-Bridge 20 Click driver.
 */
typedef struct hbridge20_s
{
    digital_out_t rst;                              /**< Reset pin (active low). */

    digital_in_t int_pin;                           /**< Interrupt pin (active low). */

    i2c_master_t i2c;                               /**< I2C driver object. */
    spi_master_t spi;                               /**< SPI driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} hbridge20_t;

/**
 * @brief H-Bridge 20 Click configuration object.
 * @details Configuration object definition of H-Bridge 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rst;                                 /**< Reset pin descriptor. */
    pin_name_t int_pin;                             /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;                           /**< I2C serial speed. */
    uint8_t    i2c_address;                         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hbridge20_cfg_t;

/**
 * @brief H-Bridge 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE20_OK = 0,
    HBRIDGE20_ERROR = -1

} hbridge20_return_value_t;

/*!
 * @addtogroup hbridge20 H-Bridge 20 Click Driver
 * @brief API for configuring and manipulating H-Bridge 20 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge20_cfg_setup ( hbridge20_cfg_t *cfg );

/**
 * @brief H-Bridge 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_init ( hbridge20_t *ctx, hbridge20_cfg_t *cfg );

/**
 * @brief H-Bridge 20 default configuration function.
 * @details This function executes a default configuration of H-Bridge 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge20_default_cfg ( hbridge20_t *ctx );

/**
 * @brief H-Bridge 20 write register function.
 * @details This function writes a 16-bit data word to the selected TLE92102QVW
 * H-bridge register over SPI, appending the CRC8 to the frame.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] reg :  Register address.
 * @param[in] data_in : 16-bit data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_write_reg ( hbridge20_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief H-Bridge 20 read register function.
 * @details This function reads a 16-bit data word from the selected TLE92102QVW 
 * H-bridge register over SPI and validates the CRC8 of the response frame.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] reg :  Register address.
 * @param[out] data_out : Pointer to the 16-bit output data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_read_reg ( hbridge20_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief H-Bridge 20 expander write register function.
 * @details This function writes a single byte of data to the PCA9538A 
 * port expander register over I2C.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] cmd : Command byte which selects the targeted expander register.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_expander_write_reg ( hbridge20_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief H-Bridge 20 expander read register function.
 * @details This function reads a single byte of data from the PCA9538A
 * port expander register over I2C.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] cmd : Command byte which selects the targeted expander register.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_expander_read_reg ( hbridge20_t *ctx, uint8_t cmd, uint8_t *data_out );

/**
 * @brief H-Bridge 20 ADC read function.
 * @details This function reads the raw 12-bit conversion result from the
 * MCP3221 ADC over I2C.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the raw 12-bit ADC code (0 to 4095).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_adc_read ( hbridge20_t *ctx, uint16_t *data_out );

/**
 * @brief H-Bridge 20 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void hbridge20_set_rst_pin ( hbridge20_t *ctx, uint8_t state );

/**
 * @brief H-Bridge 20 reset device function.
 * @details This function resets the PCA9538A port expander by toggling the RST 
 * pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge20_reset_device ( hbridge20_t *ctx );

/**
 * @brief H-Bridge 20 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hbridge20_get_int_pin ( hbridge20_t *ctx );

/**
 * @brief H-Bridge 20 set motor state function.
 * @details This function sets the motor operating state by driving the TLE92102
 * logic inputs through the PCA9538A port expander output port.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Coast,
 *                    @li @c 1 - Forward,
 *                    @li @c 2 - Reverse.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The brake state is not implemented as it triggers the overcurrent protection 
 * and safe-off state.
 */
err_t hbridge20_set_motor_state ( hbridge20_t *ctx, uint8_t state );

/**
 * @brief H-Bridge 20 get current function.
 * @details This function reads the motor current by sampling the CSA output with
 * the MCP3221 ADC.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @param[out] current : Pointer to the motor current in amperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_get_current ( hbridge20_t *ctx, float *current );

/**
 * @brief H-Bridge 20 clear status function.
 * @details This function clears the status registers of the TLE92102QVW H-bridge driver.
 * @param[in] ctx : Click context object.
 * See #hbridge20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge20_clear_status ( hbridge20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE20_H

/*! @} */ // hbridge20

// ------------------------------------------------------------------------ END
