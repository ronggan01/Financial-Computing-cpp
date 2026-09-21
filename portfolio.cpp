// cpp file defines the constructor and functions delcared in header file

#include "portfolio.hpp"
#include <iostream>

// Constructor
Portfolio::Portfolio(std::vector<Stock> initial_stocks, double initial_cash){
    stocks = initial_stocks;
    cash = initial_cash;
}

// Function 1
void Portfolio::buy_stock(std::string name, int num_shares){ // buy shares if we have enough cash
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++){
        if ((*it).get_name() == name){
            double cost = (*it).get_price() * num_shares;
            if (cash >= cost){
                (*it).buy_shares(num_shares);
                cash -= cost;
            }
            else
                std::cout << "Not enough cash" << std::endl;
            return;
        }
    }
}

// Function 2
void Portfolio::sell_stock(std::string name, int num_shares){ // sell shares
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++){
        if ((*it).get_name() == name){
            if ((*it).get_shares() >= num_shares){
                double revenue = (*it).get_price() * num_shares;
                (*it).sell_shares(num_shares);
                cash += revenue;
            }
            else
                std::cout << "Not enough shares" << std::endl;
            return;
        }
    }
}

// Function 3
double Portfolio::calculate_total_value(){ // compute total portfolio value
    return cash + calculate_stock_value();
}

// Function 4
double Portfolio::calculate_stock_value(){ // calculate value of all stocks
    double total = 0.0;
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++)
        total += (*it).calculate_value();
    return total;
}

// Function 5
double Portfolio::get_cash(){ // get available cash
    return cash;
}

// Function 6
void Portfolio::update_stock_price(std::string name, double new_price){
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++){
        if ((*it).get_name() == name){
            (*it).update_price(new_price);
            return;
        }
    }
}

// Function 7
void Portfolio::update_reference_price(std::string name, double new_reference_price){
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++){
        if ((*it).get_name() == name){
            (*it).update_reference_price(new_reference_price);
            return;
        }
    }
}

// Getter Functions
double Portfolio::get_stock_price(std::string name){
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++){
        if ((*it).get_name() == name)
            return (*it).get_price();
    }
    return  -1.0; // if stock is not found, return price=-1
}

double Portfolio::get_reference_price(std::string name){
    std::vector<Stock>::iterator it;
    for (it=stocks.begin(); it!=stocks.end(); it++){
        if ((*it).get_name() == name){
            return( *it).get_reference_price();
        }
    }
    return -1.0; // if stock is not found, return reference_price = -1
}







