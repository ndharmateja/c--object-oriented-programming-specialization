#include <string>
#include "OrderBookEntry.h"

OrderBookType OrderBookEntry::string_to_order_book_type(std::string order_type)
{
    if (order_type == "bid")
        return OrderBookType::bid;
    if (order_type == "ask")
        return OrderBookType::ask;
    if (order_type == "sale")
        return OrderBookType::sale;
    throw std::invalid_argument("Invalid order type");
}

OrderBookEntry::OrderBookEntry(std::string timestamp,
                               std::string product,
                               OrderBookType type,
                               double price,
                               double amount,
                               std::string username)
    : timestamp_(timestamp),
      product_(product),
      type_(type),
      price_(price),
      amount_(amount),
      username_(username) {}

std::string OrderBookEntry::get_product_first_part() const
{
    auto pos = product_.find("/");
    return product_.substr(0, pos);
}

std::string OrderBookEntry::get_product_second_part() const
{
    auto pos = product_.find("/");
    return product_.substr(pos + 1);
}