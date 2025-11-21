#pragma once

#include <stdio.h>
// #include "CH559.h"
#include "register.h"

#if 1
#define DEBUG(...) printf(__VA_ARGS__);
#else
#define DEBUG(...) (void)0;
#endif

#ifndef SYSTEM_FREQ
#define	SYSTEM_FREQ	48000000
#endif

void	delay_us(unsigned short n)
{
	while (n) 
	{  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
#ifdef	SYSTEM_FREQ
#if		SYSTEM_FREQ >= 14000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 16000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 18000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 20000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 22000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 24000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 26000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 28000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 30000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 32000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 34000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 36000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 38000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 40000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 42000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 44000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 46000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 48000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 50000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 52000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 54000000
		++ SAFE_MOD;
#endif
#if		SYSTEM_FREQ >= 56000000
		++ SAFE_MOD;
#endif
#endif
		--n;
	}
}

void delay_ms(unsigned short n) {
	while (n) {
		delay_us(1000);
		--n;
	}
}

int putchar(int c) {
    while (!TI);
    TI = 0;
    SBUF = c & 0xFF;
    return c;
}

int getchar(void)  {
    while(!RI);
    RI = 0;
    return SBUF;
}

inline void __enter_safe_mode(void) {
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;
}

inline void __exit_safe_mode(void) {
  SAFE_MOD = 0xFF;
}

void __clock_configuration(uint8_t pll_mul, uint8_t fusb_div, uint8_t fsys_div) {
  uint8_t tmp = (fusb_div << 5) | pll_mul;

  __enter_safe_mode();
  PLL_CFG = tmp;
  CLOCK_CFG &= 0b11100000;
  CLOCK_CFG |= fsys_div;
  __exit_safe_mode();
}

void clock_init(void) {
  #if USE_EXTERNAL_OSC
  #error External OSC is not supported.
  #else
  #if SYSTEM_FREQ == 48000000
    __clock_configuration(24, 6, 6);
  #else
  #error The system frequency is not supported.
  #endif
  #endif
}

/*
void initUART0(unsigned long baud, int alt)
{
	unsigned long x;
	if(alt) {
		PORT_CFG |= bP0_OC;
		P0_DIR |= bTXD_;
		P0_PU |= bTXD_ | bRXD_;
		PIN_FUNC |= bUART0_PIN_X;
	}
 	SM0 = 0;
	SM1 = 1;
	SM2 = 0;
	REN = 1;
   //RCLK = 0;
    //TCLK = 0;
    PCON |= SMOD;
    x = (((unsigned long)SYSTEM_FREQ / 8) / baud + 1) / 2;

    TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1;
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;
    TH1 = (256 - x) & 255;
    TR1 = 1;
	TI = 1;
}
*/

void uart0_init(uint32_t baudrate, uint8_t use_alt_pin) {
  if (use_alt_pin) {
    PORT_CFG |= (1 << 0);
    P0_DIR |= (1 << 3);
    P0_PU |= (1 << 3) | (1 << 2);
    PIN_FUNC |= (1 << 4);
  }

  SM0 = 0;
	SM1 = 1;
	SM2 = 0;
	REN = 1;
  T2CON &= ~((1 << 5) | (1 << 4));
  PCON |= (1 << 7);
  TMOD = TMOD & ~((1 << 7) | (1 << 6) | (1 << 4)) | (1 << 5);
  T2MOD |= (1 << 7) | (1 << 5);
  uint32_t x = ((((uint32_t)SYSTEM_FREQ / 8) / baudrate + 1) / 2);
  TH1 = (256 - x) & 0xFF;
  TR1 = 1;
	TI = 1;
}
