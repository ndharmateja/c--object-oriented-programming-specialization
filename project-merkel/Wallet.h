#pragma once

#include <map>
#include <string>
#include "OrderBookEntry.h"

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

    /** Returns true if the wallet can fulfill the order */
    bool can_fulfill_order(const OrderBookEntry &order) const;

    /** Returns a string representation of the wallet */
    std::string to_string() const;

    /** Processes a sale
     * updates the wallet assuming the sale is made by simuser
     */
    void process_sale(const OrderBookEntry &sale);

private:
    std::map<std::string, double> wallet_;
};

std::ostream &operator<<(std::ostream &os, const Wallet &wallet);