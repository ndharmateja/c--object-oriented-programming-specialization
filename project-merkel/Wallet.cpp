#include "Wallet.h"
#include <iostream>

Wallet::Wallet()
{
}

void Wallet::insert_currency(std::string currency, double amount)
{
    if (amount < 0)
        throw std::invalid_argument("Amount must be positive");
    wallet_[currency] += amount;
}

bool Wallet::remove_currency(std::string currency, double amount)
{
    // Check if the amount is positive
    if (amount < 0)
        throw std::invalid_argument("Amount must be positive");

    // Check if the wallet contains the currency
    if (!contains_currency(currency, amount))
        return false;

    // Decrease the amount
    wallet_[currency] -= amount;
    return true;
}

bool Wallet::contains_currency(std::string currency, double amount) const
{
    if (!wallet_.count(currency))
        return false;
    return wallet_.at(currency) >= amount;
}

bool Wallet::can_fulfill_order(const OrderBookEntry &order) const
{
    if (order.type_ == OrderBookType::ask)
        return contains_currency(order.get_product_first_part(), order.amount_);
    if (order.type_ == OrderBookType::bid)
        return contains_currency(order.get_product_second_part(), order.amount_ * order.price_);
    throw std::invalid_argument("Invalid order type");
}

std::string Wallet::to_string() const
{
    std::string s = "Wallet contents: \n";
    for (const auto &pair : wallet_)
        s += pair.first + ": " + std::to_string(pair.second) + "\n";
    return s;
}

std::ostream &operator<<(std::ostream &os, const Wallet &wallet)
{
    os << wallet.to_string();
    return os;
}