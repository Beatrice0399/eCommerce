#include "main.h"

void Notification(string message){
    system("clear");
    cout << message << flush;
    sleep(1);
}

bool StringIsNumerical(string s){
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

bool StringIsInLenght(string str, long unsigned int min, long unsigned int max){
    return (str.length() >= min) && (str.length() <= max);
}

redisReply* GetFirstEntry(redisReply *reply){
    return reply->element[0]->element[1]->element[0];
}

redisReply* GetFirstEntryElements(redisReply *reply){
    return reply->element[0]->element[1]->element[0]->element[1];
}
// Context

Context::Context(Con2DB db, redisContext *redis){
    this->db = db;
    this->redis = redis;
}
bool Context::GetDebug(){
    return this->debug;
}
void Context::SetDebug(bool debug){
    this->debug = debug;
}
redisContext* Context::GetRedis(){
    return this->redis;
}
int Context::GetId(){
    return this->id;
}
Con2DB Context::GetDB(){
    return this->db;
}
void Context::SetId(int id){
    this->id = id;
}

// Insertion

Insertion::Insertion(int id, string name, float price, int sales){
    this->id = id;
    this->name = name;
    this->price = price;
    this->sales = sales;
}
string Insertion::GetName(){return this->name;}
float Insertion::GetPrice(){return this->price;}
int Insertion::GetId(){return this->id;}
int Insertion::GetSales(){return this->sales;}
string Insertion::ToString(){
    string str;
    str.append(this->name);
    str.append(",\t");
    char buf[20];
    snprintf(buf, sizeof(buf), "%.2f", this->price);
    str.append(buf);
    return str;
}
string Insertion::ToString(int n_char, int n_price){
    string str;
    int buf_char = n_char - this->name.length();
    int price_buf_char = n_price - to_string(this->price).length();
    str.append(this->name);
    for(int i = 0; i < buf_char; i++){
        str.append(" ");
    }
    char buf[20];
    snprintf(buf, sizeof(buf), "%.2f", this->price);
    for(int i = 0; i < price_buf_char; i++){
        str.append(" ");
    }
    str.append(buf);
    str.append(" $");
    return str;
}

Order::Order(int id, string name, float price, int quantity, string shipping_status){
    this->id = id;
    this->name = name;
    this->total_price = price * quantity;
    this->quantity = quantity;
    this->shipping_status = shipping_status;
}
string Order::ToString(){
    return "";
}
string Order::ToString(int name_c, int price_c, int quantity_c, int shipping_c){
    string str;
    str.append(this->name);
    int ch = name_c - this->name.length();
    for(int i = 0; i < ch; i++){
        str.append(" ");
    }

    str.append(" | ");

    char buf[500];
    snprintf(buf, sizeof(buf), "%.2f", this->total_price);
    ch = price_c - strlen(buf);
    for(int i = 0; i < ch; i++){
        str.append(" ");
    }
    str.append(buf);

    str.append(" | ");


    int quant = quantity_c - to_string(this->quantity).length();
    for(int i = 0; i < quant; i++){str.append(" ");}
    str.append(to_string(this->quantity));

    str.append(" | ");

    ch = shipping_c - this->shipping_status.length();
    for(int i = 0; i < ch; i++){
        str.append(" ");
    }
    str.append(this->shipping_status);
    return str;
}
int Order::GetId(){return this->id;}
string Order::GetName(){return this->name;}
float Order::GetPrice(){return this->total_price;}
int Order::GetQuantity(){return this->quantity;}
string Order::GetShipping(){return this->shipping_status;}

char getch() {
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

Spinner::Spinner(bool negative){
    this->quantity = 0;
    this->negative = negative;
}

int Spinner::GetQuantity(){
    while(true){
        system("clear");
        cout << "<" << this->quantity << ">";
        char c = getch();
        switch (c){
            case 10: return this->quantity;
            case 67:
                this->quantity ++;
            case 68:
                this->quantity --;
                if(!this->negative && this->quantity <= 0){this->quantity = 1;}
        }
        return 0;
    }
}

string Spinner::ToString(){
    string str;
    str.append(" < ");
    str.append(to_string(this->quantity));
    str.append(" > ");
    return str;
}

int Spinner::GetQuantity(string msg){
    while(true){
        system("clear");
        cout << msg;
        cout << this->ToString() << endl;
        char c = getch();
        switch (c){
            case 10: return this->quantity;
            case 67:
                this->quantity ++;
                continue;
            case 68:
                this->quantity --;
                if(!this->negative && this->quantity < 0){this->quantity = 0;}
                continue;
        }
    }
    return 0;
}

string OrderTableString(int name_c, int price_c, int quantity_c, int status_c){
    string str;
    int name = name_c - 4;
    int buf = name / 2;
    for(int i = 0; i < buf; i++){str.append(" ");}
    str.append("Name");
    for(int i = 0; i < name - buf; i++){str.append(" ");}

    str.append(" | ");

    int price = price_c - 5;
    buf = price / 2;
    for(int i = 0; i < buf; i++){str.append(" ");}
    str.append("Price");
    for(int i = 0; i < price - buf; i++){str.append(" ");}

    str.append(" | ");

    int quantity = quantity_c - 3;
    buf = quantity / 2;
    for(int i = 0; i < buf; i++){str.append(" ");}
    str.append("Qty");
    for(int i = 0; i < quantity - buf; i++){str.append(" ");}

    str.append(" | ");

    int status = status_c - 6;
    buf = status / 2;
    for(int i = 0; i < buf; i++){str.append(" ");}
    str.append("Status");
    for(int i = 0; i < status - buf; i++){str.append(" ");}

    str.append("\n");
    for(int i = 0; i < name_c; i++){str.append("-");}
    str.append(" | ");
    for(int i = 0; i < price_c; i++){str.append("-");}
    str.append(" | ");
    for(int i = 0; i < quantity_c; i++){str.append("-");}
    str.append(" | ");
    for(int i = 0; i < status_c; i++){str.append("-");}

    return str;

}