#include <iostream>
#include <map>

int main(){
    // creating a database including initial account numbers and PIN
    std::map<int, int> *db_account_pin = new std::map<int, int>; 
    for (int i {10000}; i <= 99999; i++){
        db_account_pin->emplace(i, i);
    }

    delete db_account_pin;
    return 0;
}