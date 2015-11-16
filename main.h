/************************************************************ 
Copyright (C) 1995-2002 Pumpkin, Inc. and its
Licensor(s). Freely distributable.

$Source: C:\\RCS\\d\\salvo\\tut\\tu1\\main.h,v $
$Author: aek $
$Revision: 3.32 $
$Date: 2003-07-19 20:11:27-07 $

Header file for tutorial programs.

************************************************************/
                                                            
/*                                                          */                                                                
/* ===================== PICmicro ========================= */
/*                                                          */                                                                
#if   defined(SYSA) /* HI-TECH PICC         */ \
   || defined(SYSE) /* Microchip MPLAB-C18  */ \
   || defined(SYSF) /* HI-TECH PICC-18      */ \
   || defined(SYSH) /* HI-TECH PICC         */ \
   || defined(SYSP) /* IAR PIC18 C          */


#if   defined(SYSP)
#include <io18c452.h> /* for generic PIC18C452 */
#endif


/* setup which port to use, and initialize it */
#if   defined(SYSA) \
   || defined(SYSE) \
   || defined(SYSF) \
   || defined(SYSP)
#define PORT                        PORTB
#define InitPORT()                  do { PORTB = 0x00; \
                                         TRISB = 0x00; \
                                    } while (0) 
#elif defined(SYSH)
#define PORT                        PORTC
#define InitPORT()                  do { PORTC = 0x00; \
                                         TRISC = 0x00; \
                                    } while (0) 
#endif 


/* when interrupts are used (tu5 & tu6), they need to be    */
/*  appropriately initialized.                              */
#if !defined(USE_INTERRUPTS) 
#define Init()         
#else
#if   defined(SYSA) \
   || defined(SYSF) \
   || defined(SYSH) \
   || defined(SYSP)

/* PICC-18 and IAR PIC18 C use different nomenclature */
#if defined(SYSF)      
#define PS2                         T0PS2
#define PS1                         T0PS1
#define PS0                         T0PS0
#define T0IE                        TMR0IE
#elif defined(SYSP)            
#define PS2                         T0PS2
#define PS1                         T0PS1
#define PS0                         T0PS0
#endif                          

#define Init()                      do { T0CS = 0; \
                                         PSA  = 0; \
                                         PS2  = 1; \
                                         PS1  = 0; \
                                         PS0  = 1; \
                                         T0IE = 1; \
                                    } while (0) 


/*  MPLAB-C18 uses different nomenclature for certain PIC18 */
/*   family members                                         */
#elif  defined(SYSE)        
#if  defined(__18C601)  || defined(__18C658)  || defined(__18C801)  \
 ||  defined(__18C858)  || defined(__18F2220) || defined(__18F2320) \
 ||  defined(__18F2331) || defined(__18F2431) || defined(__18F4220) \
 ||  defined(__18F4320) || defined(__18F4331) || defined(__18F4431)
#define Init()                      do { T0CONbits.T0CS    = 0; \
                                         T0CONbits.T0PS0   = 1; \
                                         T0CONbits.T0PS1   = 0; \
                                         T0CONbits.T0PS2   = 1; \
                                         T0CONbits.T0PS3   = 0; \
                                         INTCONbits.TMR0IE = 1; \
                                    } while (0)
#else
#define Init()                      do { T0CONbits.T0CS    = 0; \
                                         T0CONbits.T0PS0   = 1; \
                                         T0CONbits.T0PS1   = 0; \
                                         T0CONbits.T0PS2   = 1; \
                                         T0CONbits.PSA     = 0; \
                                         INTCONbits.TMR0IE = 1; \
                                    } while (0)
#endif                          

#endif
                           
#endif                     


/*                                                          */                                                                
/* ======================= 8051 =========================== */
/*                                                          */                                                                
#elif defined(SYSI) /* Keil Cx51     */ \
   || defined(SYSM) /* HI-TECH 8051C */ \
   || defined(SYSN) /* Tasking C51   */ 
   
#if   defined(SYSI)
#include <reg51.h>  /* for generic 8051 */
#elif defined(SYSM)
#include <8051.h>   /* for generic 8051 */
#elif defined(SYSN)
#error main.h: Not supported.
#endif

/* Reload values for Timer0 - 5msec interrupts for          */
/*  Oscillator at 11.0592 MHz. This code courtesy Michael   */
/*  Stepanov.                                               */
#define TIMER_H                     238 /* TH0 reload value */
#define TIMER_L                     0   /* TL0 reload value */

