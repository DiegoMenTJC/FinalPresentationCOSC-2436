// FinalPresentationCOSC-2436.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ============ Menu items ============
class MenuItem
{
public:
    int id;
    string name;
    double price;

    MenuItem()
    {
        id = 0;
        name = "";
        price = 0.0;
    }

    MenuItem(int id, string name, double price)
        :id(id), name(name), price(price)
    {}
};

// ============ Menu ============
class Menu
{
private:
    map<int, MenuItem> items;

public:
    void addItem(int id, string name, double price)
    {
        items[id] = MenuItem(id, name, price);
    }

    void removeItem(int id)
    {
        if (items.erase(id))
        {
            cout << "Item removed.\n";
        }
        else
        {
            cout << "Item not found.\n";
        }
    }

    void updatePrice(int id, double newPrice)
    {
        if (items.count(id))
        {
            items[id].price = newPrice;
            cout << "Price Updated\n";
        }
        else
        {
            cout << "Item not found.\n";
        }
    }

    void displayMenu()
    {
        cout << "======= Menu =======\n";
        cout << left << setw(5) << "ID" << setw(23) << "Item" << "Price\n";
        for (auto& pair : items)
        {
            cout << setw(5) << pair.second.id
                << setw(23) << pair.second.name
                << "$" << pair.second.price << "\n";
        }
    }

    bool exists(int id)
    {
        return items.count(id);
    }

    MenuItem getItem(int id)
    {
        return items[id];
    }

    //Save a file
    void saveToFile(string fileName)
    {
        ofstream file(fileName);
        for (auto& pair : items)
        {
            file << pair.second.id << ","
                << pair.second.name << ","
                << pair.second.price << "\n";
        }
        file.close();
    }

    //Load a file
    void loadFromFile(string fileName)
    {
        ifstream file(fileName);
        if (!file) 
        { 
            cout << "FNFE";
            return; 
        }
        
        items.clear();
        int id;
        string name;
        double price;
        char comma;

        while (file >> id >> comma)
        {
            getline(file, name, ',');
            file >> price;
            file.ignore();
            addItem(id, name, price);
        }

        file.close();
    }
};

// ============ Order ============
class Order
{
private:
    map<int, int> itemQuantities;
    vector<MenuItem> items;

public:
    void addItem(MenuItem item)
    {
        itemQuantities[item.id]++;
        items.push_back(item);
    }

    double calculateTotal()
    {
        double total = 0;
        for (auto& item : items)
        {
            total += item.price;
        }
        return total;
    }

    void displayOrder()
    {
        cout << "\n======= Order =======\n";
        map<int, int> counts;

        for (auto& item : items)
        {
            counts[item.id]++;
        }

        for (auto& pair : counts)
        {
            for (auto& item : items)
            {
                if (item.id == pair.first)
                {
                    cout << item.name << " x" << pair.second
                        << " - $" << item.price * pair.second << "\n";
                    break;
                }
            }
        }
        double subtotal = calculateTotal();
        double tax = subtotal * 0.0825;
        double total = subtotal + tax;

        cout << "\n";
        cout << fixed << setprecision(2);
        cout << "Subtotal: $" << subtotal << "\n";
        cout << "Tax: $" << tax << "\n";
        cout << "Total: $" << total << "\n";
    }

    void saveOrder(string fileName)
    {
        ofstream file(fileName, ios::app);
        file << calculateTotal() << "\n";
        file.close();
    }

    void clear()
    {
        items.clear();
        itemQuantities.clear();
    }
};

// ============ Sales ============
class Sales
{
public:
    static double getTotalSales(string fileName)
    {
        ifstream file(fileName);
        double total = 0; 
        double value;

        while (file >> value)
        {
            total += value;
        }

        file.close();
        return total;
    }
};

// ============ Input Validation ============
int getIntInput()
{
    int x;
    while (!(cin >> x))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input. Try again: ";
    }
    return x;
}

double getDoubleInput()
{
    double x;
    while (!(cin >> x))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input. Try again: ";
    }
    return x;
}

// ============ Admin Menu ============
void adminMenu(Menu& menu)
{
    int choice;

    do
    {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Item\n";
        cout << "2. Remove Item\n";
        cout << "3. Update Price\n";
        cout << "4. View Menu\n";
        cout << "5. Save Menu\n";
        cout << "0. Back\n";
        cout << "Choice: ";

        choice = getIntInput();

        cout << "\n";

        if (choice == 1)
        {
            int id;
            string name;
            double price;

            cout << "Enter ID: ";
            id = getIntInput();
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter price: ";
            price = getDoubleInput();

            menu.addItem(id, name, price);
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter ID: ";
            id = getIntInput();
            menu.removeItem(id);
        }
        else if (choice == 3)
        {
            int id;
            double price;
            cout << "Enter ID: ";
            id = getIntInput();
            cout << "New price: $";
            price = getDoubleInput();
            menu.updatePrice(id, price);
        }
        else if (choice == 4)
        {
            menu.displayMenu();
        }
        else if (choice == 5)
        {
            menu.saveToFile("Menu.txt");
            cout << "Menu saved.\n";
        }
    } while (choice != 0);
}

int main()
{
    Menu menu;
    Order order;

    menu.loadFromFile("Menu.txt");

    // default menu if file empty
    if (!menu.exists(1))
    {
        menu.addItem(1, "Burger", 5.99);
        menu.addItem(2, "Pizza", 8.99);
        menu.addItem(3, "Fries", 2.99);
        menu.addItem(4, "Drink", 1.99);
    }

    int choice;

    do
    {
        cout << "\n====== RESTAURANT SYSTEM ======\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item to Order\n";
        cout << "3. View Order\n";
        cout << "4. Checkout\n";
        cout << "5. Admin Mode\n";
        cout << "6. View Total Sales\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        choice = getIntInput();

        cout << "\n";

        if (choice == 1)
        {
            menu.displayMenu();
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter item id: ";
            id = getIntInput();

            if (menu.exists(id))
            {
                order.addItem(menu.getItem(id));
                cout << "Added to order!\n";
            }
            else
            {
                cout << "Invalid ID.\n";
            }
        }
        else if (choice == 3)
        {
            order.displayOrder();
        }
        else if (choice == 4)
        {
            order.displayOrder();
            order.saveOrder("sales.txt");
            order.clear();
            cout << "Order complete.\n";
        }
        else if (choice == 5)
        {
            string pass;
            cout << "Enter admin password: ";
            cin >> pass;

            if (pass == "admin123")
            {
                adminMenu(menu);
            }
            else
            {
                cout << "Wrong password.\n";
            }
        }
        else if (choice == 6)
        {
            double total = Sales::getTotalSales("sales.txt");
            cout << "Total Sales: $" << total << "\n";
        }

    } while (choice != 0);

    menu.saveToFile("menu.txt");

    cout << "Goodbye! See you soon!\n";

    return 0;
}