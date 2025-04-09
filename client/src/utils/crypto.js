import CryptoJS from 'crypto-js';

const AES_KEY = CryptoJS.enc.Utf8.parse("1234567890123456");

export function decryptAES(base64Encrypted) {
  const decrypted = CryptoJS.AES.decrypt(base64Encrypted, AES_KEY, {
    mode: CryptoJS.mode.ECB, // 👈 Match ESP32's mode
    padding: CryptoJS.pad.Pkcs7,
  });
  return decrypted.toString(CryptoJS.enc.Utf8);
}
