# Multitasking-using-salvo-RTOS-for-8051-

Microcontroller:AT89C52(8051 MCU)         
      IDE: uVersion V5.15     
      C Compiler: Keil C Compiler V9.54

        I have created two tasks such as TaskA and TaskB. TaskA is going to control Port1-ON and TaskB is going to control Port1-OFF.After that TaskA is again triggered by kernel and so on. TaskA and TaskB has been controlled by Round robin scheduling via kernel.
