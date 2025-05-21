#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    float balance;

public:
    BankAccount(string accHolderName, int accNumber) {
        name = accHolderName;
        accountNumber = accNumber;
        balance = 0.0;
    }

    void deposit(float amount) {
        balance += amount;
        cout << "?" << amount << " deposited. New Balance: ?" << balance << endl;
    }

    void withdraw(float amount) {
        if (amount > balance) {
            cout << "Insufficient balance.\n";
        } else {
            balance -= amount;
            cout << "?" << amount << " withdrawn. New Balance: ?" << balance << endl;
        }
    }

    void display() {
        cout << "Account Holder: " << name << "\nAccount Number: " << accountNumber << "\nBalance: ?" << balance << "\n";
    }

    int getAccountNumber() {
        return accountNumber;
    }

    void transfer(BankAccount &receiver, float amount) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer.\n";
        } else {
            balance -= amount;
            receiver.deposit(amount);
            cout << "?" << amount << " transferred to Account " << receiver.getAccountNumber() << endl;
        }
    }
};

vector<BankAccount> accounts;

BankAccount* findAccount(int accNumber) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == accNumber) {
            return &acc;
        }
    }
    return nullptr;
}

int main() {
    int choice;
    while (true) {
        cout << "\n========= Online Banking System =========\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Display Account\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int accNumber;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter New Account Number: ";
            cin >> accNumber;
            accounts.push_back(BankAccount(name, accNumber));
            cout << "Account Created!\n";

        } else if (choice == 2) {
            int accNumber;
            float amount;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            BankAccount* acc = findAccount(accNumber);
            if (acc) {
                cout << "Enter Amount to Deposit: ";
                cin >> amount;
                acc->deposit(amount);
            } else {
                cout << "Account Not Found!\n";
            }

        } else if (choice == 3) {
            int accNumber;
            float amount;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            BankAccount* acc = findAccount(accNumber);
            if (acc) {
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;
                acc->withdraw(amount);
            } else {
                cout << "Account Not Found!\n";
            }

        } else if (choice == 4) {
            int senderAcc, receiverAcc;
            float amount;
            cout << "Enter Your Account Number: ";
            cin >> senderAcc;
            BankAccount* sender = findAccount(senderAcc);
            if (!sender) {
                cout << "Sender Account Not Found!\n";
                continue;
            }
            cout << "Enter Receiver Account Number: ";
            cin >> receiverAcc;
            BankAccount* receiver = findAccount(receiverAcc);
            if (!receiver) {
                cout << "Receiver Account Not Found!\n";
                continue;
            }
            cout << "Enter Amount to Transfer: ";
            cin >> amount;
            sender->transfer(*receiver, amount);

        } else if (choice == 5) {
            int accNumber;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            BankAccount* acc = findAccount(accNumber);
            if (acc) {
                acc->display();
            } else {
                cout << "Account Not Found!\n";
            }

        } else if (choice == 6) {
            cout << "Thank you for banking with us.\n";
            break;

        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
