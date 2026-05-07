#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>

#include "MenuItem.h"

class Menu
{
private:
    std::map<int, MenuItem> items;

public:
    const std::string FILENAME_MENU = "Menu.txt";
    const std::string FILENAME_SALES = "Sales.txt";

    void addItem(int id, const std::string& name, double price);
    void removeItem(int id);
    void updatePrice(int id, double newPrice);

    void displayMenu();

    bool exists(int id);

    MenuItem getItem(int id);

    void saveToFile(const std::string& fileName);

    void loadFromFile(const std::string& fileName);
};