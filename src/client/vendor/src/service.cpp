#include "main.h"

int AuthenticationService(Context ctx){
    bool run = true;
    Kwd_Man kwd = Kwd_Man({"Registration", "Login", "Exit"});
    int flag = -2;
    while(run){
        int comand = kwd.GetComandId();
        flag = ManageAuthenticationKwd(ctx, comand);
        if(flag == -1){
            run = false;
        }
        if(flag >= 0){
            break;
        }
    }
    return flag;
}

int MainService(Context ctx){
    bool run = true;
    Kwd_Man kwm = Kwd_Man({"Create insertion", "Visualize insertions", "Exit"});
    while(run){
        int comand = kwm.GetComandId();

        int flag = ManageMainKwd(ctx, comand);

        if(flag == -1){
            run = false;
            break;
        }
    }
    return 0;
}

int CreateInsertion(Context ctx){
    bool run = true;
    system("clear");

    cout << "Insert product name: ";
    string name;
    getline(cin, name);

    if(!StringIsInLenght(name, 2, 50)){
        Notification("Name lenght is out of range [2, 50]");
        return 0;
    }

    cout << "Insert product price: ";
    string price_str;
    getline(cin, price_str);

    float price;
    try{
        price = stof(price_str);
    } catch(exception e){
        Notification("Invalid price");
        return 0;
    }
    float tronc = round(price * pow(10, 2)) / pow(10, 2);

    string buf;
    buf.append("Recap product\n\n");
    buf.append("Name: ");
    buf.append(name);
    buf.append("\nPrice: ");
    buf.append(to_string(tronc));
    buf.append("$\n\nAdd this insertion?\n");

    Kwd_Man kw = Kwd_Man({"Yes", "no"});
    int comand = kw.GetComandId(buf);
    if(comand == 0){
        int flag = AddInsertion(ctx, name, tronc);
        if(flag == 0){
            Notification("Correctly created the insertion");
            return 0;
        }
        else{
            Notification("Error in database while creating the insertion");
            return 0;
        }
    }
    else if(comand == 1){
        Notification("Cancello il prodotto");
    }
    else{
        Notification("Invalid input");
        return 0;
    }
    return 0;
}

int VisualizeInsertion(Context ctx){
    vector<Insertion> insertions = GetInsertion(ctx);
    system("clear");
    cout << "Your insertions" << endl << endl;
    for(int i = 0; i < insertions.size(); i++){
        Insertion ins = insertions[i];
        cout << "Name: " << ins.GetName() << " Price: " << ins.GetPrice() << " Sales: " << ins.GetSales() << endl;
    }
    string comand;
    getline(cin, comand);
}