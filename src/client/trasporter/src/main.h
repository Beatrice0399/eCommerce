#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <termios.h>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>

using namespace std;

int main();

// Context

class Context{
    private:
        bool debug;
        int id;
        Con2DB db;
        redisContext *redis;
    public:
        Context(Con2DB db, redisContext *redis);
        bool GetDebug();
        void SetDebug(bool debug);
        redisContext *GetRedis();
        Con2DB GetDB();
        int GetId();
        void SetId(int id);
};

class Shipping{
private:
    int id;
    string customer_name;
    string shipping_address;
    string product_name;
    int quantity;
    string status;
public:
    Shipping(int id, string customer_name, string shipping_address, string product_name, int quantity, string status);
    int GetId();
    string GetCustomerName();
    string GetShippingAddress();
    string GetProductName();
    int GetQuantity();
    string GetStatus();
    void SetStatus(string status);
    string ToString(int c_name, int c_quantity, int c_status, int c_address);
};

// Authentication

int Registration(Context ctx);
int Login(Context ctx);

// Service

int AuthenticationService(Context ctx);
int MainService(Context ctx);
int NewShipping(Context ctx);
int MyShippings(Context ctx);
int VisualizeShipping(Context ctx, Shipping s);
int ChangeStatusService(Context ctx, Shipping s);

// Operation

int NewShippingOrder(Context ctx);
vector<Shipping> GetShippings(Context ctx);
bool ChangeStatus(Context ctx, Shipping s, int status_id);

// Manage keyword

int ManageAuthenticationKwd(Context ctx, int comand);
int ManageMainKwd(Context ctx, int comand);

class V_Kwd_Man{
private:
    int size;
    vector<string> keywords;
    long unsigned int selected;
public:
    V_Kwd_Man(vector<string> keywords);
    string ToString();
    void Previous();
    void Next();
    int GetSelected();
    int GetComandId();
    int GetComandId(string msg);
};

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

class Spinner{
private:
    int size;
    vector<string> keywords;
    long unsigned int selected;
public:
    Spinner(vector<string> keywords);
    string ToString();
    void Previous();
    void Next();
    int GetSelected();
    int GetComandId();
    int GetComandId(string msg); 
};

// Util

void Notification(string message);
redisReply* GetFirstEntry(redisReply *reply);
redisReply* GetFirstEntryElements(redisReply *reply);
string GetTableIndentation(int name_c, int quantity_c, int status_c, int addres_c);
char getc();