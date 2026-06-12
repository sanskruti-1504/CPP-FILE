#include <iostream>
#include <string>
using namespace std;
 

struct Account {
    int accountNumber;
    string name;
    string accountType; 
    double balance;
    Account* next; 
};
 

Account* head = NULL; 
int accountCounter = 1001; 
 

void createAccount() {
    
    Account* newAccount = new Account();
 
    newAccount->accountNumber = accountCounter++;
    
    cout << "\nEnter Name: ";
    cin.ignore();
    getline(cin, newAccount->name);
 
    cout << "Enter Account Type (Savings/Current): ";
    getline(cin, newAccount->accountType);
 
    cout << "Enter Initial Deposit Amount: ";
    cin >> newAccount->balance;
 
    newAccount->next = NULL;
 
    
    if (head == NULL) {
        head = newAccount;
    } else {
        
        Account* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAccount;
    }
 
    cout << "\n   Account Created Successfully!";
    cout << "\n   Your Account Number: " << newAccount->accountNumber << endl;
}
 

Account* findAccount(int accNo) {
    Account* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNo) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}
 

void depositMoney() {
    int accNo;
    double amount;
 
    cout << "\nEnter Account Number: ";
    cin >> accNo;
 
    Account* acc = findAccount(accNo);
 
    if (acc == NULL) {
        cout << " Account Not Found!\n";
        return;
    }
 
    cout << "Enter Amount to Deposit: ";
    cin >> amount;
 
    if (amount <= 0) {
        cout << " Invalid Amount!\n";
        return;
    }
 
    acc->balance += amount; 
    cout << " Deposit Successful! New Balance: " << acc->balance << endl;
}
 

void withdrawMoney() {
    int accNo;
    double amount;
 
    cout << "\nEnter Account Number: ";
    cin >> accNo;
 
    Account* acc = findAccount(accNo);
 
    if (acc == NULL) {
        cout << "Account Not Found!\n";
        return;
    }
 
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;
 
    if (amount <= 0) {
        cout << " Invalid Amount!\n";
        return;
    }
 
    if (amount > acc->balance) {
        cout << " Insufficient Balance!\n";
        return;
    }
 
    acc->balance -= amount; 
    cout << " Withdrawal Successful! New Balance: " << acc->balance << endl;
}
 

void checkBalance() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;
 
    Account* acc = findAccount(accNo);
 
    if (acc == NULL) {
        cout << "Account Not Found!\n";
        return;
    }
 
    cout << "\n--- Account Details ---\n";
    cout << "Account Number : " << acc->accountNumber << endl;
    cout << "Name           : " << acc->name << endl;
    cout << "Account Type   : " << acc->accountType << endl;
    cout << "Balance        : Rs. " << acc->balance << endl;
}
 

void showAllAccounts() {
    if (head == NULL) {
        cout << "\n No Accounts Found!\n";
        return;
    }
 
    cout << "\n========== ALL ACCOUNTS ==========\n";
    Account* temp = head;
    while (temp != NULL) {
        cout << "Account No : " << temp->accountNumber << endl;
        cout << "Name       : " << temp->name << endl;
        cout << "Type       : " << temp->accountType << endl;
        cout << "Balance    : Rs. " << temp->balance << endl;
        cout << "----------------------------------\n";
        temp = temp->next; 
    }
}
 

void deleteAccount() {
    int accNo;
    cout << "\nEnter Account Number to Delete: ";
    cin >> accNo;
 
    if (head == NULL) {
        cout << " No Accounts Found!\n";
        return;
    }
 
    
    if (head->accountNumber == accNo) {
        Account* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << " Account Deleted Successfully!\n";
        return;
    }
 
    
    Account* prev = head;
    Account* curr = head->next;
 
    while (curr != NULL) {
        if (curr->accountNumber == accNo) {
            prev->next = curr->next; 
            delete curr;
            cout << " Account Deleted Successfully!\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
 
    cout << " Account Not Found!\n";
}
 

void transferMoney() {
    int fromAcc, toAcc;
    double amount;
 
    cout << "\nEnter Your Account Number: ";
    cin >> fromAcc;
    cout << "Enter Receiver Account Number: ";
    cin >> toAcc;
 
    Account* from = findAccount(fromAcc);
    Account* to = findAccount(toAcc);
 
    if (from == NULL || to == NULL) {
        cout << " One or both accounts not found!\n";
        return;
    }
 
    cout << "Enter Amount to Transfer: ";
    cin >> amount;
 
    if (amount > from->balance) {
        cout << " Insufficient Balance!\n";
        return;
    }
 
    from->balance -= amount;
    to->balance += amount;
 
    cout << " Transfer Successful!\n";
    cout << "   Your New Balance: Rs. " << from->balance << endl;
}
 

int main() {
    int choice;
 
    cout << "====================================\n";
    cout << "   Welcome to Bank Management System\n";
    cout << "====================================\n";
 
    while (true) {
        cout << "\n========== MENU ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Transfer Money\n";
        cout << "6. Show All Accounts\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
 
        switch (choice) {
            case 1: createAccount();    break;
            case 2: depositMoney();     break;
            case 3: withdrawMoney();    break;
            case 4: checkBalance();     break;
            case 5: transferMoney();    break;
            case 6: showAllAccounts();  break;
            case 7: deleteAccount();    break;
            case 8:
                cout << "\nThank you for using Bank Management System!\n";
                return 0;
            default:
                cout << " Invalid Choice! Try Again.\n";
        }
    }
 
    return 0;
}