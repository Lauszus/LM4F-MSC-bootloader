#include "rsa.h"
#include "imath.h"
#include "sha256.h"

extern unsigned char RSAKey[33 + 512 + 5];

// RSAKey structure (total 512 bytes):
//
//  signkey_start [33 bytes]
//  modulus [512 bytes]
//  signkey_end [5 bytes]

static const unsigned char signkey_start[33] = {
    0x30, 0x82, 0x02, 0x22, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,
    0x01, 0x05, 0x00, 0x03, 0x82, 0x02, 0x0F, 0x00, 0x30, 0x82, 0x02, 0x0A, 0x02, 0x82, 0x02, 0x01,
    0x00,
};

static const unsigned char signkey_end[5] = {
    0x02, 0x03, 0x01, 0x00, 0x01,
};

// Signature structure (total 511 bytes):
//
// 0x01 [1 byte]
// 0xFF [458 bytes]
// asn1_stuff [20 bytes]
// SHA256 sum [32 bytes]

static const unsigned char asn1_stuff[20] = {
    0x00, 0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48,
    0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20,
};

int RSAVerifySignature(unsigned char *data, int datalen, unsigned char *sig, int siglen)
{
    mpz_t in, out, modulus;
    unsigned char hash[32];
    unsigned char result[512];
    int i, reslen;

    // load key
    for (i = 0; i < sizeof(signkey_start); i++) { // check beginning
        if (RSAKey[i] != signkey_start[i]) {
            return 1;
        }
    }

    for (i = 0; i < sizeof(signkey_end); i++) { // check end
        if (RSAKey[sizeof(RSAKey) - sizeof(signkey_end) + i] != signkey_end[i]) {
            return 2;
        }
    }

    mp_int_init(&modulus);
    if (MP_OK != mp_int_read_unsigned(&modulus, RSAKey + sizeof(signkey_start), 512)) { // load modulus
        return 3;
    }

    mp_int_init(&in);
    if (MP_OK != mp_int_read_unsigned(&in, sig, siglen)) { // load signature
        return 4;
    }

    mp_int_init(&out);
    mp_int_exptmod_evalue(&in, 0x010001, &modulus, &out); // exponent is 65537 aka 0x010001 - checked in signkey_end
    mp_int_clear(&in);
    mp_int_clear(&modulus);
    reslen = mp_int_unsigned_len(&out);
    if (reslen != 511) {
        mp_int_clear(&out);
        return 5;
    }
    mp_int_to_binary(&out, result, sizeof(result));
    mp_int_clear(&out);

    if (result[0] != 0x01) {
        return 6;
    }
    for (i = 1; i < 459; i++) {
        if (result[i] != 0xFF) {
            return 7;
        }
    }
    for (i = 0; i < 20; i++) {
        if (result[i + 459] != asn1_stuff[i]) {
            return 8;
        }
    }

    SHA256_Simple(data, datalen, hash);
    for (i = 0; i < 32; i++) {
        if (result[i + 479] != hash[i]) {
            return 9;
        }
    }

    return 0;
}
