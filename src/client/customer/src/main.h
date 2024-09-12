#include <hiredis/hiredis.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>
#include <termios.h>
#include <stdio.h>
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

// Keywords

class V_Kwd_Man{
private:
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
    vector<string> keywords;
    long unsigned int selected;
    int size;
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
    string ToString();
    string ToString(int n_char, int n_price);
    string GetName();
    float GetPrice();
    int GetId();
    int GetSales();
};

class Order{
private:
    int id;
    string name;
    float total_price;
    int quantity;
    string shipping_status;
public:
    Order(int id, string name, float price, int quantity, string shipping_status);
    string ToString();
    string ToString(int name_C, int price_c, int quantity_c, int shipping_c);
    int GetId();
    string GetName();
    float GetPrice();
    int GetQuantity();
    string GetShipping();
};


int ManageAuthenticationKwd(Context ctx, int comand);
int ManageMainKwd(Context ctx, int comand);

// Service

int AuthenticationService(Context ctx);
int MainService(Context ctx);
int SearchProduct(Context ctx);
int VisualizeInsertion(Context ctx, Insertion ins);
int CreatingOrderService(Context ctx, Insertion ins);
int VisualizeOrders(Context ctx);

// Operation

vector<Insertion> GetProductList(Context ctx, string name);
vector<Order> GetOrderList(Context ctx);
bool CreateOrder(Context ctx, Insertion ins, int quantity);

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
string OrderTableString(int name_c, int price_c, int quantity_c, int status_c);

// Boh

class Spinner{
private:
    int quantity;
    bool negative;
public:
    Spinner(bool negative);
    string ToString();
    int GetQuantity();
    int GetQuantity(string msg);
};