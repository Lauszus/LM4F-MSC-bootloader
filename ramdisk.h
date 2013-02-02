/*
 * Copyright 2012 Andrzej Surowiec
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
 * File:        ramdisk.h
 * Author:      Andrzej Surowiec <emeryth@gmail.com>
 * Version:     1.0
 * Decription:  Mass storage filesystem driver
 *
 */

#ifndef __RAMDISK_H__
#define __RAMDISK_H__

#define USER_PROGRAM_START  0x4000
#define USER_PROGRAM_LENGTH 0x3c000

extern void *massStorageOpen(unsigned long drive);
extern void massStorageClose(void *drive);
extern unsigned long massStorageRead(void *drive, unsigned char *data,unsigned long blockNumber,unsigned long numberOfBlocks);
extern unsigned long massStorageWrite(void *drive, unsigned char *data,unsigned long blockNumber,unsigned long numberOfBlocks);
extern unsigned long massStorageNumBlocks(void *drive);

#endif
