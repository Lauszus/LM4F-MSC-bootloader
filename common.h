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

#define BTN_LEFT    (GPIO_PIN_4)
#define BTN_RIGHT   (GPIO_PIN_0)
#define LED_RED     (GPIO_PIN_1)
#define LED_BLUE    (GPIO_PIN_2)
#define LED_GREEN   (GPIO_PIN_3)

#define USER_PROGRAM_START   (0x4000)
#define USER_PROGRAM_LENGTH (0x3c000)

#ifdef CRYPTO

#define USER_PROGRAM_SIGNATURE_LENGTH (512)
#define USER_PROGRAM_ENTRY (USER_PROGRAM_START + USER_PROGRAM_SIGNATURE_LENGTH)

#else

#define USER_PROGRAM_ENTRY (USER_PROGRAM_START)

#endif

#endif
