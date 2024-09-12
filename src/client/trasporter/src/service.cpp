#include "main.h"

int AuthenticationService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Registration", "Login", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    int flag;
    while(run){
        int comand = kwd.GetComandId();
        flag = ManageAuthenticationKwd(ctx, comand);
        if(flag == -1){run = false;}
        if(flag >= 0){break;}
    }
    return flag;
}

int MainService(Context ctx){
    bool run = true;
    Kwd_Man kwd = Kwd_Man({"New shipping", "My shippings", "Exit"});
    int flag;
    while(run){
        int comand = kwd.GetComandId();
        flag = ManageMainKwd(ctx, comand);
        if(flag == -1){return 0;}
    }
}

int NewShipping(Context ctx){
    Kwd_Man kwm = Kwd_Man({"Yes", "No"});
    int comand = kwm.GetComandId("Confirm new order\n\n");
    if(!comand){
        system("clear");
        bool flag = NewShippingOrder(ctx);
        if(!flag){cout << "Correctly got and order" << endl;}
        else{cout << "No orders available" << endl;}
    }
    return 0;
}

int MyShippings(Context ctx){ 
    while(true){
        vector<Shipping> shippings = GetShippings(ctx);
        int name_l = 4;
        int quantity_l = 4;
        int status_l = 6;
        int address_l = 7;
        for(int i = 0; i < shippings.size(); i++){
            Shipping s = shippings[i];
            if(s.GetProductName().length() > name_l){name_l = s.GetProductName().length();}
            if(to_string(s.GetQuantity()).length() > quantity_l){quantity_l = to_string(s.GetQuantity()).length();}
            if(s.GetStatus().length() > status_l){status_l = s.GetStatus().length();}
            if(s.GetShippingAddress().length() > address_l){address_l = s.GetShippingAddress().length();} 
        }
        vector<string> strings;
        for(int j = 0; j < shippings.size(); j++){
            strings.push_back(shippings[j].ToString(name_l, quantity_l, status_l, address_l));
        }
        strings.push_back("Back");
        V_Kwd_Man vkwm = V_Kwd_Man(strings);
        string indentation = GetTableIndentation(name_l, quantity_l, status_l, address_l);
        int comand = vkwm.GetComandId(indentation);
        if(comand == shippings.size()){return 0;}
        VisualizeShipping(ctx, shippings[comand]);
    }
    return 0;
}

int VisualizeShipping(Context ctx, Shipping s){
    while(true){
        string buf;
        buf.append("Shipping\n\n");
        buf.append("Customer name: ");
        buf.append(s.GetCustomerName());
        buf.append("\nProduct name: ");
        buf.append(s.GetProductName());
        buf.append("\nQuantity: ");
        buf.append(to_string(s.GetQuantity()));
        buf.append("\nAddress: ");
        buf.append(s.GetShippingAddress());
        buf.append("\n\nStatus: ");
        buf.append(s.GetStatus());
        buf.append("\n");

        Kwd_Man kwm = Kwd_Man({"Change status", "Back"});
        int comand = kwm.GetComandId(buf);
        if(comand == 1){return 0;}
        if(comand == 0){ChangeStatusService(ctx, s);}
    }
}

int ChangeStatusService(Context ctx, Shipping s){
    string buf;
    buf.append("Shipping\n\n");
    buf.append("Customer name: ");
    buf.append(s.GetCustomerName());
    buf.append("\nProduct name: ");
    buf.append(s.GetProductName());
    buf.append("\nQuantity: ");
    buf.append(to_string(s.GetQuantity()));
    buf.append("\nAddress: ");
    buf.append(s.GetShippingAddress());
    buf.append("\n\nStatus: ");
    buf.append(s.GetStatus());
    buf.append("\n\n");
    buf.append("Change status: ");

    Spinner spin = Spinner({"pendant", "delivering", "delivered"});
    int comand = spin.GetComandId(buf);
    if(ChangeStatus(ctx, s, comand)){Notification("Correctly changed the status");}
    else{Notification("Error while changing status");}
    return 0;
}
