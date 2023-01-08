#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

void test()
{
    // Step 1. Create a socket
    
    int server_fd; 
    int addrlen;
    // create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("cannot create socket");
        return 0;
    }


    // Step 2. Indentify (name) a socket

    struct sockaddr_in address;
    const int PORT = 8080;

    // htonl converts a long integer (e.g. address) to a network representation  
    // htons converts a short integer (e.g. port) to a network representation  
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address) < 0)) 
    {
        perror("bind failed");
        return 0;
    }
    

    // Step 3. On the server, wait for an incoming connection

    int new_socket;
    
    if (listen(server_fd, 3) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE); 
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
    (socklen_t*)&addrlen)) < 0)
    {
        perror("In accept");
        exit(EXIT_FAILURE);
    }


    // Step 4. Send and receive messages
    
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    
    printf("%s\n", buffer);
    if (valread < 0) 
    {
        printf("No bytes are there to read");
    }

    char *hello = "Hello from the server"; // IMPORTANT we will get to it
    write(new_socket, hello, strlen(hello));


    // Step 5. Close the socket
    close(new_socket);
}
