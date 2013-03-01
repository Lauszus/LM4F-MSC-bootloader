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

#include "crypto.h"
#include "rsa.h"
#include "common.h"

#ifdef DEBUGUART
#include "utils/uartstdio.h"
#endif

char checkCryptoSignature()
{

#ifdef DEBUGUART
	UARTprintf("Checking digital signature ...\n\n");
#endif

	unsigned char *header = (unsigned char *)UPLOAD_START;
	if (header[0] != 'Z' || header[1] != '-') {
#ifdef DEBUGUART
	UARTprintf("Magic not found.\n\n");
#endif
		return 0;
	}

	unsigned int code_size = header[2] + (header[3] << 8) + (header[4] << 16) + (header[5] << 24);
	unsigned int sign_size = header[6] + (header[7] << 8);

	if (sign_size != 512) {
#ifdef DEBUGUART
	UARTprintf("Signature does not have 512 bytes.\n\n");
#endif
		return 0;
	}

	int check = RSAVerifySignature((unsigned char *)UPLOAD_CODE_START, code_size, (unsigned char *)(UPLOAD_CODE_START + code_size), sign_size);
	if (0 == check) {
#ifdef DEBUGUART
		UARTprintf("Digital signature OK\n\n");
#endif
		return 1;
	} else {
#ifdef DEBUGUART
		UARTprintf("Digital signature BAD (error %d)\n\n", check);
#endif
		return 0;
	}
}
