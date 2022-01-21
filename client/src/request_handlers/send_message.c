#include "../../inc/client.h"

t_response_code handle_send_msg_request(const char* message_str) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_SEND_MESSAGE);
    cJSON_AddStringToObject(json, "text", message_str);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", 1); // change this to that of currently selected chat
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    t_response_code error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);
    return error_code;

}
