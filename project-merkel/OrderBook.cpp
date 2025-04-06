#include "OrderBook.h"

OrderBook::OrderBook(std::string filename)
{
    orders_ = CSVReader::read_csv(filename);
}
std::vector<std::string> OrderBook::get_known_products()
{
    std::vector<std::string> products;
    return products;
}
std::vector<OrderBookEntry> OrderBook::get_orders(OrderBookType type,
                                                  std::string product,
                                                  std::string timestamp)
{
    std::vector<OrderBookEntry> orders;
    return orders;
}