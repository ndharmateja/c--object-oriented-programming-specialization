#include <string>
#include <vector>
#include "OrderBookEntry.h"

class CSVReader
{
public:
    std::vector<OrderBookEntry> readCSV(std::string filename);

private:
    std::vector<std::string> tokenize(std::string csvLine, char separator);
    OrderBookEntry convertToOrderBookEntry(std::vector<std::string> tokens);
};