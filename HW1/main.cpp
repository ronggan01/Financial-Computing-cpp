//  HW1
//  Created by Rong Gan 
//

#include "basic_stock.hpp"
#include "portfolio.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>

int main(int argc, const char * argv[]) {
    
    // read stocks
    std::vector<Stock> stocks = read_portfolio("portfolio.txt");
    
    // initial cash
    double initial_cash = 100000;
    
    // create a portfolio
    Portfolio myPortfolio(stocks, initial_cash);
    double initial_portfolio_value = myPortfolio.calculate_total_value();
    std::cout << "Initial Portfolio Value: " << initial_portfolio_value << std::endl;
    // initial value: 100000 + 110(78.54) + 200(189.72) + 100(173.88)
    
    // Buy-and-Hold initial shares
    int initial_NVDA_shares = 110;
    int initial_AAPL_shares = 200;
    int initial_GOOG_shares = 100;
    
    // transaction count
    int total_buys = 0;
    int total_sells = 0;
    
    int NVDA_trades = 0;
    int AAPL_trades = 0;
    int GOOG_trades = 0;
    
    // store portfolio values
    std::vector<double> strategy_values;
    std::vector<double> buy_hold_values;

    // generate random num using normal distribution
    std::random_device rd;
    std::mt19937 gen(321); // gen(rd());
    std::normal_distribution<double> normal(0, 1);
    
    // simulate the return & trading strategy
    int T = 1000;
    for (int t=0; t<T; t++){
        
        // NVDA price simulation
        double old_NVDA_price = myPortfolio.get_stock_price("NVDA");
        double Z_NVDA = normal(gen);
        double r_NVDA = 0.0008 + 0.030 * Z_NVDA;
        double new_NVDA_price = old_NVDA_price * (1 + r_NVDA);
        myPortfolio.update_stock_price("NVDA", new_NVDA_price);
        // NVDA trading strategy
        double B_NVDA = myPortfolio.get_reference_price("NVDA");
        // Buy
        if (new_NVDA_price <= 0.95 * B_NVDA){
            myPortfolio.buy_stock("NVDA", 10);
            myPortfolio.update_reference_price("NVDA", new_NVDA_price);
            total_buys++;
            NVDA_trades++;
        }
        // Sell
        else if (new_NVDA_price >= 1.10 * B_NVDA){
            myPortfolio.sell_stock("NVDA", 10);
            myPortfolio.update_reference_price("NVDA", new_NVDA_price);
            total_sells++;
            NVDA_trades++;
        }
        
        
        // AAPL price simulation
        double old_AAPL_price = myPortfolio.get_stock_price("AAPL");
        double Z_AAPL = normal(gen);
        double r_AAPL = 0.0004 + 0.015 * Z_AAPL;
        double new_AAPL_price = old_AAPL_price * (1 + r_AAPL);
        myPortfolio.update_stock_price("AAPL", new_AAPL_price);
        // AAPL trading strategy
        double B_AAPL = myPortfolio.get_reference_price("AAPL");
        // Buy
        if (new_AAPL_price <= 0.95 * B_AAPL){
            myPortfolio.buy_stock("AAPL", 10);
            myPortfolio.update_reference_price("AAPL", new_AAPL_price);
            total_buys++;
            AAPL_trades++;
        }
        // Sell
        else if (new_AAPL_price >= 1.10 * B_AAPL){
            myPortfolio.sell_stock("AAPL", 10);
            myPortfolio.update_reference_price("AAPL", new_AAPL_price);
            total_sells++;
            AAPL_trades++;
        }
        
        
        // GOOG price simulation
        double old_GOOG_price = myPortfolio.get_stock_price("GOOG");
        double Z_GOOG = normal(gen);
        double r_GOOG = 0.0005 + 0.020 * Z_GOOG;
        double new_GOOG_price = old_GOOG_price * (1 + r_GOOG);
        myPortfolio.update_stock_price("GOOG", new_GOOG_price);
        // GOOG trading strategy
        double B_GOOG = myPortfolio.get_reference_price("GOOG");
        // Buy
        if (new_GOOG_price <= 0.95 * B_GOOG){
            myPortfolio.buy_stock("GOOG", 10);
            myPortfolio.update_reference_price("GOOG", new_GOOG_price);
            total_buys++;
            GOOG_trades++;
        }
        // Sell
        else if (new_GOOG_price >= 1.10 * B_GOOG){
            myPortfolio.sell_stock("GOOG", 10);
            myPortfolio.update_reference_price("GOOG", new_GOOG_price);
            total_sells++;
            GOOG_trades++;
        }
        
        
        // Protfolio Value
        double strategy_value = myPortfolio.calculate_total_value();
        strategy_values.push_back(strategy_value);
        
        // Buy-and-hold portfolio value
        double buy_hold_value = initial_cash
                                + initial_NVDA_shares * new_NVDA_price
                                + initial_AAPL_shares * new_AAPL_price
                                + initial_GOOG_shares * new_GOOG_price;
        buy_hold_values.push_back(buy_hold_value);
    }
    
    
    // Report
    // max & min account value
    double max_value = *std::max_element(strategy_values.begin(), strategy_values.end());
    double min_value = *std::min_element(strategy_values.begin(), strategy_values.end());
    std::cout << "Max portfolio value: " << max_value << std::endl;
    std::cout << "Min portfolio value: " << min_value << std::endl;
    // which stock generated the most trades
    std::string most_traded_stock;
    if (NVDA_trades >= AAPL_trades && NVDA_trades >= GOOG_trades)
        most_traded_stock = "NVDA";
    else if (AAPL_trades >= NVDA_trades && AAPL_trades >= GOOG_trades)
        most_traded_stock = "AAPL";
    else
        most_traded_stock = "GOOG";
    std::cout << "Most traded stock: " << most_traded_stock << std::endl;
    // final account values
    std::cout << "Final Account Value: " << strategy_values.back() << std::endl;
    std::cout << "Final Buy-and-Hold Value: " << buy_hold_values.back() << std::endl;
    // compare of 2 approaches
    double difference = std::abs(strategy_values.back() - buy_hold_values.back());
    bool profitable = strategy_values.back() > initial_portfolio_value;
    
    std::string better_strategy;
    if (strategy_values.back() > buy_hold_values.back())
        better_strategy = "Trading Strategy";
    else if (strategy_values.back() < buy_hold_values.back())
        better_strategy = "Buy-and-Hold";
    else
        better_strategy = "Equal Performance";

    
    // Save reports to csv
    std::ofstream report_file("report.csv");

    report_file << "Item,Result" << std::endl;
    report_file << "(a) Initial Portfolio Value," << initial_portfolio_value << std::endl;
    report_file << "(b) Final Trading Strategy Value," << strategy_values.back() << std::endl;
    report_file << "(c) Final Buy-and-Hold Value," << buy_hold_values.back() << std::endl;
    report_file << "(d) Total Buy Transactions," << total_buys << std::endl;
    report_file << "(e) Total Sell Transactions," << total_sells << std::endl;
    report_file << "(f) Maximum Portfolio Value under Trading Strategy," << max_value << std::endl;
    report_file << "(g) Minimum Portfolio Value under Trading Strategy," << min_value << std::endl;
    report_file << "(h) Most Traded Stock," << most_traded_stock << std::endl;
    report_file << "(i) Trading Strategy Profitable," << (profitable ? "Yes" : "No") << std::endl;
    report_file << "(j) Better Strategy," << better_strategy << std::endl;
    report_file << "(k) Outperformance Difference," << difference << std::endl;

    report_file.close();
    
    
    // save account values to csv
    std::ofstream simulation_file("simulation_results.csv");

    simulation_file << "Time,TradingStrategy,BuyAndHold" << std::endl;
    for (int t = 0; t < T; t++)
        simulation_file << t + 1 << "," << strategy_values[t] << "," << buy_hold_values[t] << std::endl;
    simulation_file.close();
    
    
    return 0;

}
