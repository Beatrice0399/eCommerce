#include <vector>
#include <iostream>
#include "../../../con2redis/src/con2redis.h"
#include "../../../con2db/pgsql.h"
#include <unistd.h>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <csignal>
#include <random>

using namespace std;

const int NTEST = 5;
const int NPRODUCTS = 10;

int main();

// Util

redisReply* GetFirstEntryElements(redisReply *reply);

// Test Vendor

vector<int> VendorRegistation(redisContext *redis);
void VendorCreateInsertion(redisContext *redis, vector<int> vendorIds);

// Test Customer

vector<int> CustomerRegistation(redisContext *redis);
void CustomerCreateOrder(redisContext *redis, Con2DB db, vector<int> customerIds);

// Test Transporter

vector<int> TransporterRegistration(redisContext *redis);
void TransporterNewShipping(redisContext *redis, vector<int> transporterIds);

// Data retrieve

vector<string> GetCustomerUsernameData(int NTEST);
vector<string> GetVendorUsernameData(int NTEST);
vector<string> GetPasswordData(int NTEST);
string GetEmailData(string name);
vector<string> GetVendorProductNameData(int NTEST);
float GetRandomPrice();
vector<string> GetCustomerShippingAddress(int NTEST);
vector<int> GetCustomerProductIds(Con2DB db, int size);

vector<string> GetTransporterUsernameData(int NTEST);


 