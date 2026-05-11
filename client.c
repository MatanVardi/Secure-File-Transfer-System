#include "settings.h"

int main(int argc, char const *argv[])
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    int sock_d = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connect_status = connect(sock_d, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connect_status == -1)
    {
        printf("Error: %d\n", WSAGetLastError());
    }
    else
    {
        char clientMsg[255];
        printf("Enter message for server: ");
        fgets(clientMsg, sizeof(clientMsg), stdin);

        send(sock_d, clientMsg, (int)strlen(clientMsg) + 1, 0);

        printf("Message sent to server!\n");
    }

    closesocket(sock_d);
    return 0;
}