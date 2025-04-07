#pragma once

#include <string>
#include <vector>
#include "OrderBookEntry.h"

class CSVReader
{
public:
    static std::vector<OrderBookEntry> read_csv(std::string filename);
    static std::vector<std::string> tokenize(std::string csvLine, char separator);
    static OrderBookEntry convert_to_order_book_entry(
        std::string timestamp,
        std::string product,
        OrderBookType type,
        std::string price,
        std::string amount);

private:
    static OrderBookEntry convert_to_order_book_entry(std::vector<std::string> tokens);
};