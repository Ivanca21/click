
---
# H-Bridge 20 Click

> [H-Bridge 20 Click](https://www.mikroe.com/?pid_product=MIKROE-7022) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7022&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 20 Click board. It drives the
connected brushed DC motor through the three basic output states ( forward, reverse and coast ) 
via TLE92102QVW gate driver and PCA9538A port expander, and reads the motor current through 
the on-board MCP3221 ADC.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge20

### Example Key Functions

- `hbridge20_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void hbridge20_cfg_setup ( hbridge20_cfg_t *cfg );
```

- `hbridge20_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t hbridge20_init ( hbridge20_t *ctx, hbridge20_cfg_t *cfg );
```

- `hbridge20_default_cfg` This function executes a default configuration of H-Bridge 20 Click board.
```c
err_t hbridge20_default_cfg ( hbridge20_t *ctx );
```

- `hbridge20_set_motor_state` This function sets the motor operating state by driving the TLE92102 logic inputs through the PCA9538A.
```c
err_t hbridge20_set_motor_state ( hbridge20_t *ctx, uint8_t state );
```

- `hbridge20_get_current` This function reads the motor current by sampling the CSA output with the MCP3221 ADC.
```c
err_t hbridge20_get_current ( hbridge20_t *ctx, float *current );
```

- `hbridge20_reset_device` This function resets the PCA9538A port expander by toggling the RST pin logic state.
```c
void hbridge20_reset_device ( hbridge20_t *ctx );
```

### Application Init

> Initializes the driver and performs the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge20_cfg_t hbridge20_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    hbridge20_cfg_setup( &hbridge20_cfg );
    HBRIDGE20_MAP_MIKROBUS( hbridge20_cfg, MIKROBUS_POSITION_HBRIDGE20 );
    err_t init_flag = hbridge20_init( &hbridge20, &hbridge20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE20_ERROR == hbridge20_default_cfg ( &hbridge20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles the motor through forward, coast and reverse states in a loop, and logs
the current active state as well as the motor current via USB UART.

```c
void application_task ( void )
{
    float current = 0;

    log_printf( &logger, " Motor state: Forward\r\n" );
    hbridge20_set_motor_state( &hbridge20, HBRIDGE20_MOTOR_STATE_FORWARD );
    if ( HBRIDGE20_OK == hbridge20_get_current ( &hbridge20, &current ) )
    {
        log_printf( &logger, " Current: %.3f A\r\n\n", current );
    }
    Delay_ms( 1000 );
    Delay_ms( 1000 );

    log_printf( &logger, " Motor state: Coast\r\n\n" );
    hbridge20_set_motor_state( &hbridge20, HBRIDGE20_MOTOR_STATE_COAST );
    Delay_ms( 1000 );
    Delay_ms( 1000 );

    log_printf( &logger, " Motor state: Reverse\r\n" );
    hbridge20_set_motor_state( &hbridge20, HBRIDGE20_MOTOR_STATE_REVERSE );
    if ( HBRIDGE20_OK == hbridge20_get_current ( &hbridge20, &current ) )
    {
        log_printf( &logger, " Current: %.3f A\r\n\n", current );
    }
    Delay_ms( 1000 );
    Delay_ms( 1000 );

    log_printf( &logger, " Motor state: Coast\r\n\n" );
    hbridge20_set_motor_state( &hbridge20, HBRIDGE20_MOTOR_STATE_COAST );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
}
```

### Note

> The onboard SW1 switch must be in the operating position ( INH_N high ).

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
