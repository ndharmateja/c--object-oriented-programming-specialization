#include "Wallet.h"
#include <iostream>

Wallet::Wallet()
{
}

/** Inserts the currency */
void Wallet::insert_currency(std::string currency, double amount)
{
    wallet_[currency] += amount;
}

/** Returns true if the wallet contains the currency */
bool Wallet::does_contain_currency(std::string currency, double amount)
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