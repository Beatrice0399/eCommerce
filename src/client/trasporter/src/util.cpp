#include "main.h"

void Notification(string message){
    system("clear");
    cout << message << flush;
    sleep(1);
}

redisReply* GetFirstEntry(redisReply *reply){return reply->element[0]->element[1]->element[0];}
redisReply* GetFirstEntryElements(redisReply *reply){return reply->element[0]->element[1]->element[0]->element[1];}

Context::Context(Con2DB db, redisContext *redis){
    this->db = db;
    this->redis = redis;}
bool Context::GetDebug(){return this->debug;}
void Context::SetDebug(bool debug){this->debug = debug;}
redisContext* Context::GetRedis(){return this->redis;}
int Context::GetId(){return this->id;}
Con2DB Context::GetDB(){return this->db;}
void Context::SetId(int id){this->id = id;}

char getc() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
Shipping::Shipping(int id, string customer_name, string shipping_address, string product_name, int quantity, string status){
        this->id = id;
        this->customer_name = customer_name;
        this->shipping_address = shipping_address;
        this->product_name = product_name;
        this->quantity = quantity;
        this->status = status;
}
int Shipping::GetId(){return this->id;}
string Shipping::GetCustomerName(){return this->customer_name;}
string Shipping::GetShippingAddress(){return this->shipping_address;}
string Shipping::GetProductName(){return this->product_name;}
int Shipping::GetQuantity(){return this->quantity;} 
string Shipping::GetStatus(){return this->status;}
void Shipping::SetStatus(string status){this->status = status;}
string Shipping::ToString(int c_name, int c_quantity, int c_status, int c_address){
        string buf;
        buf.append(this->product_name);
        for(int i = 0; i < c_name - this->product_name.length(); i++){buf.append(" ");}

        buf.append(" | ");

        for(int i = 0; i < c_quantity - to_string(this->quantity).length(); i++){buf.append(" ");}
        buf.append(to_string(this->quantity));

        buf.append(" | ");

        for(int i = 0; i < c_status - this->status.length(); i++){buf.append(" ");}
        buf.append(this->status);

        buf.append(" | ");

        buf.append(this->shipping_address);
        for(int i = 0; i < c_address - this->shipping_address.length(); i++){buf.append(" ");}

        return buf;
}

string GetTableIndentation(int name_c, int quantity_c, int status_c, int addres_c){
        string buf;
        int cbuf = (name_c - 4) / 2;
        for(int i = 0; i < cbuf + 3; i++){buf.append(" ");}
        buf.append("Name");
        for(int i = 0; i < (name_c - 4) - cbuf; i++){buf.append(" ");}

        buf.append(" | ");

        cbuf = (quantity_c - 4) / 2;
        for(int i = 0; i < cbuf; i++){buf.append(" ");}
        buf.append("Qty.");
        for(int i = 0; i < (quantity_c - 4) - cbuf; i++){buf.append(" ");}

        buf.append(" | ");

        cbuf = (status_c - 6) / 2;
        for(int i = 0; i < cbuf; i++){buf.append(" ");}
        buf.append("Status");
        for(int i = 0; i < (status_c - 6) - cbuf; i++){buf.append(" ");}

        buf.append(" | ");

        cbuf = (addres_c - 7) / 2;
        for(int i = 0; i < cbuf; i++){buf.append(" ");}
        buf.append("Address");
        for(int i = 0; i < (addres_c - 7) - cbuf; i++){buf.append(" ");}

        buf.append("\n");

        for(int i = 0; i < name_c + 3; i++){buf.append("-");}
        buf.append("-|-");
        for(int i = 0; i < quantity_c; i++){buf.append("-");}
        buf.append("-|-");
        for(int i = 0; i < status_c; i++){buf.append("-");}
        buf.append("-|-");
        for(int i = 0; i < addres_c; i++){buf.append("-");}
        return buf;
}