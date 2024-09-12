#include "main.h"

V_Kwd_Man::V_Kwd_Man(vector<string> keywords){
    this->keywords = keywords;
    this->selected = 0;
}
string V_Kwd_Man::ToString(){
    string str;
    for(long unsigned int i = 0; i < this->keywords.size(); i++){
        if(i == this->selected){str.append(" > ");}
        else{str.append("   ");}
        str.append(this->keywords[i]);
        str.append("\n");
    }
    return str;
}

void V_Kwd_Man::Previous(){
    this->selected--;
    if(this->selected < 0){
        this->selected = this->keywords.size() - 1;
    }
}
void V_Kwd_Man::Next(){
    this->selected++;
    this->selected = this->selected % this->keywords.size();
}
int V_Kwd_Man::GetSelected(){
    return this->selected;
}
int V_Kwd_Man::GetComandId(){
    while(true){
        system("clear");
        cout << this->ToString() << endl;
        char c = getch();
        switch (c){
        case 10:
            return this->selected;
        case 65:
            this->Previous();
            continue;
        case 66:
            this->Next();
            continue;
        default:
            continue;
        }
    }
}
int V_Kwd_Man::GetComandId(string msg){
    while(true){
        system("clear");
        cout << msg << endl;
        cout << this->ToString() << endl;
        char c = getch();
        switch (c){
        case 10:
            return this->selected;
        case 65:
            this->Previous();
            continue;
        case 66:
            this->Next();
            continue;
        default:
            continue;
        }
    }
}