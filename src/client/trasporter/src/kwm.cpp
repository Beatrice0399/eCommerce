#include "main.h"

Kwd_Man::Kwd_Man(vector<string> keywords){
    this->keywords = keywords; 
    this->size = this->keywords.size();
    this->selected = 0;
    }
string Kwd_Man::ToString(){
    string str;
    for(long unsigned int i = 0; i < this->keywords.size(); i++){
        if(this->selected == i){str.append("> ");}
        else{str.append("  ");}
        str.append(this->keywords[i]);
        str.append("   ");
    }
    return str;
}
void Kwd_Man::Next(){
    this->selected++;
    this->selected = this->selected % this->keywords.size();
}
void Kwd_Man::Previous(){
    if(this->selected == 0){
        this->selected = this->size;
    }
    this->selected -= 1;
}
int Kwd_Man::GetSelected(){
    return this->selected;
}
int Kwd_Man::GetComandId(){
    while(true){
        system("clear");
        cout << this->ToString() << endl;
        char c = getc();
        switch (c){
        case 10:
            return this->selected;
        case 67:
            this->Next();
            continue;
        case 68:
            this->Previous();
            continue;
        default:
            continue;
        }
    }
}
int Kwd_Man::GetComandId(string msg){
    while(true){
        system("clear");
        cout << msg << endl;
        cout << this->ToString() << endl;
        char c = getc();
        switch (c){
        case 10:
            return this->selected;
        case 67:
            this->Next();
            continue;
        case 68:
            this->Previous();
            continue;
        default:
            continue;
        }
    }
}