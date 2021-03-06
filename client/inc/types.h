#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

// Type for the user saved from the server
typedef struct s_user {
    int user_id;
    char* name;
    char* password;
    char* avatar_path;
    t_avatar_color avatar_color;
}              t_user;

typedef struct s_client_utils {
    int server_fd;
    SSL* ssl;
    SSL_CTX* ctx;
    pthread_t th_reader;
    pthread_mutex_t lock;
    t_user* current_user;
    t_chat* current_chat;
    t_chat* chatlist;
    // for suspending server updates during request handling
    bool is_suspended;
}              t_client_utils;

extern t_client_utils *utils;

#endif
