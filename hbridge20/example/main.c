/*!
 * @file main.c
 * @brief H-Bridge 20 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 20 Click board. It drives the
 * connected brushed DC motor through the three basic output states ( forward, reverse and coast ) 
 * via TLE92102QVW gate driver and PCA9538A port expander, and reads the motor current through 
 * the on-board MCP3221 ADC.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the default configuration.
 *
 * ## Application Task
 * Cycles the motor through forward, coast and reverse states in a loop, and logs
 * the current active state as well as the motor current via USB UART.
 *
 * @note
 * The onboard SW1 switch must be in the operating position ( INH_N high ).
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge20.h"

#ifndef MIKROBUS_POSITION_HBRIDGE20
    #define MIKROBUS_POSITION_HBRIDGE20 MIKROBUS_1
#endif

static hbridge20_t hbridge20;
static log_t logger;

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

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
