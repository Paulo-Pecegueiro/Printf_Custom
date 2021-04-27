/*
 * printf.c
 *
 *  Created on: Apr 24, 2021
 *      Author: paulo
 */
#include "../Printf_Custom/printf_custom.h"


static uint8_t convert(char* buffer, uint8_t index, unsigned int num, int base);        //Convert integer number into octal, hex, etc.



/**
  * @brief  Prints some data on a pre-set peripheral
  * @note   Do not forget to set your peripheral and declare what one are you using in printf_custom.h defines
  *
  * @parameters
  *		    ""    prints a string inside ""
  *		    %c    prints as character
  *			%s    prints as string
  *			%d    prints as signed integer/decimal number
  *			%i    prints as signed integer/decimal number
  *			%u    prints as unsigned integer/decimal number
  *			%b    prints as binary number
  *			%o    prints as octal number
  *			%x    prints as hexadecimal number
  *			%f    prints as float number with 6 decimal digits
  *			%.nf  prints as float number with n decimal digits
  *
  * @return 1 if the peripheral is busy, 0 if the data have been printed
  *
  */

uint8_t printf_custom(char* format,...)
{
#ifdef  UART_PRINTF
	if(UART_PORT.gState == HAL_UART_STATE_BUSY_TX){
		return 1;
	}
#endif
#ifdef USB_PRINTF
	USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
	if (hcdc->TxState != 0){
		return USBD_BUSY;
	}
#endif

    char *traverse;
    char *s;
    char c;
    int i, j;
    unsigned int ui;
    double f;
    uint8_t index=0;
    char buffer[MAX_CHARACTERS]={0}; 				//max number of characters that can be printed per printf_cdc call
    va_list arg;
    va_start(arg, format);

    for(traverse = format; *traverse != '\0'; traverse++)
    {
        while(*traverse!='%')
        {
        	if(*traverse =='\0')
        		break;

            buffer[index] = *traverse;
            traverse++;
            index++;
        }
        if(*traverse !='\0')
        	traverse++;

        switch(*traverse)
        {
        	case 'b':
        		ui = va_arg(arg,unsigned int);
        		index += convert(buffer, index, ui, 2);
        		break;

            case 'c' :
            	c = va_arg(arg,int);
            	buffer[index] = c;
            	index++;
                break;

            case 'd' :
            	i = va_arg(arg,int);
        		if(i<0)
        		{
        			i *= -1;
        			buffer[index] = '-';
        			index++;
        		}
        		index += convert(buffer, index, i, 10);
                break;

            case 'i' :
            	i = va_arg(arg,int);
        		if(i<0)
        		{
        			i *= -1;
        			buffer[index] = '-';
        			index++;
        		}
        		index += convert(buffer, index, i, 10);
                break;

            case 'u' :
            	ui = va_arg(arg,unsigned int);
                index += convert(buffer, index, ui, 10);
                break;

            case 'o':
            	ui = va_arg(arg,unsigned int);
            	index += convert(buffer, index, ui, 8);
                break;

            case 's':
            	s = va_arg(arg,char *);
            	while(*s!='\0')
            	{
            		buffer[index] = *s;
            		s++;
            		index++;
            	}
                break;

            case 'x':
            	ui = va_arg(arg,unsigned int);
            	index += convert(buffer, index, ui, 16);
                break;

            case 'f':
            	f = va_arg(arg,double);
            	i = (int)f;
            	f = (double)(f - i);
            	f*=1000000;
            	if(f<0) f*=-1;
            	j = (int)f;

            	if(j<0) j*=-1;

            	if((f-j)>0.5) j++;

            	if(i<0)
        		{
        			i *= -1;
        			buffer[index] = '-';
        			index++;
        		}
        		index += convert(buffer, index, i, 10);
        		buffer[index] = '.';
        		index++;
        		index += convert(buffer, index, j, 10);
            	break;

            case'.':
            	traverse++;
            	c = *traverse; //get the number of decimals
            	for(ui=49; ui<58; ui++){
            		if(c==ui)
            			break;
            	}
            	ui-=48;
            	traverse++;	//get the 'f' indicator
            	if(*traverse == 'f'){
                	f = va_arg(arg,double);
                	i = (int)f;
                	f = (double)(f - i);
                	while(ui--){
                		f*=10;
                	}
                	if(f<0) f*=-1;
                	j = (int)f;

                	if(j<0) j*=-1;

                	if((f-j)>0.5) j++;

                	if(i<0)
            		{
            			i *= -1;
            			buffer[index] = '-';
            			index++;
            		}
            		index += convert(buffer, index, i, 10);
            		buffer[index] = '.';
            		index++;
            		index += convert(buffer, index, j, 10);
            	}
            	break;

        }
    	if(*traverse =='\0')
    		break;
    }

#ifdef  UART_PRINTF
    return HAL_UART_Transmit(&UART_PORT, ( uint8_t * )buffer, index, 0xFFFF );
#endif

#ifdef USB_PRINTF
    return CDC_Transmit_FS((uint8_t*)buffer, index);
#endif
}





static uint8_t convert(char* buffer, uint8_t index, unsigned int num, int base)
{
	static char buf[32]; 			// The max number of characters when representing a number is a 32bit number in binary
    static char Representation[]= "0123456789ABCDEF";
    char *ptr;
    uint8_t i=0;
    uint8_t j=0; 					//used to return the number of characters included in the buffer.
    uint8_t k=32;   				//just for control the number of interactions.

    ptr = &buf[31];					//set the pointer address to 32th position of buf

    do
    {
        *ptr = Representation[num%base];
        num /= base;
        ptr--;
        k--;
    }while(num != 0);


    for(i=k; i<32; i++)
    {
  		buffer[j+index] = buf[i];
    	j++;
    }
    return(j);
}

