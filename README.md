# Printf_Custom
 A small footprint and fast printf for stm32, suports UART and USB CDC VCP.

### Statistics
Optimization  | Flash memory used
------------- | -------------
None  | 1.99KB
Optimize for size (-Os)  | 830B

### Features

- Use as standart printf() from sdtio.h

- %c prints as character

- %s prints as string

- %d prints as signed integer/decimal number

- %i prints as signed integer/decimal number

- %u prints as unsigned integer/decima number

- %b prints as binary number

- %o prints as octal number

- %x prints as hexadecimal number

- %f prints as float number with 6 decimal digits

- %.nf prints as float number with n decimal digits

### Example: FreeRTOS using osDelay()
```C
while(printf_custom("Hello from task1   %s   %c   %i   %u   %o   %x   %b   %.2f   %f\r\n", "string", 'X', -33, 33, 33, 33, 33, -33.33, 33.33)!=0){
	osDelay(1);
}
```

### Example: Bare-Metal using HAL_Delay()
```C
while(printf_custom("Hello from task1   %s   %c   %i   %u   %o   %x   %b   %.2f   %f\r\n", "string", 'X', -33, 33, 33, 33, 33, -33.33, 33.33)!=0){
	HAL_Delay(1);
}
```

### How to use
To use this library, you must use CUBEMX or STM32CubeIDE to configure and generate your peripherals code with HAL libraries.

In printf_custom.h define USB_PRINTF or UART_PRINTF. If you are using UART_PRINTF also define witch huart you are using in UART_PORT define. Include printf_custom.h in your application code and use printf_custom() as standard printf()

You can also use this library with SPI, I2C and CAN with some modifications in the code. This library have been tested in a STM32F103C8 with UART and USB CDC VCP.
