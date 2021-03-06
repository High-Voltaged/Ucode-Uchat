#include "../inc/server.h"

// Get the type of the request from the read json object
t_request_type get_request_type(cJSON* json) {

    return cJSON_GetObjectItem(json, "type")->valueint;

}

// Call a handler for any valid client request
t_request_type handle_request_for(const char* request, t_server_utils* utils) {

    cJSON *json = cJSON_Parse(request);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            char error[200];
            sprintf(error, "Error before: %s\n", error_ptr);
            logger(error, ERROR_LOG);
        }
        return -1;
    }

    t_request_type type = get_request_type(json);
    
    if (type == REQ_USR_LOGOUT) {
        type = handle_usr_logout(json, utils);
        cJSON_Delete(json);
        return type;
    }

    // call the request handler for the gotten request type
    request_handlers[type](json, utils);
    
    cJSON_Delete(json);
    return type;

}
