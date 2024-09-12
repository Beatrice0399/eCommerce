#include "main.h"

Spinner::Spinner(vector<string> keywords){
    this->keywords = keywords; 
    this->size = this->keywords.size();
    this->selected = 0;
    }

string Spinner::ToString(){
    string str;
    str.append("<");
    str.append(this->keywords[this->selected]);
    str.append(">");
    return str;
}
void Spinner::Next(){
    this->selected++;
    this->selected = this->selected % this->keywords.size();
}
void Spinner::Previous(){
    if(this->selected == 0){
        this->selected = this->size;
    }
    this->selected -= 1;
}
int Spinner::GetSelected(){
    return this->selected;
}
int Spinner::GetComandId(){
    while(true){
        system("clear");
        cout << this->ToString();
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
int Spinner::GetComandId(string msg){
    while(true){
        system("clear");
        cout << msg << flush;
        cout << this->ToString() << endl << flush ;
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