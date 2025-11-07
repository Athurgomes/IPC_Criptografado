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
    int sfd, cfd;
    struct sockaddr_in s_addr, c_addr;
    socklen_t c_len;
    char buf[BUF_SIZE] = {0};
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(PORT);
    if(bind(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
        perror("bind failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    if(listen(sfd, 3) < 0){
        perror("listen failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    printf("Servidor escutando na porta %d\n", PORT);
    c_len = sizeof(c_addr);
    if((cfd = accept(sfd, (struct sockaddr *)&c_addr, &c_len)) < 0){
        perror("accept failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    read(cfd, buf, BUF_SIZE);
    printf("Mensagem recebida (criptografada): %s\n", buf);
    xor_cipher(buf, secret_key);
    printf("Mensagem (descriptografada): %s\n", buf);
    const char *reply = "Msg recebida e decifrada.";
    send(cfd, reply, strlen(reply), 0);
    printf("Resposta enviada.\n");
    close(cfd);
    close(sfd);
    return 0;
}