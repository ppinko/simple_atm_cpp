#include <iostream>
#include <map>

// global parameters
int balance = 0;

// all function prototypes
void showBalance();
bool isGoodPin(int pin, int account_no, std::map<int, int> *db);
int getUserOption();

void showBalance() {
    std::cout << "You have: $" << balance << std::endl;
}


bool isGoodPin(int pin, int account_no, std::map<int, int> *db){
    return (pin == db->at(account_no));
}

int getUserOption(){
	int selectedOption {};

	std::cout << "Main menu:" << std::endl;
	std::cout << " 1 - Show my balance" << std::endl;
	std::cout << " 2 - Withdraw cash" << std::endl;
	std::cout << " 3 - Deposit funds" << std::endl;
	std::cout << " 4 - Exit" << std::endl;
	std::cout << "Please enter a choice: " << std::endl;
	std::cin >> selectedOption;
	
	return selectedOption;	
}

int main(){
    // creating a database including initial account numbers and PIN
    std::map<int, int> *db_account_pin = new std::map<int, int>; 
    for (int i {10000}; i <= 99999; i++){
        db_account_pin->emplace(i, i);
    }
    showBalance();
    delete db_account_pin;
    return 0;
}