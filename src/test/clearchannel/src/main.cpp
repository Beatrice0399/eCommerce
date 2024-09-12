#include "main.h"

int main(){
    string channels[3] = {"vendor", "customer", "transporter"};
    redisContext *redis = redisConnect("localhost", 6379);
    redisReply *reply;
    cout << "Avvio" << endl;
    for(string channel: channels){
        while(1){
        reply = (redisReply*) redisCommand(redis, "XRANGE %s - + COUNT 1", channel.c_str());
        cout << "Richiesta reply" << endl;
        if(reply->elements == 0){
            cout << "Esco dal programma" << endl; 
            break;
            }
        string rid = reply->element[0]->element[0]->str;
        cout << "Rid: " << rid << endl;
        reply = (redisReply*) redisCommand(redis, "XDEL %s %s", channel.c_str(),rid.c_str());
        cout << "Cancello reply" << endl;
        }
    }
}