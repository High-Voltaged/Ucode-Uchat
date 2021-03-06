#include "../../inc/client.h"

t_response_code handle_join_chat_request(const char* chat_name) {

    utils->is_suspended = true;
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "chat_name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_JOIN_CHAT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    
    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    if (error_code == R_SUCCESS) {

        handle_get_chats_request();

    }

    free(json_str);
    free(response);
    utils->is_suspended = false;
    return error_code;

}
