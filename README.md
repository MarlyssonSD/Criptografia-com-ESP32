# Criptografia AES no ESP32

Este projeto demonstra a implementação de criptografia AES-128 usando a biblioteca **mbedtls** no ESP32. O código criptografa e descriptografa uma mensagem utilizando o algoritmo AES em **modo CBC** (Cipher Block Chaining), uma técnica que aumenta a segurança da criptografia.

## 📦 **Bibliotecas Necessárias**

- **mbedtls**: A biblioteca mbedtls fornece funções para implementar criptografia no ESP32. Ela é usada aqui para a implementação do AES.

### Como instalar a biblioteca mbedtls:
1. A biblioteca **mbedtls** já vem incluída no framework do ESP32, então você não precisa instalar nada separadamente.
2. No entanto, caso precise de outra versão ou precise de recursos extras, você pode instalar via **Library Manager** na IDE do Arduino.

## 💻 **Placas Compatíveis**

Este projeto foi desenvolvido para ser executado na placa **ESP32 Dev Module**. Para utilizá-lo, siga os passos abaixo para configurar a IDE do Arduino.

### Como configurar a placa ESP32:
1. Abra a **IDE do Arduino**.
2. Vá até **Ferramentas > Placa > Gerenciador de Placas**.
3. Pesquise por **ESP32** e instale a placa **"ESP32 by Espressif Systems"**.
4. Selecione a placa **ESP32 Dev Module** em **Ferramentas > Placa**.

## 🛠️ **Requisitos de Software**

- **IDE Arduino**: A IDE de desenvolvimento para programar o ESP32.
  - [Baixe a IDE Arduino](https://www.arduino.cc/en/software)
  
- **Drivers do ESP32**: Se necessário, instale os drivers da sua placa ESP32.
  - [Drivers ESP32](https://github.com/espressif/esptool)

## 🚀 **Como Rodar o Projeto**

### 1. Instale a IDE do Arduino e configure a placa ESP32
   - Siga as etapas de configuração da IDE mencionadas acima para configurar o ESP32 na sua IDE Arduino.

### 2. Baixe o código-fonte
   - Clone ou baixe este repositório para o seu computador.
   
### 3. Abra o código na IDE do Arduino
   - Abra o arquivo `.ino` na IDE do Arduino.

### 4. Selecione a porta e a placa
   - Conecte sua placa **ESP32** ao computador via USB.
   - Em **Ferramentas > Porta**, selecione a porta correta à qual o seu ESP32 está conectado.
   - Em **Ferramentas > Placa**, selecione **"ESP32 Dev Module"**.

### 5. Faça o upload do código
   - Clique em **Upload** na IDE do Arduino para carregar o código no ESP32.

### 6. Acompanhe a saída
   - Abra o **Monitor Serial** (115200 bauds) para ver o texto criptografado e descriptografado.

## 📝 **Estrutura do Código**

O código realiza os seguintes passos:

1. Define uma chave AES de 128 bits.
2. Utiliza um **Vetor de Inicialização (IV)** de 16 bytes para garantir que a criptografia do mesmo texto não produza sempre os mesmos resultados.
3. Criptografa o texto usando o modo **CBC** e a chave definida.
4. Exibe o **texto criptografado** no Monitor Serial em formato hexadecimal.
5. Descriptografa o texto criptografado e exibe o **texto original** novamente.
