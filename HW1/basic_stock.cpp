// cpp file defines the constructor and functions delcared in header file

#include "basic_stock.hpp" 
#include <fstream>  // reading and writing files
#include <vector>   // vector container
#include <iostream> // input/output stream


// Constructor
Stock::Stock(std::string stock_name, int num_shares, double stock_price) {
    name = stock_name;
    shares = num_shares;
    price = stock_price;
    reference_price = stock_price;
}

// Function 1
double Stock::calculate_value() {  // compute the value of a stock position
    return shares * price;
}

// Function 2
void Stock::update_price(double new_price){ // updata the stock price
    price = new_price;
}

// Function 3
void Stock::buy_shares(int num_shares){ // buy additional shares
    shares += num_shares;
}

// Function 4
void Stock::sell_shares(int num_shares){ // sell shares
    if (num_shares <= shares)
        shares -= num_shares;
    else
        std::cout << "Not enough shares to sell" << std::endl;
}

// Function 5
void Stock::update_reference_price(double new_reference_price){
    reference_price = new_reference_price;
}

// Getter Functions
std::string Stock::get_name(){
    return name;
}

int Stock::get_shares(){
    return shares;
}

double Stock::get_price(){
    return price;
}

double Stock::get_reference_price(){
    return reference_price;
}




// Free Function
std::vector<Stock> read_portfolio(std::string filename){
    std::vector<Stock> stocks;     // stocks = []
    std::ifstream file(filename);  // input file stream
    if (!file.is_open()){
        std::cout << "Cannot open file: " << std::endl;
            return stocks;
        }
    bool done=false; // create a boolean "done", which is false
    while(!done){    // "!" means not, !false = true
        std::string name;
        int num;
        double price;
        file >> name >> num >> price;   // the order the elements in the file
        if (file.eof())   // eof(): end of file
            done=true;
        else{
            Stock s(name, num, price);  // create a object "s", which calls the constructor
            stocks.push_back(s);  // add "s" to the end of "stocks"
        }
    }
    return stocks;
}
