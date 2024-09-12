#include "main.h"

int ManageAuthenticationKwd(Context ctx, int comand){
    switch (comand)
    {
    case 0:
        return Registration(ctx);
    case 1:
        return Login(ctx);
    case 2:
        return -1;
    default:
        Notification("Invalid token");
        return -2;
    }
    return 0;
}

int ManageMainKwd(Context ctx, int comand){
    int flag = 0;
    switch (comand)
    {
    case 0:
        flag = NewShipping(ctx);
        break;
    case 1:
        flag = MyShippings(ctx);
        break;
    case 2:
        return -1;
    default:
        break;
    }
    return flag;
}