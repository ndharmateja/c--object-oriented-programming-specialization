#pragma once

#include <string>

enum class OrderBookType
{
    ask,
    bid
};

OrderBookType string_to_order_book_type(std::string order_type)
{
    if (order_type == "bid")
        return OrderBookType::bid;
    if (order_type == "ask")
        return OrderBookType::ask;
    throw std::invalid_argument("Invalid order type");
}

class OrderBookEntry
{
public:
    OrderBookEntry(std::string timestamp,
                   std::string product,
                   OrderBookType type,
                   double price,
                   double amount);

    std::string timestamp_;
    std::string product_;
    OrderBookType type_;
    double price_;
    double amount_;
};