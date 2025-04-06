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
    std::vector<OrderBookEntry> orders;
    return orders;
}