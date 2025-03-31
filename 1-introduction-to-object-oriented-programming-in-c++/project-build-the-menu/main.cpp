#include <iostream>

int main()
{
    while (true)
    {
        // Print the menu items
        std::cout << "1 : Print help" << std::endl;
        std::cout << "2 : Print exchange stats" << std::endl;
        std::cout << "3 : Place an ask" << std::endl;
        std::cout << "4 : Place a bid" << std::endl;
        std::cout << "5 : Print wallet" << std::endl;
        std::cout << "6 : Continue " << std::endl;

        // Take user option
        int userOption;
        std::cout << "Type in 1-6" << std::endl;
        std::cin >> userOption;

        // Conditional Execution
        if (userOption < 1 || userOption > 6)
            std::cout << "Invalid option!" << std::endl;
        else if (userOption == 1)
            std::cout << "Help - choose options from the menu" << std::endl
                      << "and follow the on screen instructions." << std::endl;
        else if (userOption == 2)
            std::cout << "Exchange stats" << std::endl;
        else if (userOption == 3)
            std::cout << "Place an ask" << std::endl;

        else if (userOption == 4)
            std::cout << "Place a bid" << std::endl;

        else if (userOption == 5)
            std::cout << "Print wallet" << std::endl;

        else if (userOption == 6)
            std::cout << "Continue" << std::endl;
    }

    return 0;
}