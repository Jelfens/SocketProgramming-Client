#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 80
#define BUFFER_SIZE 1024

int main()
{
    // Winsock ba�lat�l�r
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Soket olu�turulur
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET)
    {
        printf("Failed to create socket.\n");
        return 1;
    }

    // Server'a ba�lan�l�r
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr.s_addr);
    //server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT);
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
    {
        printf("Failed to connect to server.\n");
        return 1;
    }

    // �leti�im kurulur
    char buffer[BUFFER_SIZE];
    while (1)
    {
        // Veri g�nderilir
        printf("Enter message to send: ");
        fgets(buffer, sizeof(buffer), stdin);
        int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
        if (bytes_sent <= 0)
            break;

        // Veri al�n�r
        //int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        //if (bytes_received <= 0)
        //    break;

        // Veri ekrana yazd�r�l�r
        //buffer[bytes_received] = '\0';
        //printf("Received: %s\n", buffer);
    }

    // Soket kapat�l�r
    closesocket(client_socket);
    // Winsock kapat�l�r
    WSACleanup();

    return 0;
}

