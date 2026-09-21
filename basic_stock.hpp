// header file contain definition of Class
// declares the class, its variables, constructor, and functions

#ifndef basic_stock_hpp
#define basic_stock_hpp

#include <iostream>
#include <string>
#include <vector>

class Stock{
    private: // data
    std::string name; // ticker
    int shares;       // number of shares
    double price;     // stock price
    double reference_price;
    
    public:// method
    // Constructor
    Stock(std::string stock_name, int num_shares, double stock_price);
    
    // Function 1
    double calculate_value(); // compute the value of a stock postion
    
    // Function 2
    void update_price(double new_price); // updata the stock price
    
    // Function 3
    void buy_shares(int num_shares); // buy additional shares
    
    // Function 4
    void sell_shares(int num_shares); // sell shares
    
    // Function 5
    void update_reference_price(double new_reference_price);
    
    // Getter Functions
    std::string get_name();
    int get_shares();
    double get_price();
    double get_reference_price();
    
    };
    
// Free Function
std::vector<Stock> read_portfolio(std::string filename);  // takes a filename and returns a vector of Stocks


#endif
