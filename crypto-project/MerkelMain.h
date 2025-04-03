#pragma once

class MerkelMain
{
public:
    MerkelMain();
    void init();
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