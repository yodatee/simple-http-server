#include <iostream>
#include "server.h"

void server::create_server() {
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET; //internet ip protocol v4
    my_addr.sin_port = htons(PORT); //PORT
    my_addr.sin_addr.s_addr = INADDR_ANY; //network byte order

    //create socket
    if ((socket_s = socket(my_addr.sin_family, SOCK_STREAM, 0)) == -1) {
        cout << CREATION_ERROR_MESSAGE << endl;
    }

    //bind socket to a PORT
    bind(socket_s, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));

    // listen up to MAX_POSSIBLE_CONNECTIONS connections
    listen(socket_s, MAX_POSSIBLE_CONNECTIONS);
}

void server::receive_data() {
    socklen_t sock_size = sizeof(struct sockaddr_in);

    struct sockaddr_in host_addr;

    //waiting for connection
    connection_c = accept(socket_s, (struct sockaddr *) &host_addr, &sock_size);

    //receive_data contend
    char get_req[MAX_PACKET_SIZE];
    recv(connection_c, get_req, MAX_PACKET_SIZE, 0);  //GET / HTTP/1.1

    cout << get_req << endl;

    send_data();

}

void server::send_data() {
    send(connection_c, WELCOME_MESSAGE, sizeof(WELCOME_MESSAGE)-1, 0);
}

void server::detach() {
    close(socket_s);
    close(connection_c);
}
