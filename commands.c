
/**
* \file   commands.c
* \author Xianwu Luo
* \date   02-24-2022
*
* \brief  if command matches, coresponding function, and change prompt
* a table connects cmd and function togather
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "header.h"

typedef struct Mode {
    char *p_cmd;
    char *p_pmt;
    void (*p_fun)(void);
}mode;

void call_mode(void)
{
    LOG("switch mode\n");
    return;
}

mode cmd_table[] = {
      {"mode0","\nM0>", call_mode},
      {"mode1","\nM1>", call_mode},
      {"mode2","\nM2>", call_mode},
      {"mode3","\nM3>", call_mode},
      {"mode4","\nM4>", call_mode},
      {"mode5","\nM5>", call_mode},
};

int idx = 0;

#define TOTAL_CMD (sizeof(cmd_table)/sizeof(cmd_table[0]))
/*

*/
bool process_cmd( char * cmd )
{
    int i;
    //LOG("------%s, len=%d\n", cmd, strlen(cmd));
    for( i = 0; i < TOTAL_CMD; i++){
        mode *p_m = &cmd_table[i];
        //LOG("******%s, len=%d\n", p_m->p_cmd, strlen(p_m->p_cmd));
        int x= strcmp( cmd, p_m->p_cmd);
        if(  x == 0 ){
            // found match, call the function
            p_m->p_fun( );
            //UART_write(uart, p_m->p_pmt, strlen(p_m->p_pmt));
            uart_out( p_m->p_pmt );
            idx = i;
            break;
        }
    }

    if( i >= TOTAL_CMD ){
        LOG("invalid input!\n");
        uart_out("invalid command\n\r");
        uart_out(cmd_table[idx].p_pmt);
        return false;
    }
    else
        return true;
}