/* we'll be outputting to port P1 */
#define PORT                        P1 
#define InitPORT()                  do { PORT = 0x00; } while (0)
#if !defined(USE_INTERRUPTS)
#define Init()                      do { ; } while (0)
#else
#define Init()                      do { TMOD =    0x21; /* TMOD:timer1-mode2 - 8-bit reload,timer0-mode1,16-bit */ \
                                         TH0  = TIMER_H; \
                                         TL0  = TIMER_L; \
                                         PT0  =       1; /* max priority for T0 interrupt */ \
                                         ET0  =       1; /* enable timer 0 interrupt */ \
                                         TR0  =       1; /* start Timer0 */ \
                                    } while (0)
#endif


/*                                                          */                                                                
/* =================== ARClite microRISC ================== */
/*                                                          */                                                                
#elif defined(SYSL)

unsigned char PORTB; 

#if !defined(USE_INTERRUPTS) 
#define Init()                      di()
#else
/* INTENB=1, RET=1, RUN=1, prescalar disabled */
#define Init()                      do { TIMER_CTL = 0x51; \
                                      TIMER_PRESCL =    0; \
                                      TIMER_MAXA   = 40000; \
                                      TIMER_MAXB   = 40000; \
                                      ei(); \
                                    } while (0)
#endif
#define PORT                        PORTB
#define InitPORT()                  do { PORT = 0x00; } while (0)


/*                                                          */                                                                
/* ====================== MSP430 ========================== */
/*                                                          */                                                                
#elif defined(SYSQ) /* IAR MSP430 C              */ \
   || defined(SYSR) /* Archelon Quadravox AQ430  */ \
   || defined(SYSS) /* ImageCraft ICC430         */ \
   || defined(SYSX) /* Rowley CrossStudio MSP430 */

#if   defined(SYSQ)
#include <msp430x14x.h> /* for MSP430F149 */
#elif defined(SYSR)
#include <msp430x14x.h> /* for MSP430F149 */
#elif defined(SYSS)
#include <msp430x14x.h> /* for MSP430F149 */
#elif defined(SYSX)
#endif


#define PORT                        P1OUT
#if !defined(USE_INTERRUPTS)
#define Init()                      do { WDTCTL = WDTPW + WDTHOLD; /* Stop WDT */ \
                                    } while (0)
#else
#define Init()                      do { WDTCTL = WDTPW + WDTHOLD; /* Stop WDT */ \
                                         TACTL  = TASSEL1 + TACLR; /* SMCLK, clear TAR */ \
                                         CCTL0  = CCIE;            /* CCR0 interrupt enabled */ \
                                         CCR0   = 10000; \
                                         TACTL |= MC1;             /* Start Timer_A in continuous mode */ \
                                    } while (0)
#endif
#define InitPORT()                  do { P1DIR |= 0xFF; \
                                         PORT   = 0x00; \
                                    } while (0)  /* P1 is all-output */ 


/*                                                          */                                                                
/* ====================== M68HC11 ========================= */
/*                                                          */                                                                
#elif defined(SYST) /* ImageCraft ICC11 */

#if 0
/* EVB has vectors in RAM -- therefore we set them in       */
/*  Init(). Change these values and/or code below if your   */
/*  target has a different interrupt scheme.                */ 
#define JMP_INSTRUCTION             0x7E    
#define EVB_RTI_VECTOR              0xEB

extern void IntVector(void);
*(char *)EVB_RTI_VECTOR = JMP_INSTRUCTION; 
*(void (**)())(EVB_RTI_VECTOR+1) = intVector; 
#endif /* #if 0 */                                        

#if defined(USE_PORTC)
#define PORT                        PORTC
#else
#define PORT                        PORTB
#endif

#if !defined(USE_INTERRUPTS)
#define Init()    
#else                    
#define Init()                      do { PACTL &= 0b11111100; \
                                         PACTL |= 0b00000010; \
                                         TMSK2 |= 0b01000000; \
                                    } while (0)                     
#endif

#if defined(USE_PORTC)
#define InitPORT()                  do { PIOC &= 0b00001111; \
                                         DDRC  = 0b11111111; \
                                         PORT  = 0x00; \
                                    } while (0)
#else
#define InitPORT()                  do { PORT = 0x00; \
                                    } while (0) /* PORTB is output-only */ 
#endif             


/*                                                          */                                                                
/* ====================== Z8Encore ======================== */
/*                                                          */                                                                
#elif defined(SYSU) /* Zilog Z8Encore Compiler */

