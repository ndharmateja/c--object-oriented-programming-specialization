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
    bool contains_currency(std::string currency, double amount) const;
    std::string to_string() const;

private:
    std::map<std::string, double> wallet_;
};