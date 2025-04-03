#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>

MerkelMain::MerkelMain() {}

void MerkelMain::init()
{
    load_order_book();
    int user_option;
    while (true)
    {
        print_menu();
        user_option = get_user_option();
        process_option(user_option);
    }
}

void MerkelMain::load_order_book()
{
    OrderBookEntry order1("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.0217, 11.58032904);
    OrderBookEntry order2("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02168639, 0.40030022);
    OrderBookEntry order3("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02167076, 33.82130391);
    OrderBookEntry order4("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02167075, 0.1777869);
    OrderBookEntry order5("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02164914, 31.97356142);
    OrderBookEntry order6("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02164903, 0.01766217);
    OrderBookEntry order7("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02164226, 0.14046593);
    OrderBookEntry order8("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02161593, 0.00636546);
    OrderBookEntry order9("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02160336, 508.56);

    orders.push_back(order1);
    orders.push_back(order2);
    orders.push_back(order3);
    orders.push_back(order4);
    orders.push_back(order5);
    orders.push_back(order6);
    orders.push_back(order7);
    orders.push_back(order8);
    orders.push_back(order9);
}

void MerkelMain::print_menu()
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

int MerkelMain::get_user_option()
{
    int userOption;
    std::cout << "Choose option (1-6): ";
    std::cin >> userOption;

    return userOption;
}

void MerkelMain::print_help()
{
    std::cout << "Help - your aim is to make money. Analyze the market and make "
                 "bids and offers."
              << std::endl;
}

void MerkelMain::print_exchange_stats() { std::cout << "#Entries: " << orders.size() << std::endl; }

void MerkelMain::make_offer()
{
    std::cout << "Make an offer - enter an amount." << std::endl;
}

void MerkelMain::make_bid() { std::cout << "Make a bid - enter an amount." << std::endl; }

void MerkelMain::print_wallet() { std::cout << "Your wallet is empty." << std::endl; }

void MerkelMain::continue_to_next_frame()
{
    std::cout << "Going to next time frame." << std::endl;
}

void MerkelMain::invalid_option()
{
    std::cout << "Invalid option!" << std::endl;
}

void MerkelMain::process_option(int userOption)
{
    // Conditional Execution
    if (userOption < 1 || userOption > 6)
        invalid_option();
    else if (userOption == 1)
        print_help();
    else if (userOption == 2)
        print_exchange_stats();
    else if (userOption == 3)
        make_offer();
    else if (userOption == 4)
        make_bid();
    else if (userOption == 5)
        print_wallet();
    else if (userOption == 6)
        continue_to_next_frame();
}