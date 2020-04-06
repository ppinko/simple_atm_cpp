#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <sstream>

// global parameters
int balance = 0;

// all function prototypes
void showBalance();
bool isGoodPin(int pin, int account_no, std::map<int, int> *db);
bool isValidAccount(int account_no, std::map<int, int> *db);
int getUserOption();
bool login (std::map<int, int> *db);
void withdrawCash();
bool isNumber(std::string selection);

void showBalance() {
    std::cout << "You have: $" << balance << std::endl;
}

bool isGoodPin(int pin, int account_no, std::map<int, int> *db){
    return (pin == db->at(account_no));
}

bool isValidAccount(int account_no, std::map<int, int> *db){
    return (db->find(account_no) != db->end());
}

int getUserOption(){
	int choosenOption {};

	std::cout << "Main menu:" << std::endl;
	std::cout << " 1 - Show my balance" << std::endl;
	std::cout << " 2 - Withdraw cash" << std::endl;
	std::cout << " 3 - Deposit funds" << std::endl;
	std::cout << " 4 - Exit" << std::endl;
	std::cout << "Please enter a choice: " << std::endl;
	std::cin >> choosenOption;

	return choosenOption;
}

bool login (std::map<int, int> *db) {
	std::cout << "Welcome!" << std::endl;
    int account_number {};
    while (true){
        std::cout << "Please enter your account number: ";
        std::string givenAccountNumber {};
		std::cin >> givenAccountNumber;
        std::istringstream iss {givenAccountNumber};
        int temp;
        try {
            if (!(iss >> temp))
                throw 0;
        }
        catch (const int &ex){
            std::cerr << "Inavlid input. Account number consists 5 digits.\n";
            continue;
        }
        iss >> temp;
        if (isValidAccount(temp, db)){
            account_number = temp;
            break;
        }
        else {
            std::cout << "Inavlid input. Account number consists 5 digits.\n" << std::endl;
        }
    }
    int initial_PIN {};
    while (true){
        std::cout << "Please enter your PIN: ";
        std::string givenPIN {};
		std::cin >> givenPIN;
        std::istringstream iss {givenPIN};
        int temp;
        try {
            if (!(iss >> temp))
                throw 0;
        }
        catch (const int &ex){
            std::cerr << "Inavlid input. PIN consists 5 digits.\n";
            continue;
        }
        iss >> temp;
        if (isGoodPin(temp, account_number, db)){
            initial_PIN = temp;
            break;
        }
        else std::cout << "Wrong PIN! Try again." << std::endl;
    }
    std::cout << "User with account number " << account_number << " is logged." << std::endl;
	return true;
}

bool isNumber(std::string selection){
    std::istringstream iss {selection};
    int test {};
    if (iss >> test) return true;
    return false;
}

void withdrawCash() {

	int selectedOption = -1;
	int valueToWithdraw = 0;
	bool isNotFinished = true;
	int otherValue {};

	do {
		std::cout << "Withdrawal options:" << std::endl;
		std::cout << "1 - $20" << std::endl;
		std::cout << "2 - $50" << std::endl;
		std::cout << "3 - $100" << std::endl;
		std::cout << "4 - $200" << std::endl;
		std::cout << "5 - other" << std::endl;
		std::cout << "6 - cancel transaction" << std::endl;
		std::cout << "choose a withdrawal option (1-6)" << std::endl;
        std::string checkInput;
        std::cin >> checkInput;
        if (!isNumber(checkInput)){
            std::cout << "Invalid option! Try again." << std::endl;
            continue;
        }
		int selectedOption = std::stoi(checkInput);
		switch (selectedOption) {
			case 1: valueToWithdraw = 20; break;
			case 2: valueToWithdraw = 50; break;
			case 3: valueToWithdraw = 100; break;
			case 4: valueToWithdraw = 200; break;
			case 5: valueToWithdraw = 200; break;
			case 6: isNotFinished = false; break;
			default:
                std::cout << "Invalid option! Try again." << std::endl;
				break;
		}

		if (valueToWithdraw != 0) {
			if (valueToWithdraw > balance) {
				std::cout << "You just have $" << balance << ". You can't withdraw $"
				<< valueToWithdraw << std::endl;
			} else {
				balance = balance - valueToWithdraw;
				isNotFinished = false;
			}
			valueToWithdraw = 0;
		}
	} while (isNotFinished);
}

int main(){
    std::cout << std::boolalpha;

    // creating a database including initial account numbers and PIN

    std::map<int, int> *db_account_pin = new std::map<int, int>;
    for (int i {10000}; i <= 99999; i++){
        db_account_pin->emplace(i, i);
    }

//    // Test isValidAccount()

//    std::cout << isValidAccount(12345, db_account_pin) << " should be true" << std::endl;
//    std::cout << isValidAccount(1234, db_account_pin) << " should be false" << std::endl;

//    // Test login()
//    login(db_account_pin);

//    // Test isNumber()
//    std::cout << isNumber("hejka") << " should return false" << std::endl;
//    std::cout << isNumber("123") << " should return true" << std::endl;

    // Test withdrawCash()
    withdrawCash();

    delete db_account_pin;
    return 0;
}
