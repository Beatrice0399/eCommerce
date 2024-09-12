#include "main.h"

int Registration(Context ctx){
    system("clear");

    cout << "Email: ";
    string email;
    getline(cin, email);

    cout << "Username: ";
    string username;
    getline(cin, username);

    cout << "Password: ";
    string password;
    getline(cin, password);

    redisReply *reply = (redisReply*) RedisCommand(ctx.GetRedis(), 
    "XADD vendor * operation_id 1 username %s email %s password %s", username.c_str(), email.c_str(), password.c_str());
    string rid = reply->str;

    bool run = true;
    while(run){
        system("clear");
        cout << "Loading..." << endl;
        reply = RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 5000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){continue;}
        redisReply *elements = (redisReply*) GetFirstEntryElements(reply);

        string result = elements->element[1]->str;
        if(!(result.compare("2"))){
            Notification("Failed registration");
            return -2;
        }
        else if(!(result.compare("1"))){
            string sid = elements->element[3]->str;
            int id = stoi(sid);
            Notification("Successfull registration");
            return id;
        }

    }
    // Se problema ritorna -2
    // Notification("Failed registration");
    return 0;
}
int Login(Context ctx){
    system("clear");

    cout << "Username: ";
    string username;
    getline(cin, username);

    cout << "Password: ";
    string password;
    getline(cin, password);

    redisReply *reply = (redisReply*) RedisCommand(ctx.GetRedis(),
    "XADD vendor * operation_id 3 username %s password %s", username.c_str(), password.c_str());

    string rid = reply->str;
    bool run = true;

    while(run){
        system("clear");
        cout << "Loading..." << endl;
        reply = (redisReply*) RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 5000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){continue;}

        redisReply *elements = (redisReply*) GetFirstEntryElements(reply);
        string result = elements->element[1]->str;
        if(!(result.compare("2"))){
            Notification("Invalid credential");
            return -2;
        }
        else if(!(result.compare("1"))){
            string sid = elements->element[3]->str;
            int id = stoi(sid);
            Notification("Successfull login");
            return id;
        }
    }

    // Se problema ritorna -2
    // Notification("Failed login");
    return 0;
}