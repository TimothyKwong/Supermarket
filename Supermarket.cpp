#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

typedef map<string, int> Items;
typedef map<string, double> Item;

string capitalize(string s){
    s[0] = toupper(s[0]);
    return s;
}

class addRemoveEditItems{
    private:
        Items user_items;
        Item price_items;

        double totalCost; 

        void new_dictionary(){

        user_items["Bread"] = 0;
        user_items["Rice"] = 0;
        user_items["Beef"] = 0;
        user_items["Pork"] = 0;
        user_items["Milk"] = 0;
        user_items["Chicken"] = 0;
        user_items["Spinach"] = 0;
        user_items["Asparagus"] = 0;
        user_items["Lettuce"] = 0;
        user_items["Cheese"] = 0;

        price_items["Bread"] = 1.00;
        price_items["Rice"] = 10.00;
        price_items["Beef"] = 10.00;
        price_items["Pork"] = 9.00;
        price_items["Milk"] = 5.00;
        price_items["Chicken"] = 7.00;
        price_items["Spinach"] = 2.00;
        price_items["Asparagus"] = 2.00;
        price_items["Lettuce"] = 2.00;
        price_items["Cheese"] = 12.00; 
        }
    public:

        addRemoveEditItems() : totalCost(0.0) { new_dictionary(); }

        void printItems(){
            cout << "Products Menu" << endl;
            cout << "Bread: $1.00 per loaf" << endl;
            cout << "Rice: $10.00 per bag" << endl;
            cout << "Beef: $10.00 per pound" << endl;
            cout << "Pork: $9.00 per pound" << endl;
            cout << "Milk: $5.00 per bag" << endl;
            cout << "Chicken: $7.00 per pound" << endl;
            cout << "Spinach: $2.00 per bag" << endl;
            cout << "Asparagus: $2.00 per bag" << endl;
            cout << "Lettuce: $2.00 per bag" << endl;
            cout << "Cheese: $12.00 per block" << endl;
            cout << "\n";
        }
        void printCartItems(){
            cout << "Items in Cart: " << endl;
            for (map<string,int>::iterator it=user_items.begin(); it!=user_items.end(); ++it){
                if (it->second == 0){
                    cout << "";
                }else{
                    cout << it->first << " => " << it->second << '\n';
                }
            }
        }
        double bill(string item, int new_amount){
            user_items[item] = user_items[item] + new_amount;
            totalCost = 0;
            for (map<string,int>::iterator it=user_items.begin(); it!=user_items.end(); ++it){
                totalCost += it->second * price_items[it->first];
            }
            totalCost = totalCost * 1.13;
            return totalCost;
        }

        double getTotalCost(){
            return totalCost;
        }

        void resetTotalCost(){
            totalCost = 0;
        }

        void user_input(){
            string item;
            int amount;

            cout << "\nEnter: <Item> <Amount>  |  To Exit: Enter 'exit' during Item." << endl;

            do{
                cout << "Item: ";
                cin >> item;

                do{
                    cout << "Amount: ";
                    cin >> amount;
                }while((user_items[item] + amount) < 0);
                
                if(item != "exit"){
                    item = capitalize(item);                    
                    bill(item, amount);
                }

                cout << "Processing... " << endl; 
                cout << "\n";
                printCartItems();
                cout << "Current Bill: $";
                cout << fixed << showpoint;
                cout << setprecision(2);
                cout << totalCost << endl;
                cout << "============" << endl;
                cout << "\n";
            }while(item != "exit");
        }
};


class mainMenu{
    public:
        void printMainMenu(addRemoveEditItems &addRemoveEditItem){
            
            cout << "Main Menu" << endl;
            cout << "1. Add/Remove/Edit item(s)" << endl;
            cout << "2. Pay" << endl;
            cout << "3. Exit" << endl;
            cout << "\nCurrent Bill: $";
            cout << addRemoveEditItem.getTotalCost() << endl;
            }
};


bool is_number(const string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;

    return !s.empty() && it == s.end();
}

int userInput(){
    string userinput;
    do{
        do{
            cout << "\nEnter desired option: ";            
            cin >> userinput;
            //cout << is_number(userinput);
        }while(is_number(userinput) == 0);
    }while(stoi(userinput) < 1 && stoi(userinput) > 3);
    return stoi(userinput);
}


class PaymentOptions{
    public:
        void printPaymentOptions(){
            cout << "Payment Menu" << endl;
            cout << "1. Credit Card" << endl;
            cout << "2. Debit Card" << endl;
            cout << "3. Cash" << endl;
            //cout << "\n";
        }
        void userInputPaymentOptions(){
            userInput();
        }
        void printPaymentCompletion(addRemoveEditItems &addRemoveEditItem){
            cout << "Processing..." << endl;
            addRemoveEditItem.resetTotalCost();
            cout << "Current Bill: " << addRemoveEditItem.getTotalCost() << endl;
        }
};


int main(){
    mainMenu mainMenu;
    addRemoveEditItems addRemoveEditItem;
    PaymentOptions PaymentOptions;

    int userinput;

    do{
        cout << "\n\n";
        mainMenu.printMainMenu(addRemoveEditItem);

        userinput = userInput();
        cout << "Processing..." << endl;
        cout << "\n\n";

        switch (userinput){
            case 1:
                addRemoveEditItem.printItems();
                addRemoveEditItem.user_input();
                break;
            case 2:
                PaymentOptions.printPaymentOptions();
                PaymentOptions.userInputPaymentOptions();
                PaymentOptions.printPaymentCompletion(addRemoveEditItem);
                break;
        }
    } while(userinput != 3);

    cout << "Thank you for shopping." << endl;

    return 0;
}