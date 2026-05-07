#pragma once

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <fstream>

#include "MenuItem.h"

class Order
{
private:
    std::map<int, int> itemQuantities;
    std::vector<MenuItem> items;

public:
    void addItem(MenuItem item);

    double calculateTotal();

    void displayOrder();
    void saveOrder(const std::string& fileName);

    void clear();
};
