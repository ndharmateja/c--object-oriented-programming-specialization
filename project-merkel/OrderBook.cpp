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
std::vector<OrderBookEntry> OrderBook::get_orders(
    OrderBookType type,
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

std::vector<OrderBookEntry> OrderBook::match_asks_to_bids(std::string product, std::string timestamp)
{

    // asks = orderbook.asks in this timeframe
    // bids = orderbook.bids in this timeframe
    // sales = []
    std::vector<OrderBookEntry> asks = get_orders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = get_orders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;

    // sort asks lowest first
    // sort bids highest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compare_by_price_asc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compare_by_price_desc);

    // for ask in asks:
    for (OrderBookEntry &ask : asks)
    {
        // for bid in bids:
        for (OrderBookEntry &bid : bids)
        {
            // if bid.price >= ask.price # we have a match
            // sale = new orderbookentry()
            // sale.price = ask.price
            if (bid.price_ >= ask.price_)
            {
                OrderBookEntry sale{timestamp, product, OrderBookType::sale, ask.price_, 0};

                // if bid.amount == ask.amount: # bid completely clears ask
                // sale.amount = ask.amount
                // sales.append(sale)
                // bid.amount = 0 # make sure the bid is not processed again
                // # can do no more with this ask
                // # go onto the next ask
                // break
                if (bid.amount_ == ask.amount_)
                {
                    sale.amount_ = ask.amount_;
                    sales.push_back(sale);
                    bid.amount_ = 0;
                    break;
                }

                // if bid.amount > ask.amount: # ask is completely gone slice the bid
                // sale.amount = ask.amount
                // sales.append(sale)
                // # we adjust the bid in place
                // # so it can be used to process the next ask
                // bid.amount = bid.amount - ask.amount
                // # ask is completely gone, so go to next ask
                // break
                if (bid.amount_ > ask.amount_)
                {
                    sale.amount_ = ask.amount_;
                    sales.push_back(sale);
                    bid.amount_ = bid.amount_ - ask.amount_;
                    break;
                }

                // if bid.amount < ask.amount # bid is completely gone, slice the ask
                // sale.amount = bid.amount
                // sales.append(sale)
                // # update the ask
                // # and allow further bids to process the remaining amount
                // ask.amount = ask.amount - bid.amount
                // bid.amount = 0 # make sure the bid is not processed again
                // # some ask remains so go to the next bid
                // continue
                if (bid.amount_ < ask.amount_)
                {
                    sale.amount_ = bid.amount_;
                    sales.push_back(sale);
                    ask.amount_ = ask.amount_ - bid.amount_;
                    bid.amount_ = 0;
                    continue;
                }
            }
        }
    }

    // return sales
    return sales;
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
