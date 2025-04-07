#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

MerkelMain::MerkelMain() {}

void MerkelMain::init()
{
    current_time_ = order_book_.get_earliest_time();
    wallet_.insert_currency("BTC", 10);
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
    std::cout << "6 : Go to next time frame" << std::endl;
}

int MerkelMain::get_user_option()
{
    int userOption = 0;
    std::cout << "Choose option (1-6): ";

    // Use getline to get user input
    std::string line;
    std::getline(std::cin, line);

    // Convert user input to integer
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::invalid_argument &e)
    {
    }

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
    for (const std::string &p : order_book_.get_known_products())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = order_book_.get_orders(OrderBookType::ask, p, current_time_);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::get_high_price(entries)
                  << " Min ask: " << OrderBook::get_low_price(entries)
                  << " Average ask: " << OrderBook::get_mean_price(entries)
                  << " Standard Deviation: " << OrderBook::get_std_dev_price(entries) << std::endl;
    }
}

void MerkelMain::make_ask_or_bid(OrderBookType order_type)
{
    // Print the prompt
    std::cout << "Make an " << (order_type == OrderBookType::ask ? "ask" : "bid")
              << ". Enter <product>,<price>,<amount> "
                 "(Eg: ETH/BTC,100,1)."
              << std::endl;

    // Get the user input
    std::string input;
    std::getline(std::cin, input);

    // Tokenize the input
    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');

    // Check the number of tokens
    if (tokens.size() != 3)
    {
        std::cout << "Invalid number of tokens." << std::endl;
        return;
    }

    // Convert the tokens to an order book entry
    std::string product = tokens[0];
    std::string price_string = tokens[1];
    std::string amount_string = tokens[2];
    try
    {
        OrderBookEntry entry = CSVReader::convert_to_order_book_entry(
            current_time_, product, order_type,
            price_string, amount_string);

        // Add the entry to the order book
        order_book_.insert_order(entry);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void MerkelMain::make_ask() { make_ask_or_bid(OrderBookType::ask); }

void MerkelMain::make_bid() { make_ask_or_bid(OrderBookType::bid); }

void MerkelMain::print_wallet() { std::cout << wallet_ << std::endl; }

void MerkelMain::continue_to_next_frame()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string &p : order_book_.get_known_products())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = order_book_.match_asks_to_bids(p, current_time_);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price_ << " amount " << sale.amount_ << std::endl;
        }
    }
    current_time_ = order_book_.get_next_time(current_time_);
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
        make_ask();
    else if (userOption == 4)
        make_bid();
    else if (userOption == 5)
        print_wallet();
    else if (userOption == 6)
        continue_to_next_frame();
}