#include "../../inc/client.h"

t_response_code last_msg_id_response(const char* response_str, int* i_last_msg_id) {

    if (response_str == NULL) {
        return R_INVALID_INPUT;
    }

    cJSON* json = cJSON_Parse(response_str);

    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS) {
        cJSON_Delete(json);
        return error_code;
    }

    cJSON* last_msg_id = cJSON_GetObjectItem(json, "last_msg_id");
    if (!cJSON_IsNumber(last_msg_id)) {
        return R_JSON_FAILURE;
    }
    *i_last_msg_id = last_msg_id->valueint;
    cJSON_Delete(json);
    return R_SUCCESS;

}

int handle_last_msg_id_request(int chat_id) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddNumberToObject(json, "type", REQ_LAST_MSG_ID);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    
    int error_code = 0;
    char* response = send_and_recv_from_server(utils->ssl, json_str);
    free(json_str);

    int last_msg_id = 0;
    if ((error_code = last_msg_id_response(response, &last_msg_id)) != R_SUCCESS) {
        logger(get_response_str(error_code), ERROR_LOG);
        free(response);
        return -1;
    }
    free(response);
    return last_msg_id;

}
