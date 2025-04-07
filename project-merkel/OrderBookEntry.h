#pragma once

#include <string>
#include <stdexcept>

enum class OrderBookType
{
    ask,
    bid
};

class OrderBookEntry
{
public:
    OrderBookEntry(std::string timestamp,
                   std::string product,
                   OrderBookType type,
                   double price,
                   double amount);

    static OrderBookType string_to_order_book_type(std::string order_type);
    static bool compare_by_timestamp(const OrderBookEntry &a, const OrderBookEntry &b) { return a.timestamp_ < b.timestamp_; }

    std::string timestamp_;
    std::string product_;
    OrderBookType type_;
    double price_;
    double amount_;
};