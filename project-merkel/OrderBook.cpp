#include "OrderBook.h"

OrderBook::OrderBook(std::string filename)
{
    orders_ = CSVReader::read_csv(filename);
}
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    return products;
}
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> orders;
    return orders;
}