#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new transporter into the database. It sends a message to the new vendor whit their id.
*/
int newRegistrationMsg(string entry_number, string username, string email, string password, redisContext *redis) {
    cout << "Creating new transporter within the database..." << endl;
    int id_vendor = newRegistrationDB(username, email, password); 
    if (id_vendor < 0) {
        cout << "Error while creating new transporter user within the database" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New transporter created with: " << endl;
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    cout << "Password: " << endl << endl;
    
    messageReturnIdRedis(redis, entry_number, id_vendor);
    
    return 0; 
}

/*
analyzes the message extracitng the information for the request shipping.
If there is an order available for shipping, then the shipping is created and a message is sent to 
the transporte who did the request. Otherwise it returns an error message.
*/
int requestShippingMsg(string entry_number, string id_transporter, redisContext *redis) {
    cout << "Cerco un ordine disponibile per la spedizione..."<< endl;
    int status = requestShippingDB(stoi(id_transporter));
    if (status == -2) {
        cout << "Nessun ordine disponibile" << endl;
        messageNoOrderAvailable(redis, entry_number);
        return -1;
    } else if (status == -1) {
        cout << "Error query" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New shipping created" << endl << endl;
    messageStatusOkRedis(redis, entry_number);
    return 0;
}

/*
analyzes the message extracting the necessary informations that will be used to search
user credentials inside the database. A message is sent to the redis transporter client to 
confirm the seccussful operation including the transporter's id.
*/
int loginMsg(string entry_number, string username, string password, redisContext *redis) {
    int id = loginDB(username, password);
    if (id != -1) {
        cout << "Login transporter with id " << id << endl;
        messageReturnIdRedis(redis, entry_number, id);
        return 0; 
    } else {
        cout << "Error login" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}

/*
analyzes the message extracting the necessary informations that will be used to change the 
shipping status. A message is sent to the redis transporter client to confirm the 
successful operation or the error.
*/
int changeShippingStatusMsg(string entry_number, string id_shipping, string sh_status, redisContext *redis) {
    int status = changeShippingStatusDB(stoi(id_shipping), sh_status);
    if (status < 0) {
        cout << "Error while updating shipping status within the database." << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "Shipping status correctly updated." << endl << endl;
    messageStatusOkRedis(redis,entry_number);
    return 0;
}