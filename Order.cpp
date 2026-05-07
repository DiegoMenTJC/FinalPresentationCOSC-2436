#include "Order.h"

void Order::addItem(MenuItem item)
{
    itemQuantities[item.id]++;
    items.push_back(item);
}

double Order::calculateTotal()
{
    double total = 0;
    for (auto& item : items)
    {
        total += item.price;
    }
    return total;
}

void Order::displayOrder()
{
    std::cout << "\n======= Order =======\n";
    std::map<int, int> counts;

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
                std::cout << item.name << " x" << pair.second
                    << " - $" << item.price * pair.second << "\n";
                break;
            }
        }
    }
    double subtotal = calculateTotal();
    double tax = subtotal * 0.0825;
    double total = subtotal + tax;

    std::cout << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Subtotal: $" << subtotal << "\n";
    std::cout << "Tax: $" << tax << "\n";
    std::cout << "Total: $" << total << "\n";
}

void Order::saveOrder(const std::string& fileName)
{
    std::ofstream file(fileName, std::ios::app);
    file << calculateTotal() << "\n";
    file.close();
}

void Order::clear()
{
    items.clear();
    itemQuantities.clear();
}