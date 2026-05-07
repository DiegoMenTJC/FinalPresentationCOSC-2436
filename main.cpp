// FinalPresentationCOSC-2436.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <string>

#include "Menu.h"
#include "Order.h"
#include "Sales.h"
#include "InputValidation.h"

// ============ Admin Menu ============
void adminMenu(Menu& menu)
{
    int choice;

    do
    {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Update Price\n";
        std::cout << "4. View Menu\n";
        std::cout << "5. Save Menu\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        choice = InputValidation::getInput<int>();

        std::cout << "\n";

        if (choice == 1)
        {
            int id;
            std::string name;
            double price;

            std::cout << "Enter ID: ";
            id = InputValidation::getInput<int>();
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter price: ";
            price = InputValidation::getInput<double>();

            menu.addItem(id, name, price);
        }
        else if (choice == 2)
        {
            int id;
            std::cout << "Enter ID: ";
            id = InputValidation::getInput<int>();
            menu.removeItem(id);
        }
        else if (choice == 3)
        {
            int id;
            double price;
            std::cout << "Enter ID: ";
            id = InputValidation::getInput<int>();
            std::cout << "New price: $";
            price = InputValidation::getInput<double>();
            menu.updatePrice(id, price);
        }
        else if (choice == 4)
        {
            menu.displayMenu();
        }
        else if (choice == 5)
        {
            menu.saveToFile(menu.FILENAME_MENU);
            std::cout << "Menu saved.\n";
        }
    } while (choice != 0);
}

int main()
{
    Menu menu;
    Order order;

    menu.loadFromFile(menu.FILENAME_MENU);

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
        std::cout << "\n====== RESTAURANT SYSTEM ======\n";
        std::cout << "1. View Menu\n";
        std::cout << "2. Add Item to Order\n";
        std::cout << "3. View Order\n";
        std::cout << "4. Checkout\n";
        std::cout << "5. Admin Mode\n";
        std::cout << "6. View Total Sales\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        choice = InputValidation::getInput<int>();

        std::cout << "\n";

        if (choice == 1)
        {
            menu.displayMenu();
        }
        else if (choice == 2)
        {
            int id;
            std::cout << "Enter item id: ";
            id = InputValidation::getInput<int>();

            if (menu.exists(id))
            {
                order.addItem(menu.getItem(id));
                std::cout << "Added to order!\n";
            }
            else
            {
                std::cout << "Invalid ID.\n";
            }
        }
        else if (choice == 3)
        {
            order.displayOrder();
        }
        else if (choice == 4)
        {
            order.displayOrder();
            order.saveOrder(menu.FILENAME_SALES);
            order.clear();
            std::cout << "Order complete.\n";
        }
        else if (choice == 5)
        {
            std::string pass;
            std::cout << "Enter admin password: ";
            std::cin >> pass;

            if (pass == "admin123")
            {
                adminMenu(menu);
            }
            else
            {
                std::cout << "Wrong password.\n";
            }
        }
        else if (choice == 6)
        {
            double total = Sales::getTotalSales(menu.FILENAME_SALES);
            std::cout << "Total Sales: $" << total << "\n";
        }

    } while (choice != 0);

    menu.saveToFile(menu.FILENAME_MENU);

    std::cout << "Goodbye! See you soon!\n";

    return 0;
}