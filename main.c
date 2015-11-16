#include "main.h"
#include "salvo.h"



_OSLabel(TaskA_1)
_OSLabel(TaskB_1)


void TaskA( void )
{
    for (;;){
		P1=0xFF;	        //P1-ON 
    OS_Yield(TaskA_1);//Again TaskA eligible 
    }
		
}

void TaskB( void )
{
    for (;;){
    P1=0x00;          //P1-OFF
		OS_Yield(TaskB_1);//Again TaskB eligible 
    }
}




void main(){
	
Init();      //Initialize 8051 BSP 

    OSInit();//Initialize OS predefined task
    /*OSCreateTask(Task_Name, TCB, Priority);*/
    OSCreateTask(TaskA, OSTCBP(1), 1);
    OSCreateTask(TaskB, OSTCBP(2), 1);


    for (;;)
        OSSched();//  goes to scheduling 
	
}
