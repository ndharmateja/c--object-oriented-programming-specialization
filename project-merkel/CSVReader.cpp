#include <string>
#include <vector>
#include <fstream>
#include "CSVReader.h"
#include <stdexcept>

std::vector<OrderBookEntry> CSVReader::read_csv(std::string filename)
{
    std::ifstream file{filename};
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    std::vector<OrderBookEntry> order_book_entries;
    std::string line;
    std::vector<std::string> tokens;
    while (std::getline(file, line))
    {
        // Tokenize the line
        tokens = tokenize(line, ',');

        try
        {
            OrderBookEntry entry = convert_to_order_book_entry(tokens);
            order_book_entries.push_back(entry);
        }
        catch (const std::exception &e)
        {
            continue;
        }
    }
    file.close();
    return order_book_entries;
}

std::vector<std::string> CSVReader::tokenize(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string::size_type start, end;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            tokens.push_back(csvLine.substr(start, end - start));
        else
            tokens.push_back(csvLine.substr(start));
        start = end + 1;
    } while (end != std::string::npos);

    return tokens;
}

OrderBookEntry CSVReader::convert_to_order_book_entry(std::vector<std::string> tokens)
{
    // If the line does not have 5 tokens, skip it
    if (tokens.size() != 5)
        throw std::invalid_argument("Invalid line");

    // Declare 5 variables for order book entry
    double price, amount;
    OrderBookType order_type;
    std::string timestamp, product;

    // Try to convert the tokens to floats
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument("Invalid line");
    }

    // Try to convert the order type
    try
    {
        order_type = OrderBookEntry::string_to_order_book_type(tokens[2]);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument("Invalid line");
    }

    // Assign the tokens to the timestamp and product
    timestamp = tokens[0];
    product = tokens[1];

    return OrderBookEntry{timestamp, product, order_type, price, amount};
}

OrderBookEntry CSVReader::convert_to_order_book_entry(
    std::string timestamp,
    std::string product,
    OrderBookType type,
    std::string price_string,
    std::string amount_string)
{
    // Try to convert the tokens to floats
    double price, amount;
    try
    {
        price = std::stod(price_string);
        amount = std::stod(amount_string);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument("(CSVReader::convert_to_order_book_entry) Invalid floats! " + price_string + "," + amount_string);
    }

    return OrderBookEntry{timestamp, product, type, price, amount};
}