#include "../../inc/client.h"

void handle_delete_msg_request(int message_id) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", 1); // chat_id here
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    int error_code = handle_server_response(response);
    // if ((error_code = handle_server_response(response)) != R_SUCCESS) {

        // Here, if server responded with error, notify the user via the GUI
        logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // }
    free(json_str);
    free(response);

}