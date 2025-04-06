#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

MerkelMain::MerkelMain() {}

void MerkelMain::init()
{
    current_time_ = order_book_.get_earliest_time();
    int user_option;
    while (true)
    {
        print_menu();
        user_option = get_user_option();
        std::cout << std::endl;
        process_option(user_option);
        std::cout << std::endl;
    }
}

void MerkelMain::print_menu()
{

    std::cout << "********" << std::endl;
    std::cout << "* MENU *" << std::endl;
    std::cout << "********" << std::endl;
    std::cout << "Current time: " << current_time_ << std::endl;
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

void MerkelMain::print_exchange_stats()
{
    std::string current_time = "2020/03/17 17:01:24.884492";
    for (const std::string &p : order_book_.get_known_products())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = order_book_.get_orders(OrderBookType::ask, p, current_time);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::get_high_price(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::get_low_price(entries) << std::endl;
    }
}

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