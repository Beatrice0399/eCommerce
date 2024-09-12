#include "main.h"

int AddInsertion(Context ctx, string name, float price){
    redisReply *reply = RedisCommand(ctx.GetRedis(), 
    "XADD vendor * operation_id 2 product_name %s price %f id_vendor %d", name.c_str(), price, ctx.GetId());

    string rid = reply->str;

    while(true){
        system("clear");
        cout << "Loading..." << endl;
        reply = (redisReply*) RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 5000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){continue;}

        redisReply *elements = (redisReply*) GetFirstEntryElements(reply);
        string result = elements->element[1]->str;
        if(!(result.compare("3"))){
            Notification("Insertion created successfull");
            return 0;
        }
        else if(!(result.compare("2"))){
            Notification("Error creating insertion");
            return 0;
        }
    }

    return 0;
}

vector<Insertion> GetInsertion(Context ctx){

    vector<Insertion> insertions;

    char comand[400];
    snprintf(comand, sizeof(comand), 
    "SELECT id, product, price, vendor FROM Insertion WHERE vendor = %d", ctx.GetId());
    PGresult *result = ctx.GetDB().ExecSQLtuples(comand);
    for(int i = 0; i < PQntuples(result); i++){
        int id = atoi(PQgetvalue(result, i, 0));
        string name = PQgetvalue(result, i, 1);
        float price = atof(PQgetvalue(result, i, 2));
        snprintf(comand, sizeof(comand),
        "SELECT COUNT (*) FROM Orders WHERE product = %d", id);
        PGresult *sales_query = ctx.GetDB().ExecSQLtuples(comand);
        int sales = atoi(PQgetvalue(sales_query, 0, 0));
        insertions.push_back(Insertion(id, name, price, sales));
    }
    return insertions;
}