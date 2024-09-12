#include "main.h"

Con2DB CreateDB(){
    // hostname, port, username, password, dbname
    static Con2DB db("localhost", "5432", "ecommerce", "47002", "myecommerce");
    return db;
}

/*
create a new transporter within the database with username, email and password 
received from redis client. It returns the new vendor's id.
*/
int newRegistrationDB(string username, string email, string password) {
    Con2DB db = CreateDB();
    char command[200];
    sprintf(command, "BEGIN"); 
    PGresult *result = db.ExecSQLcmd(command);

    snprintf(command, sizeof(command), 
        "SELECT * FROM transporter WHERE email = '%s';", email.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }

    snprintf(command, sizeof(command), 
        "SELECT * FROM transporter WHERE username = '%s';", username.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }
    
    snprintf(command, sizeof(command),
     "INSERT INTO transporter (username, password, email) VALUES ('%s', '%s', '%s') RETURNING id;", 
      username.c_str(), password.c_str(), email.c_str());
    
   
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
login by searching within the database an entity with the same username and password as given 
in the redis message. It returns id of the entity.
*/
int loginDB(string username, string password) {
    cout << "Cerco l'utente: " << username << endl;
    char command[200];
    Con2DB db = CreateDB();
    snprintf(command, sizeof(command), 
        "SELECT id FROM transporter WHERE username = '%s' AND password = '%s';", 
        username.c_str(), password.c_str());
    PGresult *result = db.ExecSQLtuples(command);
    if (!((PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result)) > 0 )) {
        return -1;
    }
    int id = atoi(PQgetvalue(result, 0, 0));
    return id;
}

/*
query to search an order available for shipping. If there is one then a shipping is
created.
*/
int requestShippingDB(int id_transporter) {
    system("clear");
    char command[200];
    Con2DB db = CreateDB();
    sprintf(command, "BEGIN"); 
    PGresult *result = db.ExecSQLcmd(command);
    snprintf(command, sizeof(command),
    "SELECT o.id FROM orders o WHERE o.assigned='false' ORDER BY o.instant_date ASC");
    result = db.ExecSQLtuples(command);
    if (!((PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result)) > 0 )) {
        return -2;
    }
    int id_order = atoi(PQgetvalue(result, 0, 0));
    snprintf(command, sizeof(command),
    "INSERT INTO shipping (id_order, transporter) VALUES (%d, %d)", id_order, id_transporter);
    result = db.ExecSQLcmd(command);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        return -1;
    }

    snprintf(command, sizeof(command),
    "UPDATE orders SET assigned='true' WHERE id=%d", id_order);
    result = db.ExecSQLcmd(command);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        return -1;
    }
    sprintf(command, "COMMIT"); 
    result = db.ExecSQLcmd(command);
    return 0;
}

/*
query to change the shipping status with the given status.
*/
int changeShippingStatusDB(int id_shipping, string sh_status) {
    char command[200];
    Con2DB db = CreateDB();
    snprintf(command, sizeof(command),
    "UPDATE shipping SET shipping_status='%s' WHERE id=%d", sh_status.c_str(), id_shipping);
    PGresult *result = db.ExecSQLcmd(command);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        return -1;
    }
    return 0;
}

int queryShippingToTransporter(){return 1;}