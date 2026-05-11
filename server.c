#include "settings.h"

int main(int argc, char const *argv[])
{
    WSADATA wsa;
    if (WSASTARTUP(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return -1;
    }
    int server_sock_d = socket(AF_INET, SOCK_STREAM, 0);
    char serMsg[255];

    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_sock_d, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("Bind failed with error: %d\n", WSAGetLastError());
    }
    listen(server_sock_d, 1);

    while (true)
    {
        int client_socket = accept(server_sock_d, NULL, NULL);

        char buffer[255];
        int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes > 0)
        {
            buffer[bytes] = '\0';
            printf("Client sent: %s\n", buffer);
        }
    }
    closesocket(server_sock_d);
    WSACleanup();

    return 0;
}