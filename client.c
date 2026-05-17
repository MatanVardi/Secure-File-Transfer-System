#include "settings.h"

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        printf("Usage: client <filepath>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f)
    {
        printf("Couldn't open file: %s\n", argv[1]);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    int file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *file_data = malloc(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);

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

    // char clientMsg[255];
    // printf("Enter message for server: ");
    // fgets(clientMsg, sizeof(clientMsg), stdin);

    // send(sock_d, clientMsg, (int)strlen(clientMsg) + 1, 0);

    // printf("Message sent to server!\n");

    send(sock_d, (char *)&file_size, sizeof(int), 0);
    send(sock_d, file_data, file_size, 0);
    printf("Sent %d bytes\n", file_size);
    free(file_data);
    closesocket(sock_d);
    WSACleanup();
    return 0;
}