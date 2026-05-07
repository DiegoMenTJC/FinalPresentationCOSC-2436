#pragma once

// Static class
class Sales
{
public:
    static double getTotalSales(const std::string& fileName)
    {
        std::ifstream file(fileName);
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