#include "../inc/client.h"

/* 	Initialize all the client utils,
	put the server socket in a non-blocking mode 
*/
void client_init(int server_fd, SSL *ssl, SSL_CTX* ctx) {

	int flags = fcntl(server_fd, F_GETFL,0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
    fcntl(server_fd, F_SETFD, O_NONBLOCK);

	utils = malloc(sizeof(*utils));
	pthread_mutex_init(&utils->lock, NULL);
	pthread_mutex_lock(&utils->lock);
	utils->server_fd = server_fd;
	utils->ssl = ssl;
	utils->ctx = ctx;
	utils->current_user = NULL;
	utils->current_chat = NULL;
	utils->chatlist = NULL;
	utils->is_suspended = true;
	pthread_mutex_unlock(&utils->lock);

}

// Check if command line arguments are valid
void handle_arg_errors(char** argv) {

	if (argv[1] == NULL || argv[2] == NULL) {
		mx_printerr("usage: ./uchat [ip] [port]\n");
		exit(EXIT_FAILURE);
	} 

}

// Establish a connection with the server via the port
void connect_to_server(const char* ip_address, int port, int* server_fd, SSL_CTX **ctx, SSL **ssl) {

    struct sockaddr_in server_addr;

	init_ssl(ctx);

    server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip_address);
	server_addr.sin_port = htons(port);
	
	if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {		
		handle_error(strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (connect(*server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		handle_error(strerror(errno));
		exit(EXIT_FAILURE);
	}

	connect_ssl(ssl, server_fd, ctx);
}

void handle_error(const char* error) {

	char* err_str = mx_strjoin(error, "\n");
    mx_printerr(err_str);
    logger(err_str, ERROR_LOG);
	mx_strdel(&err_str);

}
