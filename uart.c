
/**
* \file   uart.c
* \author Xianwu Luo
* \date   02-23-2022
*
* \brief  get input command from uart, 
*         process the input cmd
*/
 
 
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdbool.h>
#include <string.h>

#include "header.h"
 
#define DEV_NAME "/dev/ttyUSB0"
#define MAX_INPUT 128

#ifdef TI
#warning  build for TI
#else
#warning build for Linux
#endif
 
UART_HANDLE fd = 0;   //file descriptor of the device

UART_HANDLE uart_init( char *dev_name )
{
    char cmd_line[128];
    sprintf( cmd_line, "stty -F %s 115200 min 1 -icanon -echo raw", DEV_NAME);
    LOG("%s\n", cmd_line);

    system( cmd_line);
 
    UART_HANDLE f = open( DEV_NAME, O_RDWR );
    if(f == UART_INVALID)
    {
        printf("Error while opening the device\n");
    }
    return f;
}
 
int serial_getc_non_block(int fd, unsigned char * p_char )
{
    long flag = fcntl(fd, F_GETFL, 0 );
    flag |=  O_NONBLOCK;
    fcntl(fd,F_SETFL,flag);
 
    int rc = UART_read( fd, p_char, 1);
 
    flag &=  ~O_NONBLOCK;
    fcntl(fd,F_SETFL,flag);
 
    return rc;
}

/*
 * read a line from uart
 */
int UART_readline( UART_HANDLE fd, char *p_buf )
{
    char *p = p_buf;
    int i;
    for( i = 0; i < MAX_INPUT - 1;  ){ // save 1 byte for termination
        //UART_read(uart, &p, 1);
        int rc = UART_read( fd, p, 1);  // wait until get
        //LOG("0x%x(%c)\n",*p, *p);
        if( rc != 1) {
            uart_out( "read uart error!\n" );
            return 0;
        }
        //echo char back
        if( *p != '\b'){
            if( *p == '\r' || *p == '\n' ){ 
                uart_out_c('\r');
                uart_out_c('\n');
            }
            else{
                uart_out_c(*p);
            }
        }
        
        if( (*p == '\r') || (*p == '\n') ){
            *p = '\0'; // \r,\n removed
            break;
        }
        else if ( *p=='\b' ) { // backspace
            if( i > 0 ){
                uart_out_c('\b');
                uart_out_c(' ');
                uart_out_c('\b');
                 i--;   
                 p--;
            }
        }
        else {
            i++;
            p++;
        }
 
    }

    if( i >= MAX_INPUT )
        return 0;
    else
        return i+1; // number of char received
}


bool uart_out_c( char byte )
{
    int num = UART_write( fd, &byte, 1 );
    return ( num == 1 ? true : false );
}

bool uart_out( char *str )
{
    int num = UART_write( fd, str, strlen(str));
    return ( num == -1 ? false: true );
}
 

 
int main()
{
    char buf[MAX_INPUT];
 
    fd = uart_init( DEV_NAME );
    if( fd == UART_INVALID ){
        LOG("open %s failed!\n", DEV_NAME);
        return -1;
    }

    while(1) {
        if( UART_readline( fd, buf ) != 0 ){
            process_cmd( buf );
        }

    }
  
   return 0;
 
}

