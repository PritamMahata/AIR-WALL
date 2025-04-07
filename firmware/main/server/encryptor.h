#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <Arduino.h>
#include <mbedtls/aes.h>
#include <mbedtls/base64.h>

String encryptAES(const String &plainText, const String &key);
String decryptAES(const String &cipherBase64, const String &key);

#endif // ENCRYPTOR_H