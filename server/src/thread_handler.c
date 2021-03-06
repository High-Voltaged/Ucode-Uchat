#include "../inc/server.h"

char* get_client_request(SSL* ssl, int length) {

    char buffer[SENT_DATA_LEN] = "";
    int bytesRead = 0;
    while (bytesRead < length) {

        int bytes = SSL_read(ssl, &buffer[bytesRead], length - bytesRead );
        if (bytes <= 0) {

            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                continue;
            }
            return NULL;

        } else if (bytes < length) {
            
            bytesRead += bytes;
        
        } else if (bytes == length) {
        
            bytesRead = bytes;
            break;
        
        }
    }
    buffer[bytesRead] = '\0';
    return mx_strdup(buffer);

} 

// Read client data (a request to be handled)
char* read_client_data(SSL *ssl) {

    char buffer[SENT_DATA_LEN];
    int n_bytes = 0;
    while ((n_bytes = SSL_read(ssl, buffer, SENT_DATA_LEN)) <= 0) {
        
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            continue;
        }
        return NULL;
    
    }
    // buffer[n_bytes] = '\0';
    // return mx_strdup(buffer);
    return get_client_request(ssl, atoi(buffer));

}

void* thread_handler(void* arg) {

    t_server_utils *server_utils = (t_server_utils*)arg;
    while (1) {

        char* request_str = NULL;
        if (!(request_str = read_client_data(server_utils->ssl)))
            continue;

        t_request_type req_type = handle_request_for(request_str, server_utils);
        if (req_type == REQ_CLIENT_EXIT) {
            mx_strdel(&request_str);
            break;
        }
        mx_strdel(&request_str);

    }
    pthread_detach(pthread_self());
    return NULL;

}
