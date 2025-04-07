#pragma once

#include <map>
#include <string>

class Wallet
{
public:
    Wallet();

    /** Inserts the currency */
    void insert_currency(std::string currency, double amount);

    /** Removes the currency */
    bool remove_currency(std::string currency, double amount);

    /** Returns true if the wallet contains the currency */
    bool does_contain_currency(std::string currency, double amount);
    void print_wallet();

private:
    std::map<std::string, double> wallet_;
};