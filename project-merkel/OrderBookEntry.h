#pragma once

#include <string>
#include <stdexcept>

enum class OrderBookType
{
    ask,
    bid,
    sale
};

class OrderBookEntry
{
public:
    OrderBookEntry(std::string timestamp,
                   std::string product,
                   OrderBookType type,
                   double price,
                   double amount,
                   std::string username = "dataset");

    std::string get_product_first_part() const;
    std::string get_product_second_part() const;

    static OrderBookType string_to_order_book_type(std::string order_type);
    static bool compare_by_timestamp(const OrderBookEntry &a, const OrderBookEntry &b) { return a.timestamp_ < b.timestamp_; }
    static bool compare_by_price_asc(const OrderBookEntry &a, const OrderBookEntry &b) { return a.price_ < b.price_; }
    static bool compare_by_price_desc(const OrderBookEntry &a, const OrderBookEntry &b) { return a.price_ > b.price_; }

    std::string timestamp_;
    std::string product_;
    OrderBookType type_;
    double price_;
    double amount_;
    std::string username_;
};