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

bool Wallet::contains_currency(std::string currency, double amount)
{
    if (!wallet_.count(currency))
        return false;
    return wallet_[currency] >= amount;
}

void Wallet::print_wallet()
{
    std::cout << "Wallet contents: " << std::endl;
    for (const auto &pair : wallet_)
        std::cout << pair.first << ": " << pair.second << std::endl;
}