/* PORTE is used to force writes to the LED arrays ...      */
/*  only D1 and D4 really show anything useful ...          */
#define PORT                        PGOUT

#if !defined(USE_INTERRUPTS)
#define Init()                      do { PEADDR =  0x01; \
                                         PECTL  =  0x00; \
                                         PGADDR =  0x01; \
                                         PGCTL  =  0x00; \
                                         PEOUT  =  0x00; \
                                         PEOUT |=  0x20; \
                                         PEOUT &= ~0x00; \
                                         PGOUT  =  0x01; \
                                         PEOUT |=  0xC0; \
                                         PEOUT &= ~0xC0; \
                                    } while (0)
#else                                
#define Init()                      do { PEADDR =  0x01; \
                                         PECTL   =  0x00; \
                                         PGADDR  =  0x01; \
                                         PGCTL   =  0x00; \
                                         PEOUT   =  0x00; \
                                         PEOUT  |=  0x20; \
                                         PEOUT  &= ~0x00; \
                                         PGOUT   =  0x01; \
                                         PEOUT  |=  0xC0; \
                                         PEOUT  &= ~0xC0; \
                                         SET_VECTOR(TIMER0, IntVector);\
                                         T0H     =  0x00; \
                                         T0L     =  0x00; \
                                         T0RH    =  0x5A; \
                                         T0RL    =  0x00; \
                                         T0CTL   =  0x99; \
                                         IRQ0E0 &=  0xDF; \
                                         IRQ0E1 |=  0x20; \
                                    } while (0)
#endif                                     


/*                                                          */                                                                
/* ======================= AVR ============================ */
/*                                                          */                                                                
#elif defined(SYSV) /* ImageCraft ICCAVR */ \
   || defined(SYSY) /* AVR-GCC           */ 

#if   defined(SYSV)
#include <io8515v.h> /* for AT90S8515 */
#elif defined(SYSY)
#endif

#define PORT                        PORTB 
#define InitPORT()                  do { DDRB = 0xFF; \
                                         PORT = 0x00; \
                                    } while (0)

#if !defined(USE_INTERRUPTS)
#define Init()                    
#else
#define Init()                      do { TCCR1B = 0x00; /* Stop Timer1 */ \
                                         TCNT1H = 0x00; /* Clear Timer1 */ \
                                         OCR1AH = 0x00; /* Set Compare A to 39 */ \
                                         OCR1AL = 0x27; /* ((4MHz/1024)/39) = 10ms timer */ \
                                         TIMSK  = 0x40; /* Compare A Interrupt enable */ \
                                         TCCR1B = 0x0D; /* Start Timer1 with clk/1024 */ \
                                    } while (0)
#endif
    


/*                                                          */                                                                
/* ===================== TMS320C28x ======================= */
/*                                                          */                                                                
#elif defined(SYSW) /* TI Code Composer Studio 'C2000 */

/* just define an imaginary port called PORTB and write     */
/*  to it ...                                               */
unsigned int PORTB;

/* Initialization of Timer2 is in InitTMR2() in vectors.asm.*/
extern void InitTMR2(void);

#if !defined(USE_INTERRUPTS)
#define Init()    
#else                    
#define Init()                      do { InitTMR2();\
                                    } while (0)
#endif

#define PORT                        PORTB
#define InitPORT()                  do { PORT = 0x00; } while (0)


/*                                                          */                                                                
/* ===================== TMS320C24x ======================= */
/*                                                          */                                                                
#elif defined(SYSAA) /* TI Code Composer */
#include <f2407_c.h> /* for TMS320LF2407A */

/* Initialization of '2407 is in initialize.c.              */
extern void InitLF2407(void);

#if !defined(USE_INTERRUPTS)
#define    Init()                   do { InitLF2407();\
                                    } while (0)
/* since vectors.asm is not compiled conditionally, we need */
/*  a "dummy ISR3" to satisfy its external reference to     */
/*  _ISR3.                                                  */
interrupt void ISR3(void)           { *EVAIFRB = *EVAIFRB & 0x0001; }
#else                    
#define Init()                      do { InitLF2407();\
                                    } while (0)
#endif

/* set GPIO PORT B to all outputs and zero it in one op.    */
#define PORT                        *PBDATDIR                    
#define InitPORT()                  do { PORT = 0xFF00; \
                                    } while (0)                


/*                                                          */                                                                
/* ====================== undefined ======================= */
/*                                                          */                                                                
#else                      
#error Undefined Salvo test system (SYS*). Definition required.


#endif
