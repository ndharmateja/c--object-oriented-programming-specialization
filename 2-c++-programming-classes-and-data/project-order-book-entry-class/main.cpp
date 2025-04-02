#include <iostream>
#include <string>
#include <vector>

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

double computeAveragePrice(std::vector<OrderBookEntry> &entries)
{
    int num_entries = 0;
    double sum_prices = 0.0;
    for (const OrderBookEntry &order : entries)
    {
        num_entries++;
        sum_prices += order.price_;
    }
    return sum_prices / num_entries;
}
double computeLowPrice(std::vector<OrderBookEntry> &entries)
{
    double min_price = entries[0].price_;
    for (const OrderBookEntry &order : entries)
        if (order.price_ < min_price)
            min_price = order.price_;
    return min_price;
}
double computeHighPrice(std::vector<OrderBookEntry> &entries)
{
    double max_price = entries[0].price_;
    for (const OrderBookEntry &order : entries)
        if (order.price_ > max_price)
            max_price = order.price_;
    return max_price;
}
double computePriceSpread(std::vector<OrderBookEntry> &entries)
{
    return computeHighPrice(entries) - computeLowPrice(entries);
}

int main()
{
    std::vector<OrderBookEntry> orders;

    OrderBookEntry order1("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.0217, 11.58032904);
    OrderBookEntry order2("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02168639, 0.40030022);
    OrderBookEntry order3("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02167076, 33.82130391);
    OrderBookEntry order4("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02167075, 0.1777869);
    OrderBookEntry order5("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02164914, 31.97356142);
    OrderBookEntry order6("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02164903, 0.01766217);
    OrderBookEntry order7("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02164226, 0.14046593);
    OrderBookEntry order8("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02161593, 0.00636546);
    OrderBookEntry order9("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::ask, 0.02160336, 508.56);

    orders.push_back(order1);
    orders.push_back(order2);
    orders.push_back(order3);
    orders.push_back(order4);
    orders.push_back(order5);
    orders.push_back(order6);
    orders.push_back(order7);
    orders.push_back(order8);
    orders.push_back(order9);

    // Print the prices of all orders
    for (const OrderBookEntry &order : orders)
        std::cout << "The price is: " << order.price_ << std::endl;

    std::cout << std::endl
              << "Stats" << std::endl;
    std::cout << "Average price: " << computeAveragePrice(orders) << std::endl;
    std::cout << "Low price: " << computeLowPrice(orders) << std::endl;
    std::cout << "High price: " << computeHighPrice(orders) << std::endl;
    std::cout << "Price spread: " << computePriceSpread(orders) << std::endl;
}