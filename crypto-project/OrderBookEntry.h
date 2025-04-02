#include <string>

enum class OrderBookType
{
    ask,
    bid
};

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