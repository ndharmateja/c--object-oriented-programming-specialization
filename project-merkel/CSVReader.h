#include <string>
#include <vector>
#include "OrderBookEntry.h"

class CSVReader
{
public:
    std::vector<OrderBookEntry> read_csv(std::string filename);

private:
    std::vector<std::string> tokenize(std::string csvLine, char separator);
    OrderBookEntry convert_to_order_book_entry(std::vector<std::string> tokens);
};