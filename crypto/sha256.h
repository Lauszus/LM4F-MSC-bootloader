#ifndef __SHA256_H__
#define __SHA256_H__

typedef struct {
    unsigned int h[8];
    unsigned char block[64];
    int blkused;
    unsigned int lenhi, lenlo;
} SHA256_State;
void SHA256_Init(SHA256_State * s);
void SHA256_Bytes(SHA256_State * s, const void *p, int len);
void SHA256_Final(SHA256_State * s, unsigned char *output);
void SHA256_Simple(const void *p, int len, unsigned char *output);

#endif
