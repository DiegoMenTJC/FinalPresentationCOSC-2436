#pragma once

#include <string>

struct MenuItem
{
    int id;
    std::string name;
    double price;

    MenuItem()
        : id(0), name(""), price(0.0) {
    }

    MenuItem(int id, const std::string& name, double price)
        : id(id), name(name), price(price) {
    }
};