#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new vendor into the database. It sends a message to the new vendor whit their id.
*/
int newRegistrationMsg(string entry_number, string username, string email, string password, redisContext *redis) {
    // clear();
    // move(0,0);
    printw( "Creation new vendor user...\n");
    refresh();
    int id_vendor = newRegistrationDB(username, email, password);
    if (id_vendor < 0) {
        printw("Error while creating a new vendor user within the database.\n");
        refresh();
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    // clear();
    // move(0,0);
    // printw("New vendor created with \nId: %d\nUsername: %s\nEmail: %s\nPassword: %s\n", id_vendor, username.c_str(), email.c_str(), password.c_str());
    // refresh();
    cout << "New vendor created:" << endl;
    cout << "\tId: " << id_vendor << endl;
    cout << "\tUsername: " << username << endl;
    cout << "\tEmail: " << email << endl;
    cout << "\tPassword: " << password << endl << endl;
    messageReturnIdRedis(redis, entry_number, id_vendor);
    return 0; 

}

/*
analyzes the message extracting the necessary informations that will be used to add a new 
insertion into the database. A message is sent to the redis vendor client to confirm the successful 
operation.
*/
int newInsertionMsg(string entry_number, string product_name, string price, string id_vendor, redisContext *redis) {
    replace(product_name.begin(), product_name.end(), '_', ' ');
    // clear();
    // move(0,0);
    // printw("Creation new product...\n");
    cout << "Creation new product..." << endl; 
    int status = newInsertionDB(product_name, price, id_vendor);
    if (status != 0) {
        cout << "Error while creating the new product within the database" << endl;
        statusErrMessageRedis(redis, entry_number); 
        return -1;
    } else {
        messageStatusOkRedis(redis, entry_number);
        // printw("New product created with the following characteristics:\nProduct name: %s\nPrice: %s \nId_vendor: %s\n", product_name.c_str(), price.c_str(), id_vendor.c_str());
        // refresh();  
        cout << "New product created with the following characteristics:" << endl;
        cout << "Product name: " << product_name  << endl;
        cout << "Price: " << price << endl;
        cout << "Id_vendor: " << id_vendor << endl << endl;
        return 0; 
    }
}

/*
analyzes the message extracting the necessary informations that will be used to search
user credentials inside the database. A message is sent to the redis vendor client to 
confirm the seccussful operation including the vendor's id.
*/
int loginMsg(string entry_number, string username, string password, redisContext *redis) {
    // clear();
    int id = loginDB(username, password);
    if (id != -1) {
        cout << "Successful login" << endl;
        messageReturnIdRedis(redis, entry_number, id);
        return 0; 
    } else {
        cout << "Login failed" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}