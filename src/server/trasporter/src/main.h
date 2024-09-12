#include <iostream>
#include <hiredis/hiredis.h>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <thread>
#include <ncurses.h>

#include <csignal>
#include <atomic>

using namespace std;

int main();

// database
Con2DB CreateDB();
int newRegistrationDB(string username, string email, string password);
int newShippingDB(string id_order);
int loginDB(string username, string password);
int requestShippingDB(int id_transporter);
int changeShippingStatusDB(int id_shipping, string sh_status);

// operation
int newRegistrationMsg(string id_entry, string username, string email, string password, redisContext *redis);
int changeShippingStatusMsg(string entry_number, string id_shipping, string status, redisContext *redis);
int loginMsg(string id_entry, string username, string password, redisContext *redis);
int requestShippingMsg(string id_entry, string id_transporter, redisContext *redis);

// utils
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser);
int statusErrMessageRedis(redisContext *redis, string id_entry);
int messageStatusOkRedis(redisContext *redis, string id_entry);
int messageNoOrderAvailable(redisContext *redis, string id_entry);

// thread
void inputListener(bool &run);
int redisListener(redisContext *redis, bool &run);