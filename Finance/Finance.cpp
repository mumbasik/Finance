#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

struct Date {
    unsigned day;
    unsigned month;
    unsigned year;
    void Outpuut() const {
        cout << "Day: " << day << endl;
        cout << "Month : " << month << endl;
        cout << "Year: " << year << endl;
    }
    void Input() {
        cout << "Enter a day: " << endl;
        cin >> day;
        cout << "Enter a month: " << endl;
        cin >> month;
        cout << "Enter a year: " << endl;
        cin >> year;
    }
};
class MoneyStorage;

class Spending {
    int money;
   string category; // 1 - groceries, 2 - automotive, 3 - pet supplies, 4 - sports goods, 5 - household goods, 6 - construction goods, 7 - dining out, 8 - entertainment
    Date date;

public:
    Spending() {

    }
    Spending(float mon, int cat, Date d);
   
    void Input() {
        cout << "Enter the balance of money you want to spend: " << endl;
        cin >> money;
       
        date.Input();
        cout << "Enter the category" << endl;
        cin >> category;
    }

    int GetMoney() const {
        return money;
    }

    string GetCategory() const {
        return category;
    }

    bool operator<(const Spending& b) const {
        return date.year < b.date.year ||
            (date.year == b.date.year && (date.month < b.date.month ||
                (date.month == b.date.month && date.day < b.date.day)));
    }

    const Date& GetDate() const {
        return date;
    }
    
};

Spending::Spending(float mon, int cat, Date d) {
    money = mon;
    category = cat;
    date = d;
}

class MoneyStorage {
protected:
    long long number;
    float totalMoney;
    multiset<Spending> spendings;
    float creditLimit; 
    int CVV;

public:
    MoneyStorage() : totalMoney(0), creditLimit(0) {}

    MoneyStorage(int cvv, long long num, float credit) : number(num), totalMoney(0), creditLimit(credit) {}

    virtual void Output() = 0;

    virtual void ToUp() = 0;
    virtual void Input() = 0;
    
    void AddSpend();

    virtual int GetCVV() = 0;

    
    

    virtual long long GetNumber() const = 0;
    float TotalMoney() {
        return totalMoney;
    }
    void SaveSpendings(const multiset<Spending>& spendings);
    virtual multiset<Spending> GetSpendings() const = 0;
    
    
};


void MoneyStorage::AddSpend() {
    Spending spend;

    if (TotalMoney() == 0) {
        cout << "You have 0 money: " << endl;
        cout << "You want to replish your storage? : 1) - yea. 2) - no" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {

            ToUp();
            return;
        }

        else {
            cout << "Anayway you need to replish your storage to make buys! " << endl;
            return;
            
        }
        
        

    }
    spend.Input();
    spendings.insert(spend);
    cout << "Successfully! " << endl;

    totalMoney -= spend.GetMoney();
    
}
void MoneyStorage::SaveSpendings(const multiset<Spending>& spendings) {
    ofstream file("saveSpend.txt", ios::app);
    if (!file) {
        cout << "Can't open this file " << endl;
        return;
    }
    for (auto& spend : spendings) {
        file << "Money spent " << spend.GetMoney() << endl;
        file << "Category for spend " << spend.GetCategory() << endl;
        const Date& date = spend.GetDate();
        file << "Date of spending  " << endl;
        file << "Day: " << date.day << endl;
        file << "Month: " << date.month << endl;
        file << "Year: " << date.year << endl;
        file << "Storage: " << GetNumber() << endl;
        file << endl;

    }
    file.close();
}
class Card : public MoneyStorage {

    string bankName;

public:
    Card() {}

    Card(int cvv, long long num, float credit, string name) : MoneyStorage(cvv, num, credit), bankName(name) {}

    void Input()  override {
        cout << "Enter number of the card: " << endl;
        cin >> number;

        while (to_string(number).length() != 16) {
            cout << "Number is lower that 16 or higher, try again! " << endl;
            cin >> number;

        }
        cout << "What is the credit limit? " << endl;
        cin >> creditLimit;
        if (creditLimit > 0) {
            cout << "This is a credit card" << endl;
        }
        else {
            cout << "This is a debit card" << endl;
        }
        cout << "Make up secret CVV code for your storage: " << endl;
        cin >> CVV;
        while (to_string(CVV).length() != 3) {
            cout << "Number is lower that 3 or higher, try again! " << endl;
            cin >> CVV;
        }
        cout << "Enter a name of this card: " << endl;
        cin.ignore();
        getline(cin, bankName);
    }

    void ToUp() override{
        int amount = 0;
        cout << "Enter the amount you want to replenish: " << endl;
        cin >> amount;
        totalMoney += amount;
        cout << "Successfully! " << endl;
    }

    void Output() override {
        cout << "Number of the storage: " << number << endl;
        cout << "Total money of this storage: " << totalMoney << endl;
        cout << "Name  of this card: " << bankName << endl;
        cout << "CVV cod: " << CVV << endl;
    }
    multiset<Spending> GetSpendings() const override {
        return spendings;
    }
   
