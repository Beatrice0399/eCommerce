#include "main.h"
#include <atomic>
#include <termios.h>

/*
std::atomic<bool> shouldExit(false); // Variabile atomica per indicare se il programma deve uscire

bool kbhit() {
    timeout(0); 
    int ch = getch();
    timeout(-1); 
    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

// Funzione per gestire l'input da tastiera in un thread separato
void listener() {
    while (!shouldExit) {
        if (kbhit()) {
            char ch = getch(); // Legge il tasto premuto
            if (ch == 27) { // Tasto ESC
                shouldExit = true; 
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}



// Funzione per leggere un carattere da tastiera
char my_getch() {
    return static_cast<char>(wgetch(stdscr));
}
*/

/*
redis server listening requests from redis vendor client.
*/
int main(){
    /*
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    */ 
    redisContext *redis = redisConnect("localhost", 6379);
    system("clear");
    // std::thread inputThread(listener);
    while(true) {   
        redisReply *reply = (redisReply*) redisCommand(redis, "XRANGE transporter - + COUNT 1");
        if (reply->elements != 0){
            redisReply *prima_reply = reply->element[0];
            string id_entry = prima_reply->element[0]->str;
            string operation = prima_reply->element[1]->element[1]->str;  
            switch (stoi(operation))
                {
                case 1: 
                    cout << "Registrazione" << endl;
                    newRegistrationMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, prima_reply->element[1]->element[7]->str, redis);
                    break;
                case 2:
                    cout << "Change shipping status" << endl;
                    changeShippingStatusMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, redis);
                    break;
                case 3: 
                    cout << "Login" << endl;   
                    loginMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, redis); 
                    break;
                case 4:
                    cout << "Request new Shipping" << endl;
                    requestShippingMsg(id_entry, prima_reply->element[1]->element[3]->str, redis);
                }
            redisCommand(redis, "XDEL transporter %s", id_entry.c_str());
        }
    } 
    // inputThread.join();
    // endwin();
    return 0;
}