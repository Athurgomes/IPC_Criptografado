# Projeto de IPC com Sockets e Criptografia em C

Este projeto demonstra a comunicação entre processos (IPC) usando Sockets TCP em linguagem C. A comunicação implementa uma troca de mensagens criptografadas entre um cliente e um servidor.

## Descrição

O projeto consiste em duas aplicações:

1.  **Servidor (`servidor.c`):** Aguarda conexões na porta `8080`. Ao receber uma mensagem de um cliente, ele a descriptografa e a exibe no console.
2.  **Cliente (`cliente.c`):** Conecta-se ao servidor no `localhost:8080`, criptografa uma mensagem e a envia. Em seguida, aguarda uma resposta do servidor.

## Criptografia

Foi utilizada uma cifra **XOR simétrica** simples. Uma chave secreta (hardcoded) é usada tanto pelo cliente (para criptografar) quanto pelo servidor (para descriptografar). A função `xor_cipher` aplica a operação XOR bit-a-bit entre cada caractere da mensagem e os caracteres da chave.

`dados[i] = dados[i] ^ chave[i % tamanho_chave]`

## Como Compilar e Executar

Este projeto foi desenvolvido e testado em ambiente Linux (ou macOS).

### 1. Compilação

Você precisará de um compilador C (como o `gcc`). Abra seu terminal e compile os dois arquivos:

```bash
# Compilar o servidor
gcc servidor_cripto.c -o servidor

# Compilar o cliente
gcc cliente_cripto.c -o cliente
```

### 2. Execução

Você precisará de dois terminais abertos.

**No Terminal 1 (Servidor):**

Execute o servidor primeiro. Ele ficará aguardando uma conexão.

```bash
./servidor
```

*Saída esperada:*
`Servidor escutando na porta 8080`

**No Terminal 2 (Cliente):**

Execute o cliente para enviar a mensagem.

```bash
./cliente
```

### 3. Resultados

**No Terminal 2 (Cliente), você verá:**

```
Mensagem original: Ola, servidor. Esta eh uma mensagem secreta!
Mensagem criptografada: [lixo ilegível]
Mensagem criptografada enviada.
Servidor: Msg recebida e decifrada.
```

**No Terminal 1 (Servidor), você verá:**

```
Servidor escutando na porta 8080
Mensagem recebida (criptografada): [lixo ilegível]
Mensagem (descriptografada): Ola, servidor. Esta eh uma mensagem secreta!
Resposta enviada.
```
