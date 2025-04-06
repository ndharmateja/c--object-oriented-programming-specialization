#pragma once

#include <vector>
#include "OrderBook.h"

class MerkelMain
{
public:
    MerkelMain();
    /**
     * Initialize the application
     */
    void init();

private:
    OrderBook order_book_{"data/20200317.csv"};
    std::string current_time_;

    void print_menu();
    int get_user_option();
    void print_help();
    void print_exchange_stats();
    void make_offer();
    void make_bid();
    void print_wallet();
    void continue_to_next_frame();
    void invalid_option();
    void process_option(int userOption);
};