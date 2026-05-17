#include "settings.h"

int main(int argc, char const *argv[])
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return -1;
    }
    int server_sock_d = socket(AF_INET, SOCK_STREAM, 0);

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

        int file_size = 0;
        recv(client_socket, (char *)&file_size, sizeof(int), 0);
        char *file_data = malloc(file_size);
        int received = 0;
        while (received < file_size)
        {
            int r = recv(client_socket, file_data + received, file_size - received, 0);
            if (r <= 0)
            {
                break;
            }
            received += r;
        }

        unsigned long long key = ENCRYPTION_KEY;
        unsigned char *key_bytes = (unsigned char *)&key;
        for (int i = 0; i < received; i++)
        {
            file_data[i] ^= key_bytes[i % 8];
        }

        FILE *f = fopen("received_file", "wb");
        fwrite(file_data, 1, received, f);
        fclose(f);

        printf("Received %d bytes, saved as 'received_file\n", received);
        free(file_data);
        closesocket(client_socket);
    }
    closesocket(server_sock_d);
    WSACleanup();

    return 0;
}