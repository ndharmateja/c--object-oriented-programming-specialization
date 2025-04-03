#pragma once

#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
public:
    MerkelMain();
    /**
     * Initialize the application
     */
    void init();

private:
    std::vector<OrderBookEntry> orders;

    void loadOrderBook();
    void printMenu();
    int getUserOption();
    void printHelp();
    void printExchangeStats();
    void makeOffer();
    void makeBid();
    void printWallet();
    void continueToNextTimeFrame();
    void invalidOption();
    void processOption(int userOption);
};