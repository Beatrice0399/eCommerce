#include "main.h"

bool isNumerical(string str) {
    try {
        size_t pos;
        stod(str, &pos); // or use std::stod for floating-point numbers
        return pos == str.length(); // Ensure the entire string is consumed
    } catch (const invalid_argument&) {
        return false; // Conversion failed
    } catch (const out_of_range&) {
        return false; // Value is out of the range of int or double
    }
}

bool isIntNumerical(string str) {
    try {
        size_t pos;
        stoi(str, &pos); // or use std::stod for floating-point numbers
        return pos == str.length(); // Ensure the entire string is consumed
    } catch (const invalid_argument&) {
        return false; // Conversion failed
    } catch (const out_of_range&) {
        return false; // Value is out of the range of int or double
    }
}

/*
message to redis vendor client to confirm that a new vendor was created with the given id. 
The channel ID from which the messsage was received is used.
*/
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser) {
    cout << "Sending message to " << id_entry << "..." << endl;
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 1 iduser %d", id_entry.c_str(), iduser);
    return 0;
    cout << "Message sent" << endl;
}

/*
message to redis vendor client to inform that there has been an error.
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
message to redis vendor client to confirm the successful ooperation.
The channel ID from which the message was received is used.
*/
int messageStatusOkRedis(redisContext *redis, string id_entry) {
    cout << "Sending message to " << id_entry << "..." << endl;
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 3", id_entry.c_str());
    cout << "Message sent" << endl;
    return 0;
}