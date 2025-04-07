#include "encryptor.h"

static void aes_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input, output);
    mbedtls_aes_free(&aes);
}

static void aes_decrypt(const uint8_t *key, const uint8_t *input, uint8_t *output) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, key, 128);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, input, output);
    mbedtls_aes_free(&aes);
}

String encryptAES(const String &plainText, const String &key) {
    uint8_t encrypted[16];
    uint8_t padded[16] = {0};
    strncpy((char*)padded, plainText.c_str(), 16);
    aes_encrypt((const uint8_t *)key.c_str(), padded, encrypted);

    size_t olen;
    unsigned char base64[32];
    mbedtls_base64_encode(base64, sizeof(base64), &olen, encrypted, sizeof(encrypted));

    return String((char*)base64);
}

String decryptAES(const String &cipherBase64, const String &key) {
    uint8_t decrypted[16];
    uint8_t decoded[16];
    size_t olen;

    mbedtls_base64_decode(decoded, sizeof(decoded), &olen, (const uint8_t *)cipherBase64.c_str(), cipherBase64.length());
    aes_decrypt((const uint8_t *)key.c_str(), decoded, decrypted);

    return String((char*)decrypted);
}