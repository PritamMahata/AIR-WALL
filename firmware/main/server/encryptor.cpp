#include "encryptor.h"
#include <vector>

static void aes_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output)
{
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input, output);
    mbedtls_aes_free(&aes);
}

static void aes_decrypt(const uint8_t *key, const uint8_t *input, uint8_t *output)
{
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, key, 128);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, input, output);
    mbedtls_aes_free(&aes);
}

String encryptAES(const String &plainText, const String &key)
{
    size_t len = plainText.length();
    size_t paddedLen = ((len + 15) / 16) * 16; // pad to multiple of 16

    std::vector<uint8_t> input(paddedLen, 0);
    memcpy(input.data(), plainText.c_str(), len);

    std::vector<uint8_t> encrypted(paddedLen);

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, (const uint8_t *)key.c_str(), 128);

    for (size_t i = 0; i < paddedLen; i += 16)
    {
        mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input.data() + i, encrypted.data() + i);
    }

    mbedtls_aes_free(&aes);

    // Base64 encode
    size_t olen;
    std::vector<uint8_t> base64((paddedLen * 4 / 3) + 4);
    mbedtls_base64_encode(base64.data(), base64.size(), &olen, encrypted.data(), paddedLen);

    return String((char *)base64.data());
}

String decryptAES(const String &cipherBase64, const String &key)
{
    std::vector<uint8_t> decoded(cipherBase64.length());
    size_t decodedLen;

    if (mbedtls_base64_decode(decoded.data(), decoded.size(), &decodedLen,
                              (const uint8_t *)cipherBase64.c_str(), cipherBase64.length()) != 0)
    {
        return "Base64 decode error";
    }

    decoded.resize(decodedLen);
    std::vector<uint8_t> decrypted(decodedLen, 0);

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, (const uint8_t *)key.c_str(), 128);

    for (size_t i = 0; i < decodedLen; i += 16)
    {
        mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, decoded.data() + i, decrypted.data() + i);
    }

    mbedtls_aes_free(&aes);

    // Ensure null-termination
    decrypted.push_back(0);

    return String((char *)decrypted.data());
}
