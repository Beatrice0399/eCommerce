#include <iostream>
#include <hiredis/hiredis.h>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <termios.h>
#include <curses.h>
using namespace std;

int main();

// database
Con2DB CreateDB();
int newRegistrationDB(string username, string email, string password, string shipping_address);
int newOrderDB(string id_product, string quantity, string id_customer);
int loginDB(string email, string password);

// operation
int newRegistrationMsg(string entry_number, string username, string email, string password, string shipping_address, redisContext *redis);
int newOrderMsg(string entry_number, string id_product, string quantity, string id_customer, redisContext *redis);
int loginMsg(string entry_number, string username, string password, redisContext *redis);

// utils
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser);
int statusErrMessageRedis(redisContext *redis, string id_entry);
int messageStatusOkRedis(redisContext *redis, string id_entry);



// thread
void manageThread(string operation, redisReply *reply, redisContext *redis);