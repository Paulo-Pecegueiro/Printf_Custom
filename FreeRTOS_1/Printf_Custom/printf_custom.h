/*
 * printf.h
 *
 *  Created on: Apr 24, 2021
 *      Author: paulo
 */

#ifndef PRINTF_CUSTOM_H_
#define PRINTF_CUSTOM_H_
#include "stdarg.h"

#define USB_PRINTF 			// UART_PRINTF
#define MAX_CHARACTERS 128		//Max number of characters that can be printed, changing will impact in RAM consumption

#ifdef UART_PRINTF
#include "usart.h"
#define UART_PORT huart1 		//Choose your UART Port
UART_HandleTypeDef huart1;
#endif

#ifdef USB_PRINTF
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
USBD_HandleTypeDef hUsbDeviceFS;
#endif

uint8_t printf_custom(char* format,...);
#endif /* PRINTF_CUSTOM_H_ */
