/**
* \file   header.h
* \author Xianwu Luo
* \date   02-24-2022
*
* \brief  declare all public function 
*/
extern bool uart_out( char *str );
extern bool uart_out_c( char ch );
extern bool process_cmd( char * cmd );



#if TI
#define LOG
#define UART_HANDLE UART_HANDLE
#define UART_INVALID NULL
#else
#define UART_HANDLE int
#define UART_INVALID (-1)
#define UART_read   read
#define UART_write  write
#define LOG printf
#endif