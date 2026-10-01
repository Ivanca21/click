### Software Support

[H-Bridge 21 Click](https://www.mikroe.com/?pid_product=MIKROE-7022) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

**Example Description**

This example demonstrates the use of the H-Bridge 21 Click board. It drives the
connected brushed DC motor through the three basic output states ( forward, reverse and coast ) 
via TLE92102QVW gate driver and PCA9538A port expander, and reads the motor current through 
the on-board MCP3221 ADC.

<ins>Key Functions</ins>

- `hbridge21_cfg_setup` This function initializes Click configuration structure to initial values.
- `hbridge21_init` This function initializes all necessary pins and peripherals used for this Click board.
- `hbridge21_default_cfg` This function executes a default configuration of H-Bridge 21 Click board.
- `hbridge21_set_motor_state` This function sets the motor operating state by driving the TLE92102 logic inputs through the PCA9538A.
- `hbridge21_get_current` This function reads the motor current by sampling the CSA output with the MCP3221 ADC.
- `hbridge21_reset_device` This function resets the PCA9538A port expander by toggling the RST pin logic state.

<ins>Application Init</ins>

Initializes the driver and performs the default configuration.

<ins>Application Task</ins>

Cycles the motor through forward, coast and reverse states in a loop, and logs
the current active state as well as the motor current via USB UART.

**Application Output**

This Click board can be interfaced and monitored in two ways:
- <ins>Application Output</ins> - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- <ins>UART Terminal</ins> - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

**Additional Notes and Information**

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.
