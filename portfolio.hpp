// header file contain definition of Class
// Declares the class, its variables, constructor, and functions

#include "basic_stock.hpp"
#include <string>
#include <vector>

class Portfolio{
private: // data
    std::vector<Stock> stocks;  // stocks vector
    double cash;                // available cash
    
public: // method
    // Constructor
    Portfolio(std::vector<Stock> initial_stocks, double initial_cash);
    
    // Function 1
    void buy_stock(std::string name, int shares); // buy shares
    
    // Function 2
    void sell_stock(std::string name, int shares);  // sell shares
    
    // Function 3
    double calculate_total_value(); // compute total portfolio value
    
    // Function 4
    double calculate_stock_value(); // calculate value of all stocks
    
    // Function 5
    double get_cash(); // get available cash
    
    // Function 6
    void update_stock_price(std::string name, double new_price);
    
    // Function 7
    void update_reference_price(std::string name, double new_reference_price);
    
    // Getter Functions
    double get_stock_price(std::string name);
    double get_reference_price(std::string name);
};
