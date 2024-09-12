#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new customer into the database. It sends a message to the new customer whit their id.
*/
int newRegistrationMsg(string entry_number, string username, string email, string password, string shipping_address, redisContext *redis) {
    replace(shipping_address.begin(), shipping_address.end(), '_', ' ');
    int id_customer = newRegistrationDB(username, email, password, shipping_address); 
    if (id_customer < 0) {
        cout << "Error creating new customer within the database" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New customer created with the following characteristics: "<< endl;
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    cout << "Password: " << password << endl << endl;
    messageReturnIdRedis(redis, entry_number, id_customer);
    return 0; 

}

/*
analyzes the message extracting the necessary informations that will be used to add a new 
order into the database. A message is sent to the redis customer client to confirm the successful 
operation and to the transporter to create a new shipping.
*/
int newOrderMsg(string entry_number, string id_product, string quantity, string id_customer, redisContext *redis) {
    cout << "Creating new order..." << endl;
    int id_order = newOrderDB(id_product, quantity, id_customer);
    if (id_order < 0) {
        cout << "Error while creating new order within database" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    } else {
        cout << "Ner order created with: " << endl;
        cout << "Id: "<< id_order << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Id_customer: " << id_customer << endl << endl;
        messageStatusOkRedis(redis, entry_number);
       return 0; 
    }
}

/*
analyzes the message extracting the necessary informations that will be used to search
user credentials inside the database. A message is sent to the redis customer client to 
confirm the seccussful operation including the customer's id.
*/
int loginMsg(string entry_number, string username, string password, redisContext *redis) {
    clear();
    int id = loginDB(username, password);
    if (id != -1) {
        move(0,0);
        printw("Successful operation Login.");
        refresh();
        messageReturnIdRedis(redis, entry_number, id);
        return 0; 
    } else {
        move(0,0);
        printw("Error login");
        refresh();
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}