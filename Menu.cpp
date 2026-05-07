#include "Menu.h"

void Menu::addItem(int id, const std::string& name, double price)
{
    items[id] = MenuItem(id, name, price);
}

void Menu::removeItem(int id)
{
    if (items.erase(id))
    {
        std::cout << "Item removed.\n";
    }
    else
    {
        std::cout << "Item not found.\n";
    }
}

void Menu::updatePrice(int id, double newPrice)
{
    if (items.count(id))
    {
        items[id].price = newPrice;
        std::cout << "Price Updated\n";
    }
    else
    {
        std::cout << "Item not found.\n";
    }
}

void Menu::displayMenu()
{
    std::cout << "======= Menu =======\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(23) << "Item" << "Price\n";
    for (auto& pair : items)
    {
        std::cout << std::setw(5) << pair.second.id
            << std::setw(23) << pair.second.name
            << "$" << pair.second.price << "\n";
    }
}

bool Menu::exists(int id)
{
    return items.count(id);
}

MenuItem Menu::getItem(int id)
{
    return items[id];
}

//Save a file
void Menu::saveToFile(const std::string& fileName)
{
    std::ofstream file(fileName);
    for (auto& pair : items)
    {
        file << pair.second.id << ","
            << pair.second.name << ","
            << pair.second.price << "\n";
    }
    file.close();
}

//Load a file
void Menu::loadFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "FNFE";
        return;
    }

    items.clear();
    int id;
    std::string name;
    double price;
    char comma;

    while (file >> id >> comma)
    {
        std::getline(file, name, ',');
        file >> price;
        file.ignore();
        addItem(id, name, price);
    }

    file.close();
}