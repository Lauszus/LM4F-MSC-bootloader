/*
 * Copyright (c) 2012, Mauro Scomparin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Mauro Scomparin nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Mauro Scomparin ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Mauro Scomparin BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File:         LM4F_startup.c
 * Author:       Mauro Scomparin <http://scompoprojects.worpress.com>
 * Version:      1.0.0
 * Description:  LM4F120H5QR startup code
 */

#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

//-----------------------------------------------------------------------------
//               Functions declarations
//-----------------------------------------------------------------------------

// Main should be defined on your main file so it's extern
extern int main(void);
// rst_handler contains the code to run on reset
void ResetISR(void);
// nmi_handler it's the code for an non maskerable interrupt
void NmiSR(void);
// this is just the default handler
void IntDefaultHandler(void);
// this is the code for an hard fault
void FaultISR(unsigned int * hardfault_args);

extern void USB0DeviceIntHandler(void);

//-----------------------------------------------------------------------------
//                 Variables declarations
//-----------------------------------------------------------------------------

// defined by the linker it's the stack top variable (End of RAM)
extern unsigned long _estack;
// defined by the liker, this are just start and end marker for each section
// .text (code)
extern unsigned long _stext;
extern unsigned long _etext;
// .data (data to be copied on RAM)
extern unsigned long _sdata;
extern unsigned long _edata;
// .bss (uninitialized data to set to 0)
extern unsigned long _sbss;
extern unsigned long _ebss;

// NVIC ISR table
// the funny looking void(* myvectors[])(void) basically it's a way to make cc accept an array of function pointers
__attribute__ ((section(".isr_vector")))
void(* myvectors[])(void) = {
// This are the fixed priority interrupts and the stack pointer loaded at startup at R13 (SP).
//                                                       VECTOR N (Check Datasheet)
	(void (*)) &_estack,  // Initial stack pointer          0
	ResetISR,             // Code entry point               1
	NmiSR,                // NMI handler                    2
	FaultISR,             // Hard fault handler             3
	// Configurable priority interruts handler start here
	IntDefaultHandler,    // Memory Management Fault        4
	IntDefaultHandler,    // Bus Fault                      5
	IntDefaultHandler,    // Usage Fault                    6
	0,                    // Reserved                       7
	0,                    // Reserved                       8
	0,                    // Reserved                       9
	0,                    // Reserved                      10
	IntDefaultHandler,    // SV call                       11
	IntDefaultHandler,    // Debug monitor                 12
	0,                    // Reserved                      13
	IntDefaultHandler,    // PendSV                        14
	IntDefaultHandler,    // SysTick                       15
	// Peripherial interrupts start here
	IntDefaultHandler,    // GPIO Port A                   16
	IntDefaultHandler,    // GPIO Port B                   17
	IntDefaultHandler,    // GPIO Port C                   18
	IntDefaultHandler,    // GPIO Port D                   19
	IntDefaultHandler,    // GPIO Port E                   20
	IntDefaultHandler,    // UART 0                        21
	IntDefaultHandler,    // UART 1                        22
	IntDefaultHandler,    // SSI 0                         23
	IntDefaultHandler,    // I2C 0                         24
	0,                    // Reserved                      25
	0,                    // Reserved                      26
	0,                    // Reserved                      27
	0,                    // Reserved                      28
	0,                    // Reserved                      29
	IntDefaultHandler,    // ADC 0 Seq 0                   30
	IntDefaultHandler,    // ADC 0 Seq 1                   31
	IntDefaultHandler,    // ADC 0 Seq 2                   32
	IntDefaultHandler,    // ADC 0 Seq 3                   33
	IntDefaultHandler,    // WDT 0 and 1                   34
	IntDefaultHandler,    // 16/32 bit timer 0 A           35
	IntDefaultHandler,    // 16/32 bit timer 0 B           36
	IntDefaultHandler,    // 16/32 bit timer 1 A           37
	IntDefaultHandler,    // 16/32 bit timer 1 B           38
	IntDefaultHandler,    // 16/32 bit timer 2 A           39
	IntDefaultHandler,    // 16/32 bit timer 2 B           40
	IntDefaultHandler,    // Analog comparator 0           41
	IntDefaultHandler,    // Analog comparator 1           42
	0,                    // Reserved                      43
	IntDefaultHandler,    // System control                44
	IntDefaultHandler,    // Flash + EEPROM control        45
	IntDefaultHandler,    // GPIO Port F                   46
	0,                    // Reserved                      47
	0,                    // Reserved                      48
	IntDefaultHandler,    // UART 2                        49
	IntDefaultHandler,    // SSI 1                         50
	IntDefaultHandler,    // 16/32 bit timer 3 A           51
	IntDefaultHandler,    // 16/32 bit timer 3 B           52
	IntDefaultHandler,    // I2C 1                         53
	0,                    // Reserved                      54
	IntDefaultHandler,    // CAN 0                         55
	0,                    // Reserved                      56
	0,                    // Reserved                      57
	0,                    // Reserved                      58
	IntDefaultHandler,    // Hibernation module            59
	USB0DeviceIntHandler, // USB                           60
	0,                    // Reserved                      61
	IntDefaultHandler,    // UDMA SW                       62
	IntDefaultHandler,    // UDMA Error                    63
	IntDefaultHandler,    // ADC 1 Seq 0                   64
	IntDefaultHandler,    // ADC 1 Seq 1                   65
	IntDefaultHandler,    // ADC 1 Seq 2                   66
	IntDefaultHandler,    // ADC 1 Seq 3                   67
	0,                    // Reserved                      68
	0,                    // Reserved                      69
	0,                    // Reserved                      70
	0,                    // Reserved                      71
	0,                    // Reserved                      72
	IntDefaultHandler,    // SSI 2                         73
	IntDefaultHandler,    // SSI 2                         74
	IntDefaultHandler,    // UART 3                        75
	IntDefaultHandler,    // UART 4                        76
	IntDefaultHandler,    // UART 5                        77
	IntDefaultHandler,    // UART 6                        78
	IntDefaultHandler,    // UART 7                        79
	0,                    // Reserved                      80
	0,                    // Reserved                      81
	0,                    // Reserved                      82
	0,                    // Reserved                      83
	IntDefaultHandler,    // I2C 2                         84
	IntDefaultHandler,    // I2C 4                         85
	IntDefaultHandler,    // 16/32 bit timer 4 A           86
	IntDefaultHandler,    // 16/32 bit timer 4 B           87
	0,                    // Reserved                      88
	0,                    // Reserved                      89
	0,                    // Reserved                      90
	0,                    // Reserved                      91
	0,                    // Reserved                      92
	0,                    // Reserved                      93
	0,                    // Reserved                      94
	0,                    // Reserved                      95
	0,                    // Reserved                      96
	0,                    // Reserved                      97
	0,                    // Reserved                      98
	0,                    // Reserved                      99
	0,                    // Reserved                     100
	0,                    // Reserved                     101
	0,                    // Reserved                     102
	0,                    // Reserved                     103
	0,                    // Reserved                     104
	0,                    // Reserved                     105
	0,                    // Reserved                     106
	0,                    // Reserved                     107
	IntDefaultHandler,    // 16/32 bit timer 5 A          108
	IntDefaultHandler,    // 16/32 bit timer 5 B          109
	IntDefaultHandler,    // 32/64 bit timer 0 A          110
	IntDefaultHandler,    // 32/64 bit timer 0 B          111
	IntDefaultHandler,    // 32/64 bit timer 1 A          112
	IntDefaultHandler,    // 32/64 bit timer 1 B          113
	IntDefaultHandler,    // 32/64 bit timer 2 A          114
	IntDefaultHandler,    // 32/64 bit timer 2 B          115
	IntDefaultHandler,    // 32/64 bit timer 3 A          116
	IntDefaultHandler,    // 32/64 bit timer 3 B          117
	IntDefaultHandler,    // 32/64 bit timer 4 A          118
	IntDefaultHandler,    // 32/64 bit timer 4 B          119
	IntDefaultHandler,    // 32/64 bit timer 5 A          120
	IntDefaultHandler,    // 32/64 bit timer 5 B          121
	IntDefaultHandler,    // System Exception             122
	0,                    // Reserved                     123
	0,                    // Reserved                     124
	0,                    // Reserved                     125
	0,                    // Reserved                     126
	0,                    // Reserved                     127
	0,                    // Reserved                     128
	0,                    // Reserved                     129
	0,                    // Reserved                     130
	0,                    // Reserved                     131
	0,                    // Reserved                     132
	0,                    // Reserved                     133
	0,                    // Reserved                     134
	0,                    // Reserved                     135
	0,                    // Reserved                     136
	0,                    // Reserved                     137
	0,                    // Reserved                     138
	0,                    // Reserved                     139
	0,                    // Reserved                     140
	0,                    // Reserved                     141
	0,                    // Reserved                     142
	0,                    // Reserved                     143
	0,                    // Reserved                     144
	0,                    // Reserved                     145
	0,                    // Reserved                     146
	0,                    // Reserved                     147
	0,                    // Reserved                     148
	0,                    // Reserved                     149
	0,                    // Reserved                     150
	0,                    // Reserved                     151
	0,                    // Reserved                     152
	0,                    // Reserved                     153
	0                     // Reserved                     154
};

