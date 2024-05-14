#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>




using namespace std;

struct Item {
    string name;
    int quantity;
    float price;
};

class Inventory {
    map<string, vector<Item>> inventory;

public:
    void add(const string& category, const Item& item) {//добавляет что то
        inventory[category].push_back(item);
    }

    void update(const string& category, const string& itemName, const Item& updatedItem) {// обновляет инвентарь
        auto& items = inventory[category];
        for (auto& item : items) {
            if (item.name == itemName) {
                item = updatedItem;
                break;
            }
        }
    }

    void remov(const string& category, const string& itemName) {// удаляет определенный предмет
        auto& items = inventory[category];
        auto beforeSize = items.size();
        items.erase(remove_if(items.begin(), items.end(),
            [&](const Item& item) { return item.name == itemName; }),
            items.end());
        if (items.size() != beforeSize)
            cout << "Item removed successfully." << endl;
        else
            cout << "Item not found." << endl;
    }
    void removeCategory(const string& category){
        
        inventory.erase(category);
    }
    void show() {// показывает весь инвентарь
        for (const auto& category : inventory) {
            cout << "Category: " << category.first << endl;
            for (const auto& item : category.second) {
                cout << "Item: " << item.name << ", Quantity: " << item.quantity << ", Price: " << item.price << endl;
            }
            cout << endl;
        }
    }
    void save(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& category : inventory) {
                file << category.first << endl;
                for (const auto& item : category.second) {
                    file << item.name << " " << item.quantity << " " << item.price << endl;
                }
                file << endl;
            }
            file.close();
            cout << "Inventory saved to " << filename << " successfully." << endl;
        } else {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    void load(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            inventory.clear();
            string category;
            while (getline(file, category)) {
                vector<Item> items;
                string itemName;
                int quantity;
                float price;
                while (file >> itemName >> quantity >> price) {
                    items.push_back({itemName, quantity, price});
                }
                inventory[category] = items;
            }
            file.close();
            cout << "Inventory loaded from " << filename << " successfully." << endl;
        } else {
            cout << "Unable to open file " << filename << " for reading. Starting with empty inventory." << endl;
        }
    }
};

int main() {
    Inventory inventory;
    cout<<"Hello my friend I am your personal catalog Kiwi"<<endl;
    inventory.load("inventory.txt");//вспоминаем что раньше записывали
    while(true){
        string a;
        a="";
        
        cout<<"What do you want?"<<endl;
        cout<<"1.add something"<<endl;
        cout<<"2.update something"<<endl;
        cout<<"3.delete something"<<endl;
        cout<<"4.remove category"<<endl;
        cout<<"5.display all"<<endl;
        cout<<"6.exit"<<endl;
        cin>>a;
        if(a=="6"){
            inventory.save("inventory.txt");
            break;
        }

        string category, itemName;
        if(a=="1"){
            Item newItem;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter item name: ";
            cin >> newItem.name;
            cout << "Enter quantity: ";
            cin >> newItem.quantity;
            cout << "Enter price: ";
            cin >> newItem.price;
            inventory.add(category, newItem);
        }
        if(a=="2"){
            Item updatedItem;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter item name: ";
            cin >> itemName;
            cout << "Enter updated quantity: ";
            cin >> updatedItem.quantity;
            cout << "Enter updated price: ";
            cin >> updatedItem.price;
            inventory.update(category, itemName, updatedItem);
        }
        if(a=="3"){
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter item name: ";
            cin >> itemName;
            inventory.remov(category, itemName);
        }
        if(a=="4"){
            cout << "Enter category to remove: ";
            cin >> category;
            inventory.removeCategory(category);
        }
        if(a=="5"){
            inventory.show();
        }
        if(a >"6" or a<"1"){
            cout<<"We have problem try again"<<endl;
        }
    }
    return 0;
}