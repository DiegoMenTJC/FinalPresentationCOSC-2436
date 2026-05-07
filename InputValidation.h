#pragma once

// Static class
class InputValidation
{
public:
    template<typename T>
    static T getInput()
    {
        T input{};
        while (!(std::cin >> input))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\nInvalid input. Try again: ";
        }
        return input;
    }
};