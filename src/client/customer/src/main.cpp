#include "main.h"

int main(){
    redisContext *redis = redisConnect("localhost", 6379);
    Con2DB db = Con2DB("localhost", "5432", "ecommerce", "47002", "myecommerce");
    Context ctx = Context(db, redis);  
    ctx.SetDebug(false);  
    bool run = true;
    int flag;
    while(run){
        flag = AuthenticationService(ctx);
        if(flag == -1){
            run = false;
            return 0;
        }
        if(flag >= 0){
            break;
        }
    }
    ctx.SetId(flag);

    // Main cycle
    int result = MainService(ctx);
    return result;
}