#include "main.h"

int NewShippingOrder(Context ctx){
    system("clear");
    redisReply *reply;
    char buf[300];
    snprintf(buf, sizeof(buf), "XADD transporter * operation_id 4 id_transporter %d", ctx.GetId());
    reply = RedisCommand(ctx.GetRedis(), buf);
    string rid = reply->str;
    while(true){
        reply = RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 5000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){continue;}
        redisReply *elements = (redisReply*) GetFirstEntryElements(reply);
        string result = elements->element[1]->str;
        if(!result.compare("3")){return true;}
        else{return false;}
    }
    return false;
}

vector<Shipping> GetShippings(Context ctx){
    char buf[500];
    snprintf(buf, sizeof(buf), "SELECT s.id, u.username, u.shipping_address, i.product, o.quantity, s.shipping_status FROM orders o JOIN customer u ON o.customer = u.id JOIN insertion i ON o.product = i.id JOIN shipping s ON o.id = s.id_order WHERE s.transporter = %d", ctx.GetId());
    PGresult *result = ctx.GetDB().ExecSQLtuples(buf);
    vector<Shipping> shippings;
    for(int i = 0; i < PQntuples(result); i++){
        int id = atoi(PQgetvalue(result, i, 0));
        string username = PQgetvalue(result, i, 1);
        string shipping_address = PQgetvalue(result, i, 2);
        string product_name = PQgetvalue(result, i, 3);
        int quantity = atoi(PQgetvalue(result, i, 4));
        string shipping_status = PQgetvalue(result, i, 5);
        shippings.push_back(Shipping(id, username, shipping_address, product_name, quantity, shipping_status));
    }
    return shippings;
}

bool ChangeStatus(Context ctx, Shipping s, int status_id){
    system("clear");
    cout << "Loading..." << endl;
    string status;
    switch (status_id){
    case 0: status = "pendant"; break;
    case 1: status = "delivering"; break;
    case 2: status = "delivered"; break;
    default: return false;}

    char buf[500];
    snprintf(buf, sizeof(buf), "XADD transporter * operation_id 2 id_shipping %d status %s", s.GetId(), status.c_str());
    redisReply *reply;
    reply = RedisCommand(ctx.GetRedis(), buf);
    string rid = reply->str;
    while(true){
        reply = RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 5000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){continue;}
        redisReply *elements = (redisReply*) GetFirstEntryElements(reply);
        string result = elements->element[1]->str;
        if(!result.compare("3")){return true;}
        else{return false;}
    }
    return false;
}
