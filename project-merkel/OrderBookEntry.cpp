#include <string>
#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(std::string timestamp,
                               std::string product,
                               OrderBookType type,
                               double price,
                               double amount)
    : timestamp_(timestamp),
      product_(product),
      type_(type),
      price_(price),
      amount_(amount) {}