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
    switch (comand)
    {
    case 0:
        return SearchProduct(ctx);
    case 1:
        return VisualizeOrders(ctx);
    case 2:
        return -1;
    default:
        Notification("Invalid token");
        return -2;
    }
    return 0;
}


