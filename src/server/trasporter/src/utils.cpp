#include "main.h"

/*
message to redis transporter client to confirm that a new transporter was created with the given id. 
The channel ID from which the messsage was received is used.
*/
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser) {
    cout << "Sending message to " << id_entry << "..." << endl;
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 1 iduser %d", id_entry.c_str(), iduser);
    cout << "Message sent" << endl;
    return 0;
}

/*
message to redis transporter client to inform that there has been an error.
The channel ID from which the message was received is used.
*/
int statusErrMessageRedis(redisContext *redis, string id_entry) {
    cout << "Sending error message to " << id_entry << "..." << endl;
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 2", id_entry.c_str());
    cout << "Message sent" << endl;
    return 0;
}

/*
message to redis transporter client to confirm the successful operation.
The channel ID from which the message was received is used.
*/
int messageStatusOkRedis(redisContext *redis, string id_entry) {
    cout << "Sending message to " << id_entry << "..." << endl;
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 3", id_entry.c_str());
    cout << "Message sent" << endl;
    return 0;
}

/*
message to redis transporter client to inform that no order is available for shipping.
The channel ID from which the message was received is used.
*/
int messageNoOrderAvailable(redisContext *redis, string id_entry) {
    cout << "Sending message to " << id_entry << "..." << endl;
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 4", id_entry.c_str());
    cout << "Message sent" << endl;
    return 0;
}
