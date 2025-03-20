#include <Arduino.h>
#include <mbedtls/aes.h>

#define TAMANHO 16
#define BLOCOS 3

// Chave AES de 128 bits (16 bytes)
const uint8_t chave_aes[TAMANHO] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F' };

// Vetor de Inicialização (IV) de 16 bytes
const uint8_t iv_original[TAMANHO] = { 'E', 'S', 'P', '3', '2', '_', 'I', 'V', '_', 'V', 'E', 'C', 'T', 'O', 'R', '!' };

// Função para imprimir os dados em bits
void imprimirBits(const uint8_t *dados, size_t tamanho) {
    for (size_t i = 0; i < tamanho; i++) {
        for (int b = 7; b >= 0; b--) {
            Serial.print((dados[i] >> b) & 1);
        }
        Serial.print(" ");
    }
    Serial.println();
}

// Função para imprimir dados em hexadecimal
void imprimirHex(const uint8_t *dados, size_t tamanho) {
    for (int i = 0; i < tamanho; i++) {
        Serial.printf("%02X ", dados[i]);
    }
    Serial.println();
}

// Função para criptografar usando AES-CBC (com IV)
void criptografarAES_CBC(const uint8_t *entrada, uint8_t *saida, size_t tamanho, uint8_t *iv) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, chave_aes, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, tamanho, iv, entrada, saida);
    mbedtls_aes_free(&aes);
}

// Função para descriptografar usando AES-CBC (com IV)
void descriptografarAES_CBC(const uint8_t *entrada, uint8_t *saida, size_t tamanho, uint8_t *iv) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, chave_aes, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, tamanho, iv, entrada, saida);
    mbedtls_aes_free(&aes);
}

// Função para criptografar usando AES-ECB (sem IV)
void criptografarAES_ECB(const uint8_t *entrada, uint8_t *saida, size_t tamanho) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, chave_aes, 128);
    
    // ECB cripta cada bloco independentemente
    for (size_t i = 0; i < tamanho; i += 16) {
        mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, &entrada[i], &saida[i]);
    }
    
    mbedtls_aes_free(&aes);
}

// Função para descriptografar usando AES-ECB (sem IV)
void descriptografarAES_ECB(const uint8_t *entrada, uint8_t *saida, size_t tamanho) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, chave_aes, 128);
    
    // ECB descripta cada bloco independentemente
    for (size_t i = 0; i < tamanho; i += 16) {
        mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, &entrada[i], &saida[i]);
    }
    
    mbedtls_aes_free(&aes);
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Teste: Texto com padrões repetitivos
    Serial.println("\n=== TESTE: CRIPTOGRAFANDO TEXTO COM PADRÕES REPETITIVOS ===");
    
    // Criamos um texto com padrões repetitivos (3 blocos iguais)
    uint8_t texto_padrao[TAMANHO * BLOCOS];
    // uint8_t padrao[TAMANHO] = { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A' };
    uint8_t padrao[TAMANHO] = { 'S', 'E', 'N', 'H', 'A', 'L', 'E', 'G', 'A', 'L', '1', '2', '3', '4', '5', '6' };
    
    for (int i = 0; i < BLOCOS; i++) {
        memcpy(&texto_padrao[i * TAMANHO], padrao, TAMANHO);
    }
    
    Serial.println("\nTexto padrão (3 blocos idênticos):");
    Serial.write(texto_padrao, TAMANHO * BLOCOS);
    Serial.println();
    
    // Buffers para criptografia e descriptografia
    uint8_t texto_criptografado_ecb[TAMANHO * BLOCOS];
    uint8_t texto_criptografado_cbc[TAMANHO * BLOCOS];
    uint8_t texto_descriptografado_ecb[TAMANHO * BLOCOS];
    uint8_t texto_descriptografado_cbc[TAMANHO * BLOCOS];
    
    // Cópia do IV
    uint8_t iv_cripto[TAMANHO], iv_decripto[TAMANHO];
    
    // Criptografia ECB (sem IV)
    criptografarAES_ECB(texto_padrao, texto_criptografado_ecb, TAMANHO * BLOCOS);
    Serial.println("\nTexto criptografado no modo ECB - Electronic Codebook (sem IV):");
    imprimirHex(texto_criptografado_ecb, TAMANHO * BLOCOS);
    
    // Descriptografia ECB
    descriptografarAES_ECB(texto_criptografado_ecb, texto_descriptografado_ecb, TAMANHO * BLOCOS);
    Serial.println("\nTexto descriptografado no modo ECB - Electronic Codebook:");
    Serial.write(texto_descriptografado_ecb, TAMANHO * BLOCOS);
    Serial.println();
    
    // Criptografia CBC (com IV)
    memcpy(iv_cripto, iv_original, TAMANHO);
    criptografarAES_CBC(texto_padrao, texto_criptografado_cbc, TAMANHO * BLOCOS, iv_cripto);
    Serial.println("\nTexto criptografado no modo CBC - Cipher Block Chaining (com IV):");
    imprimirHex(texto_criptografado_cbc, TAMANHO * BLOCOS);
    
    // Descriptografia CBC
    memcpy(iv_decripto, iv_original, TAMANHO);
    descriptografarAES_CBC(texto_criptografado_cbc, texto_descriptografado_cbc, TAMANHO * BLOCOS, iv_decripto);
    Serial.println("\nTexto descriptografado no modo CBC - Cipher Block Chaining:");
    Serial.write(texto_descriptografado_cbc, TAMANHO * BLOCOS);
    Serial.println();
    
    // Análise de padrões nos blocos criptografados
    Serial.println("\n=== ANÁLISE DE PADRÕES ===");
    
    // No ECB, blocos iguais resultam em criptogramas iguais
    Serial.println("\nBlocos criptografados no modo ECB (devem ser iguais):");
    for (int i = 0; i < BLOCOS; i++) {
        Serial.print("Bloco ");
        Serial.print(i + 1);
        Serial.print(": ");
        imprimirHex(&texto_criptografado_ecb[i * TAMANHO], TAMANHO);
    }
    
    // No CBC, blocos iguais resultam em criptogramas diferentes
    Serial.println("\nBlocos criptografados no modo CBC (devem ser diferentes):");
    for (int i = 0; i < BLOCOS; i++) {
        Serial.print("Bloco ");
        Serial.print(i + 1);
        Serial.print(": ");
        imprimirHex(&texto_criptografado_cbc[i * TAMANHO], TAMANHO);
    }
    
    // Conclusão
    Serial.println("\n=== CONCLUSÃO ===");
    Serial.println("\nO modo ECB (sem IV) revela padrões no texto cifrado quando blocos idênticos são criptografados.");
    Serial.println("O modo CBC (com IV) esconde padrões, pois cada bloco criptografado depende do bloco anterior.");
    Serial.println("\nIsso demonstra a importância do uso do IV para a segurança da criptografia em casos reais.");
}

void loop() {
    // Nada aqui, apenas executamos o teste na inicialização
}