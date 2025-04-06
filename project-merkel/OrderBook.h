#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <string>

class OrderBook
{
public:
    /** Constructor, reading a CSV file */
    OrderBook(std::string filename);
    /** return the list of known products */
    std::vector<std::string> get_known_products();
    /** return vector of OrderBookEntries according to the filters */
    std::vector<OrderBookEntry> get_orders(OrderBookType type,
                                           std::string product,
                                           std::string timestamp);
    /** return the earliest timestamp */
    std::string get_earliest_time();

    /**
     * return the next timestamp and if we reach the end
     * it circles back to the beginning
     */
    std::string get_next_time(std::string timestamp);

    static double get_high_price(std::vector<OrderBookEntry> &orders);
    static double get_low_price(std::vector<OrderBookEntry> &orders);
    static double get_mean_price(std::vector<OrderBookEntry> &orders);
    static double get_std_dev_price(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> orders_;
};