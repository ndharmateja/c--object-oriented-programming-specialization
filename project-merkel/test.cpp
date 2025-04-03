#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "OrderBookEntry.h"

std::vector<std::string> tokenize(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    int start, end;
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

OrderBookType stringToOrderBookType(std::string order_type)
{
    if (order_type == "bid")
        return OrderBookType::bid;
    if (order_type == "ask")
        return OrderBookType::ask;
    throw std::invalid_argument("Invalid order type");
}

int main()
{
    std::ifstream file{"data/20200317.csv"};
    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return -1;
    }

    std::string line;
    std::vector<std::string> tokens;
    while (std::getline(file, line))
    {
        // Tokenize the line
        tokens = tokenize(line, ',');

        // If the line does not have 5 tokens, skip it
        if (tokens.size() != 5)
        {
            std::cout << "Invalid line: " << line << std::endl;
            continue;
        }

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
            std::cout << "Invalid floats in line: " << line << std::endl;
            continue;
        }

        // Try to convert the order type
        try
        {
            order_type = stringToOrderBookType(tokens[2]);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Invalid order type in line: " << line << std::endl;
            continue;
        }

        // Assign the tokens to the timestamp and product
        timestamp = tokens[0];
        product = tokens[1];
    }
    file.close();

    return 0;
}