#include <iostream>

void printMenu()
{

    std::cout << std::endl;
    std::cout << "********" << std::endl;
    std::cout << "* MENU *" << std::endl;
    std::cout << "********" << std::endl;
    std::cout << "1 : Print help" << std::endl;
    std::cout << "2 : Print exchange stats" << std::endl;
    std::cout << "3 : Place an ask" << std::endl;
    std::cout << "4 : Place a bid" << std::endl;
    std::cout << "5 : Print wallet" << std::endl;
    std::cout << "6 : Continue " << std::endl;
}

int getUserOption()
{
    int userOption;
    std::cout << "Choose option (1-6): ";
    std::cin >> userOption;

    return userOption;
}

void printHelp()
{
    std::cout << "Help - your aim is to make money. Analyze the market and make "
                 "bids and offers."
              << std::endl;
}

void printExchangeStats() { std::cout << "Market looks good." << std::endl; }

void makeOffer()
{
    std::cout << "Make an offer - enter an amount." << std::endl;
}

void makeBid() { std::cout << "Make a bid - enter an amount." << std::endl; }

void printWallet() { std::cout << "Your wallet is empty." << std::endl; }

void continueToNextTimeFrame()
{
    std::cout << "Going to next time frame." << std::endl;
}

void invalidOption()
{
    std::cout << "Invalid option!" << std::endl;
}

void processOption(int userOption)
{
    // Conditional Execution
    if (userOption < 1 || userOption > 6)
        invalidOption();
    else if (userOption == 1)
        printHelp();
    else if (userOption == 2)
        printExchangeStats();
    else if (userOption == 3)
        makeOffer();
    else if (userOption == 4)
        makeBid();
    else if (userOption == 5)
        printWallet();
    else if (userOption == 6)
        continueToNextTimeFrame();
}

int main()
{
    while (true)
    {
        printMenu();
        int userOption = getUserOption();
        processOption(userOption);
    }

    return 0;
}