// Function implementations

/*
 * System on reset code. NVIC 1
 * Here I prepare the memory for the C compiler
 * The stack pointer should be set at the beginning with the NVIC table already
 * Copy the .data segment from flash into RAM
 * 0 to the .bss segment
 */

void ResetISR() {
	// Copy the .data section pointers to RAM from flash
	// Look at LD manual (Optional Section Attributes)

	// source and destination pointers
	unsigned long *src;
	unsigned long *dest;

	// this should be good!
	src = &_etext;
	dest = &_sdata;

	// this too
	while(dest < &_edata) {
		*dest++ = *src++;
	}

	// now set the .bss segment to 0!
	dest = &_sbss;
	while(dest < &_ebss) {
		*dest++ = 0;
	}

	//
	// Enable the floating-point unit.  This must be done here to handle the
	// case where main() uses floating-point and the function prologue saves
	// floating-point registers (which will fault if floating-point is not
	// enabled).  Any configuration of the floating-point unit using DriverLib
	// APIs must be done here prior to the floating-point unit being enabled.
	//
	// Note that this does not use DriverLib since it might not be included in
	// this project
	//
	HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) | NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);

	// after setting copying .data to ram and "zero-ing" .bss we are good
	// to start the main() method!
	// There you go!
	main();
}

// NMI Exception handler code NVIC 2
void NmiSR() {
	// just loop forever, so if you want to debug the processor it's running
	while (1) {
	}
}

// Hard fault handler code NVIC 3
void FaultISR(unsigned int * hardfault_args)
{
	// just loop forever, so if you want to debug the processor it's running
	while (1) {
	}
}

// Empty handler used as default
void IntDefaultHandler()
{
	// just loop forever, so if you want to debug the processor it's running
	while (1) {
	}
}