    int GetCVV() override {
        return CVV;
    }
    long long GetNumber() const override {
        return number;
    }
    
   
};

class Wallet : public MoneyStorage {
    string walletType;

public:
    Wallet() {}

    Wallet(int cvv, long long num, float credit, string type) : MoneyStorage(cvv, num, credit), walletType(type) {}

    void Input()  override {
        cout << "Enter number of the wallet: " << endl;
        cin >> number;

        while (to_string(number).length() != 4) {
            cout << "Number is lower that 4 or higher, try again! " << endl;
            cin >> number;

        }
        
        cout << "What is the credit limit? " << endl;
        cin >> creditLimit;
        if (creditLimit > 0) {
            cout << "This is a credit wallet" << endl;
        }
        else {
            cout << "This is a debit wallet" << endl;
        }
        cout << "Make up secret CVV code for your storage: " << endl;
        cin >> CVV;
        while (to_string(CVV).length() != 3) {
            cout << "Number is lower that 3 or higher, try again! " << endl;
            cin >> CVV;
        }
        cout << "Enter a name of wallet: " << endl;
        cin.ignore();
        getline(cin, walletType);
    }

    void ToUp() override{
        int amount = 0;
        cout << "Enter the amount you want to replenish: " << endl;
        cin >> amount;
        totalMoney += amount;
        cout << "Successfully! " << endl;
    }

    void Output() override {
        cout << "Number of the storage: " << number << endl;
        cout << "Total money of this storage: " << totalMoney << endl;
        cout << "Name of wallet: " << walletType << endl;
        cout << "CVV cod: " << CVV << endl;
        
        
    }
    multiset<Spending> GetSpendings() const override {
        return spendings;
    }
    int GetCVV() override {
        return CVV;
    }
    long long GetNumber() const override {
        return number;
    }
};

class FinanceManagement   {
   
    multimap<long long, int> counter;
   

    

public:
    FinanceManagement() {}

    void AddStorage(MoneyStorage* ptr, MoneyStorage* pt) {
        cout << "Enter the date of adding " << endl;
        Date d;
        d.Input();
        int choice;
        cout << "Which storage you want to add? - 1) (Card) - 2) (Wallet) " << endl;
        cin >> choice;

        if (choice == 1) {
            MoneyStorage* storage = new Card();
            cout << "Make up the number of your card " << endl;
            ptr->Input();
            for (auto it = counter.begin(); it != counter.end(); ++it) {
                if (ptr->GetNumber() == it->first) {
                    cout << "This number of card is already exits in BASE" << endl;
                    return;
                }
            }

            cout << "Your storage have been created! " << endl;
            cout << "Data: " << endl;
            ptr->Output();

            d.Outpuut();
            counter.insert(make_pair(ptr->GetNumber(), ptr->GetCVV()));
        }
        else if (choice == 2) {
            MoneyStorage* storage = new Wallet();
            cout << "Make up the number of your card " << endl;
            pt->Input();
            for (auto it = counter.begin(); it != counter.end(); ++it) {
                if (pt->GetNumber() == it->first) {
                    cout << "This number of wallet is already exits in BASE" << endl;
                    return;
                }
            }
            cout << "Your storage have been created! " << endl;
            cout << "Data: " << endl;
            pt->Output();

            d.Outpuut();
            counter.insert(make_pair(pt->GetNumber(), pt->GetCVV()));
        }

        else  {
            cout << "Wrong symbols " << endl;
        }
       
        
       



       
    }

   

    void Cout(MoneyStorage* pt, MoneyStorage* ptr) {
        if (counter.empty()) {
            cout << "Did not found any storages! " << endl;
            return;
        }
        long long numb;
        cout << "Enter number of this storage: " << endl;
        
        cin >> numb;
        multimap<string, string>::iterator it;
        bool find = false;
        for (auto it = counter.begin(); it != counter.end(); ++it) {


           
                if (numb == pt->GetNumber()) {
                    pt->Output();
                    find = true;
                    break;
                }
                else if (numb == ptr->GetNumber()) {
                    ptr->Output();
                    find = true;
                    break;
                }
            
           
        }
        
            if (!find) {
                cout << "Unknown storage: " << endl;
                cout << "Forget your number of storage? " << endl;
                cout << "Try to find by CVV cod: " << endl;
                int number;
                cin >> number;
                if (number == pt->GetCVV()) {
                    cout << "Card found: " << endl;
                    pt->Output();
                }
                else if (number == ptr->GetCVV()) {
                    cout << "Wallet found: " << endl;
                    ptr->Output();
                }
                else if (number != pt->GetCVV() || number != ptr->GetCVV()) {
                    cout << "Maybe this storage does not exist! " << endl;
                }
            
        }

        

    }
    
