#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define PUBLIC_DIR "./public"
#define PORT 8080  // 硬編碼端口號

void handle_client(int client_socket);
void send_404(int client_socket);
void send_file(int client_socket, const char *path);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        close(server_socket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1) {
        perror("Socket listen failed");
        close(server_socket);
        return 1;
    }

    printf("Server is listening on http://localhost:%d\n", PORT);

    // Accept and handle incoming connections
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len)) != -1) {
        handle_client(client_socket);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char method[16], path[256], version[16];

    bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        perror("Read from client failed");
        return;
    }

    buffer[bytes_read] = '\0';
    sscanf(buffer, "%15s %255s %15s", method, path, version);

    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/") == 0) {
            strcpy(path, "/index.html");
        }

        char full_path[BUFFER_SIZE];
        snprintf(full_path, sizeof(full_path), "%s%s", PUBLIC_DIR, path);

        if (access(full_path, F_OK) == 0) {
            send_file(client_socket, full_path);
        } else {
            send_404(client_socket);
        }
    } else {
        send_404(client_socket);
    }
}

void send_404(int client_socket) {
    const char *response =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "<h1>404 Not Found</h1>";
    write(client_socket, response, strlen(response));
}

void send_file(int client_socket, const char *path) {
    int file = open(path, O_RDONLY);
    if (file == -1) {
        perror("Open file failed");
        send_404(client_socket);
        return;
    }

    struct stat st;
    fstat(file, &st);

    char header[BUFFER_SIZE];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %lld\r\n"
             "\r\n", (long long)st.st_size);
    write(client_socket, header, strlen(header));

    char file_buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(file, file_buffer, sizeof(file_buffer))) > 0) {
        write(client_socket, file_buffer, bytes_read);
    }

    close(file);
}