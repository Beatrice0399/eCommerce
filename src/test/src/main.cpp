#include "main.h"

int main(){
    srand(time(0));
    system("clear");
    redisContext *redis = redisConnect("localhost", 6379);
    Con2DB db("localhost", "5432", "ecommerce", "47002", "myecommerce");

    // Vendor test

    cout << "Vendor registration test:" << endl;
    sleep(1);
    vector<int> vendorIds = VendorRegistation(redis);

    cout << endl << endl << "Vendor create insertion test: " << endl;
    sleep(1);
    VendorCreateInsertion(redis, vendorIds);

    // Customer test
    
    cout << endl << endl << "Customer registration test:" << endl;
    sleep(1);
    vector<int> customerIds = CustomerRegistation(redis);

    cout << endl << endl << "Customer create order test:" << endl;
    sleep(1);
    CustomerCreateOrder(redis, db, customerIds);

    // Transporter test

    cout << endl << endl << "Transporter registratoin test:" << endl;
    sleep(1);
    vector<int> transporterIds = TransporterRegistration(redis);

    cout << endl << endl << "Transporter new shipping test:" << endl;
    sleep(1);
    TransporterNewShipping(redis, transporterIds);

    return 0;
}