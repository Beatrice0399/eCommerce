#include "main.h"

vector<int> VendorRegistation(redisContext *redis){
    vector<int> vendorIds;
    vector<string> vendorUsernames = GetVendorUsernameData(NTEST);
    vector<string> vendorPasswords = GetPasswordData(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = vendorUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = vendorPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetEmailData(username);
        cout << "Email: " << email << ";\tResult: ";

        // Redis command test
        redisReply *reply = (redisReply*)redisCommand(redis, "XADD vendor * operation_id 1 username %s password %s email %s", username.c_str(), email.c_str(), password.c_str());
        string rid = reply->str;

        // Getting result
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("1")){
            cout << "SUCCESS" << endl;
            int id = stoi(GetFirstEntryElements(reply)->element[3]->str); 
            vendorIds.push_back(id);
            } 
        else{cout << "USER ALREADY EXISTS" << endl;}
    }
    return vendorIds;
}

void VendorCreateInsertion(redisContext *redis, vector<int> vendorIds){
    int size = vendorIds.size();

    vector<string> productNames = GetVendorProductNameData(size);

    for(int i = 0; i < size; i++){
        cout << "Test n." << i + 1 << ";\t";
        int id = vendorIds.at(i);
        cout << "Vendor id: " << id << ";\t";
        string name = productNames.at(i);
        cout << "Product name: " << name << ";\t";
        float price = GetRandomPrice();
        cout << "Price: " << price << ";\tResult: ";

        // Redis command test
        redisReply *reply = (redisReply*) redisCommand(redis, "XADD vendor * operation_id 2 product_name %s price %.2f id_vendor %d", name.c_str(), price, id);
        string rid = reply->str;

        // Getting result
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("3")){cout << "SUCCESS" << endl;} 
        else{cout << "FAIL" << endl;}

    }
    return;
}

vector<int> CustomerRegistation(redisContext *redis){
    vector<int> customerIds;
    vector<string> CustomerUsernames = GetCustomerUsernameData(NTEST);
    vector<string> CustomerPasswords = GetPasswordData(NTEST);
    vector<string> CustomerAddresses = GetCustomerShippingAddress(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = CustomerUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = CustomerPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetEmailData(username);
        cout << "Email: " << email << ";\t";
        string sa = CustomerAddresses.at(i);
        cout << "Shipping Address: " << sa << ";\tResult:";

        redisReply *reply = (redisReply*)redisCommand(redis, "XADD customer * operation_id 1 username %s password %s email %s shipping_address %s", username.c_str(), email.c_str(), password.c_str(), sa.c_str());
        string rid = reply->str;
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("1")){
            cout << "SUCCESS" << endl;
            int id = stoi(GetFirstEntryElements(reply)->element[3]->str); 
            customerIds.push_back(id);
            } 
        else{cout << "USER ALREADY EXISTS" << endl;}
    }
    return customerIds;
}

void CustomerCreateOrder(redisContext *redis, Con2DB db, vector<int> customerIds){
    int size = customerIds.size();

    vector<int> productIds = GetCustomerProductIds(db, size);
    
    for(int i = 0; i < size; i++){
        cout << "Test n." << i + 1 << ";\t";
        int id = customerIds.at(i);
        cout << "Customer id: " << id << ";\t";
        int product_id = productIds.at(i);
        cout << "Product id: " << product_id << ";\t";
        int quantity = rand() % 10;
        cout << "Quantity: " << quantity << ";\tResult: ";

        // Send Redis Test
        redisReply* reply = (redisReply*) RedisCommand(redis, "XADD customer * operation_id 2 id_product %d quantity %d id_customer %d", product_id, quantity, id);
        string rid = reply->str;

        // Receive Redis Answer
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("3")){cout << "SUCCESS" << endl;} 
        else{cout << "FAIL" << endl;}
    }
}

vector<int> TransporterRegistration(redisContext *redis){
    vector<int> transporterIds;
    vector<string> TransporterUsernames = GetTransporterUsernameData(NTEST);
    vector<string> TransporterPasswords = GetPasswordData(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = TransporterUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = TransporterPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetEmailData(username);
        cout << "Email: " << email << ";\t";

        redisReply *reply = (redisReply*)redisCommand(redis, "XADD transporter * operation_id 1 username %s password %s email %s", username.c_str(), email.c_str(), password.c_str());
        string rid = reply->str;
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("1")){
            cout << "SUCCESS" << endl;
            int id = stoi(GetFirstEntryElements(reply)->element[3]->str); 
            transporterIds.push_back(id);
            } 
        else{cout << "USER ALREADY EXISTS" << endl;}
    }
    return transporterIds;
}

void TransporterNewShipping(redisContext *redis, vector<int> transporterIds){
    int size = transporterIds.size();

    for (int i = 0; i < size; i++){
        cout << "Test n." << i + 1 << ";\t";
        int id = transporterIds.at(i);
        cout << "Transporter id: " << id << ";\tResult: ";

        // Send Redis Request
        redisReply* reply = (redisReply*) RedisCommand(redis, "XADD transporter * operation_id 4 id_transporter %d", id);
        string rid = reply->str;

        // Receive Redis Answer
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("3")){cout << "SUCCESS" << endl;} 
        else if(!result.compare("4")){cout << "NO ORDER AVAILABLE" << endl;}
        else{cout << "FAIL" << endl;}
    }
}
