#include "main.h"

Con2DB CreateDB(){
    // hostname, port, username, password, dbname
    static Con2DB db("localhost", "5432", "ecommerce", "47002", "myecommerce");
    return db;
}

/*
create a new customer within the database with username, email, password and shipping address
received from redis client. It returns new user's id.
*/
int newRegistrationDB(string username, string email, string password, string shipping_address) {
    Con2DB db = CreateDB();
    cout << "Username: " << username << endl << "Email: " << email << endl << "Password: "<< password <<endl;

    char command[200];
    sprintf(command, "BEGIN"); 
    PGresult *result = db.ExecSQLcmd(command);

    snprintf(command, sizeof(command), 
        "SELECT * FROM Customer WHERE email = '%s';", email.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }

    snprintf(command, sizeof(command), 
        "SELECT * FROM Customer WHERE username = '%s';", username.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }
    
    snprintf(command, sizeof(command),
     "INSERT INTO Customer (username, password, email, shipping_address) VALUES ('%s', '%s', '%s', '%s') RETURNING id;", 
      username.c_str(), password.c_str(), email.c_str(), shipping_address.c_str());
    
   
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        return -1;
    }

    int id = atoi(PQgetvalue(result, 0, 0));
    sprintf(command, "COMMIT"); 
    result = db.ExecSQLcmd(command);
    //PQclear(result);
    return id;
}


/*
create a new order within the databse with id_product, quantity and id_customer received
from the redis client. It returns new order's id.
*/
int newOrderDB(string id_product, string quantity, string id_customer) {
    Con2DB db = CreateDB();

    int id_p = stoi(id_product);
    int qty = stoi(quantity);
    int id_c = stoi(id_customer);

    char command[200];
    snprintf(command, sizeof(command), 
    "INSERT INTO orders (product, quantity, customer) VALUES ('%d', '%d', '%d') RETURNING id", id_p, qty, id_c );
    PGresult *result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        return -1;
    }  

    int id = atoi(PQgetvalue(result, 0, 0));
    //PQclear(result);
    return id;
}

/*
login by searching within the database an entity with the same username and password as given 
in the redis message. It returns id of the entity.
*/
int loginDB(string username, string password) {
    system("clear");
    cout << "Cerco l'utente: " << username << endl;
    char command[200];
    Con2DB db = CreateDB();
    snprintf(command, sizeof(command), 
        "SELECT id FROM Customer WHERE username = '%s' AND password = '%s';", 
        username.c_str(), password.c_str());
    PGresult *result = db.ExecSQLtuples(command);
    if (!((PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result)) > 0 )) {
        return -1;
    }
    int id = atoi(PQgetvalue(result, 0, 0));
    return id;
}