    void UpStorage( MoneyStorage* ptr, MoneyStorage* pt) {
        if (counter.empty()) {
            cout << "Did not found any storages! " << endl;
            return;
        }
        cout << "Enter the number of storage: " << endl;
        long long numb;
        cin >> numb;
        multimap<string, string>::iterator it;
        bool find = false;
       
        
        for (auto it = counter.begin(); it != counter.end(); ++it) {
            
               
            
            if (numb == ptr->GetNumber()) {
                ptr->ToUp();
                find = true;
                return;
            }
            else if (numb == pt->GetNumber()) {
                pt -> ToUp();
                find = true;
                return;
            }
           
        }
        if (!find) {
            cout << "Unknown storage: " << endl;
            cout << "Forget your number of storage? " << endl;
            cout << "Try to find by CVV cod " << endl;
            int number;
            cin >> number;
            if (number == ptr->GetCVV()) {
                cout << "Card found " << endl;
                ptr->ToUp();
                return;
            }
            else if (number == pt->GetCVV()) {
                cout << "Wallet found " << endl;
                pt->ToUp();
                return;
            }
            else {
                cout << "Maybe this storage does not exist! " << endl;
            }
        }

       
    }

    void AddSpendingToStorage(MoneyStorage* ptr, MoneyStorage* pt) {
        if (counter.empty()) {
            cout << "Did not found any storages! " << endl;
            return;
        }
        cout << "Enter the number of storage " << endl;
        long long numb;
        bool find = false;
        cin >> numb;
        multimap<string, string>::iterator it;

        for (auto it = counter.begin(); it != counter.end(); ++it) {
            
                if (numb == ptr->GetNumber()) {
                    ptr->AddSpend();
                    find = true;
                    ptr->SaveSpendings(ptr->GetSpendings());
                    return;
                }
                 if (numb == pt->GetNumber()) {
                    pt->AddSpend();
                    find = true;
                   pt-> SaveSpendings(pt->GetSpendings());
                   return;
                }
               
                
            
           
        }
        if (!find) {
            cout << "Unknown storage: " << endl;
            cout << "Forget your number of storage? " << endl;
            cout << "Try to find by CVV cod: " << endl;
            int number;
            cin >> number;
            if (number == ptr->GetCVV()) {
                cout << "Card found " << endl;
                ptr->AddSpend();
                ptr->SaveSpendings(ptr->GetSpendings());
                return;
            }
            else if (number == pt->GetCVV()) {
                cout << "Wallet found " << endl;
                pt->AddSpend();
                pt->SaveSpendings(pt->GetSpendings());
                return;
            }
            else {
                cout << "Maybe this storage does not exist! " << endl;
            }
        }
       
        
    }

    void DeleteStorage(MoneyStorage* ptr, MoneyStorage* pt) {
        if (counter.empty()) {
            cout << "Did not found any storages! " << endl;
            return;
        }
        int numb;
        bool found = false;
        cout << "Enter a CVV cod of storage you want to delete: " << endl;
        cin >> numb;
        for (auto it = counter.begin(); it != counter.end(); ++it) {
            if (numb == ptr->GetCVV()) {
                counter.erase(it);
                cout << "Storage by this CCV code deleted! " << endl;
                return;
            }
            else if (numb == pt->GetCVV()) {
                counter.erase(it);
                cout << "Storage by this CCV code deleted! " << endl;
                return;
            }
        }
        cout << "Unknown Storage: " << endl;

        if (!found) {
            cout << "Unknown Storage: " << endl;
        }
    }


};

int main() {
   
    MoneyStorage* stor_ptr1;
    MoneyStorage* stor_ptr2;

   
   
   
    stor_ptr1 = new Card(123, 5555555555555555, 2000, "unknown");
    stor_ptr2 = new Wallet(231, 11111, 1000, "unknown");
   

    FinanceManagement system;
    
   
    
    /*system.Output();*/
    unsigned operation;
    do {
        cout << "-----------------------------|\n";
        cout << "Choose operation             |\n";
        cout << "1 - AddStorage               |\n";  
        cout << "2 - ToUp                     |\n";  
        cout << "3 - Show storages            |\n";  
        cout << "4 - AddSpending              |\n";  
        cout << "5 - DeleteStorage            |\n";
        cout << "6 - Exit                     |\n";
    
        cout << "-----------------------------|\n";
        cin >> operation;
        switch (operation) {
        case 1:
            system.AddStorage(stor_ptr1, stor_ptr2);
            break;
        case 2:
            system.UpStorage(stor_ptr1, stor_ptr2);

            break;
        case 3:
            system.Cout(stor_ptr1, stor_ptr2);
            break;
        case 4:
            system.AddSpendingToStorage(stor_ptr1, stor_ptr2);
            break;
        case 5:
            system.DeleteStorage(stor_ptr1, stor_ptr2);
            break;
        case 6:
            cout << "bye!\n";
            break;
        default:
            cout << "This operation does not exist!\n";
        }
    } while (operation != 11);
    return 0;
}



