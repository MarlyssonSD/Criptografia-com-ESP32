#include <Arduino.h>
#include <mbedtls/aes.h>

#define TAMANHO 16
// Chave AES de 128 bits (16 bytes)
const uint8_t chave_aes[TAMANHO] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F' };

// Vetor de Inicialização (IV) de 16 bytes
const uint8_t iv_original[TAMANHO] = { 'E', 'S', 'P', '3', '2', '_', 'I', 'V', '_', 'V', 'E', 'C', 'T', 'O', 'R', '!' };

void criptografarAES(const uint8_t *entrada, uint8_t *saida, size_t tamanho, uint8_t *iv) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, chave_aes, 128);

    // Criptografa os blocos de 16 bytes
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, tamanho, iv, entrada, saida);
    
    mbedtls_aes_free(&aes);
}

void descriptografarAES(const uint8_t *entrada, uint8_t *saida, size_t tamanho, uint8_t *iv) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, chave_aes, 128);

    // Descriptografa os blocos de 16 bytes
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, tamanho, iv, entrada, saida);
    
    mbedtls_aes_free(&aes);
}

void setup() {
    Serial.begin(115200);

    // Definir um texto de 16 bytes (sem \0)
    uint8_t texto_original[16] = { 'M', 'e', 'n', 's', 'a', 'g', 'e', 'm', ' ', 'S', 'e', 'c', 'r', 'e', 't', 'a' };
    uint8_t texto_criptografado[16];
    uint8_t texto_descriptografado[16];

    // Criar cópias do IV para não ser modificado
    uint8_t iv_para_cripto[16], iv_para_decripto[16];
    memcpy(iv_para_cripto, iv_original, 16);
    memcpy(iv_para_decripto, iv_original, 16);

    Serial.println("Texto original:");
    Serial.write(texto_original, 16);
    Serial.println();

    // Criptografia
    criptografarAES(texto_original, texto_criptografado, sizeof(texto_original), iv_para_cripto);

    Serial.println("Texto criptografado:");
    for (int i = 0; i < 16; i++) {
        Serial.printf("%02X ", texto_criptografado[i]); // Imprime em formato hexadecimal
    }
    Serial.println();

    // Descriptografia
    descriptografarAES(texto_criptografado, texto_descriptografado, sizeof(texto_criptografado), iv_para_decripto);

    Serial.println("Texto descriptografado:");
    Serial.write(texto_descriptografado, 16);
    Serial.println();
}

void loop() {
    // Nada aqui, apenas rodamos a criptografia na inicialização
}
