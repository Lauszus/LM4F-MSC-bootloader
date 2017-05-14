/*
 * Copyright (c) 2013 Pavol Rusnak <stick@gk2.sk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#define BTN_GPIO_PERIPH (SYSCTL_PERIPH_GPIOF)
#define BTN_GPIO_BASE   (GPIO_PORTF_BASE)
#define BTN_LEFT        (GPIO_PIN_4)
#define BTN_RIGHT       (GPIO_PIN_0)

#define LED_GPIO_PERIPH (SYSCTL_PERIPH_GPIOF)
#define LED_GPIO_BASE   (GPIO_PORTF_BASE)
#define LED_RED         (GPIO_PIN_1)
#define LED_BLUE        (GPIO_PIN_2)
#define LED_GREEN       (GPIO_PIN_3)

#define UPLOAD_START  (0x6000)
#define UPLOAD_LENGTH (0x40000 - UPLOAD_START)

#ifdef CRYPTO
#define UPLOAD_HEADER_LENGTH (32)
#define UPLOAD_CODE_START (UPLOAD_START + UPLOAD_HEADER_LENGTH)
#else
#define UPLOAD_CODE_START (UPLOAD_START)
#endif

#endif
