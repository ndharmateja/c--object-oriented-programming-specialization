#include "OrderBook.h"
#include <set>

OrderBook::OrderBook(std::string filename)
{
    orders_ = CSVReader::read_csv(filename);
}
std::vector<std::string> OrderBook::get_known_products()
{
    std::set<std::string> unique_products;
    for (const OrderBookEntry &entry : orders_)
        unique_products.insert(entry.product_);

    std::vector<std::string> products;
    for (const std::string &product : unique_products)
        products.push_back(product);

    return products;
}
std::vector<OrderBookEntry> OrderBook::get_orders(OrderBookType type,
                                                  std::string product,
                                                  std::string timestamp)
{
    std::vector<OrderBookEntry> filtered_orders;

    for (const OrderBookEntry &entry : orders_)
        if (entry.type_ == type &&
            entry.product_ == product &&
            entry.timestamp_ <= timestamp)
            filtered_orders.push_back(entry);
    return filtered_orders;
}

double OrderBook::get_high_price(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price_;
    for (const OrderBookEntry &order : orders)
        if (order.price_ > max)
            max = order.price_;
    return max;
}

double OrderBook::get_low_price(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].price_;
    for (const OrderBookEntry &order : orders)
        if (order.price_ < min)
            min = order.price_;
    return min;
}
