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
    std::vector<std::string> getKnownProducts();
    /** return vector of OrderBookEntries according to the filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);

private:
    std::vector<OrderBookEntry> orders_;
};