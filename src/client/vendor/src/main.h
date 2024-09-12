#include <hiredis/hiredis.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdio.h>
#include <termios.h>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>

using namespace std;

int main();

// Context

class Context{
    private:
        int id;
        Con2DB db;
        redisContext *redis;
    public:
        Context(Con2DB db, redisContext *redis);
        redisContext *GetRedis();
        Con2DB GetDB();
        int GetId();
        void SetId(int id);
};

// Keywords

class Kwd_Man{
private:
    int size;
    vector<string> keywords;
    long unsigned int selected;
public:
    Kwd_Man(vector<string> keywords);
    string ToString();
    void Previous();
    void Next();
    int GetSelected();
    int GetComandId();
    int GetComandId(string msg);
};

// Insertion

class Insertion{
private:
    int id;
    string name;
    float price;
    int sales;
public:
    Insertion(int id, string name, float price, int sales);
    string GetName();
    float GetPrice();
    int GetId();
    int GetSales();
};

int ManageAuthenticationKwd(Context ctx, int comand);
int ManageMainKwd(Context ctx, int comand);

// Service

int AuthenticationService(Context ctx);
int MainService(Context ctx);
int CreateInsertion(Context ctx);
int VisualizeInsertion(Context ctx);

// Operation

int AddInsertion(Context ctx, string name, float price);
vector<Insertion> GetInsertion(Context ctx);

// Authentication

int Registration(Context ctx);
int Login(Context ctx);

// Util

void Notification(string message);
bool StringIsNumerical(string str);
bool StringIsInLenght(string str, int min, int max);
redisReply* GetFirstEntry(redisReply *reply);
redisReply* GetFirstEntryElements(redisReply *reply);
char getch();