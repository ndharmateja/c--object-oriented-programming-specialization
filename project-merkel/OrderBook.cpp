#include "OrderBook.h"
#include <set>
#include <algorithm>

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

std::string OrderBook::get_earliest_time()
{
    // Because the orders are sorted in the ascending order of the timestamps
    // we can return the first one
    return orders_[0].timestamp_;
}

std::string OrderBook::get_next_time(std::string timestamp)
{
    // Because the orders are sorted in the ascending order of the timestamps
    // we can return the first timestamp greater than the given one
    for (const OrderBookEntry &entry : orders_)
        if (entry.timestamp_ > timestamp)
            return entry.timestamp_;

    // If there is no next timestamp, return the first one
    return orders_[0].timestamp_;
}

void OrderBook::insert_order(OrderBookEntry &order)
{
    orders_.push_back(order);
    std::sort(orders_.begin(), orders_.end(), OrderBookEntry::compare_by_timestamp);
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

double OrderBook::get_mean_price(std::vector<OrderBookEntry> &orders)
{
    double sum = 0.0;
    for (const OrderBookEntry &order : orders)
        sum += order.price_;
    return sum / orders.size();
}

double OrderBook::get_std_dev_price(std::vector<OrderBookEntry> &orders)
{
    double mean = get_mean_price(orders);
    double sum = 0.0;
    for (const OrderBookEntry &order : orders)
        sum += (order.price_ - mean) * (order.price_ - mean);
    return sqrt(sum / orders.size());
}
