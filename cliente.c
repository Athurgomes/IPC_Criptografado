#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUF_SIZE 1024
const char *secret_key = "MINHACHAVE123";
void xor_cipher(char *data, const char *key) {
    int data_len = strlen(data);
    int key_len = strlen(key);
    for (int i = 0; i < data_len; i++) {
        data[i] = data[i] ^ key[i % key_len];
    }
}
int main(){
    int sfd = 0;
    struct sockaddr_in s_addr;
    char buf_resposta[BUF_SIZE] = {0};
    char msg[BUF_SIZE] = "Ola, servidor. Esta eh uma mensagem secreta!";
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &s_addr.sin_addr) <= 0){
        perror("invalid address");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    if(connect(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
        perror("connection failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    printf("Mensagem original: %s\n", msg);
    xor_cipher(msg, secret_key);
    printf("Mensagem criptografada: %s\n", msg);
    send(sfd, msg, strlen(msg), 0);
    printf("Mensagem criptografada enviada.\n");
    read(sfd, buf_resposta, BUF_SIZE);
    printf("Servidor: %s\n", buf_resposta);
    close(sfd);
    return 0;
}