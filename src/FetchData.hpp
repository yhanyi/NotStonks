#ifndef FETCHDATA_HPP
#define FETCHDATA_HPP

#include <stdlib.h>

#include <filesystem>
#include <iostream>
#include <string>

static void fetch(const std::string& ticker, const std::string& start_date, const std::string& end_date, const std::string& filename) {
    std::string command = "python3 datasets/fetch.py " + ticker + " " + start_date + " " + end_date + " datasets/finance/" + filename;
    int err = std::system(command.c_str());
    if (err) {
        std::cerr << "Error executing Python script. Please ensure you have Python and the yfinance library installed." << std::endl;
        exit(err);
    }
}

static std::string cli() {
    std::string ticker, start_date, end_date, filename;
    std::cout << "Enter the ticker symbol (Example: SPY): ";
    std::cin >> ticker;
    std::cout << "Enter the start date (Example: YYYY-MM-DD): ";
    std::cin >> start_date;
    std::cout << "Enter the end date (Example: YYYY-MM-DD): ";
    std::cin >> end_date;
    // std::cout << "Enter the filename to save the data (Example: data.csv): ";
    // std::cin >> filename;
    filename = "test.csv";
    fetch(ticker, start_date, end_date, filename);
    return filename;
}

static void clean() {
    std::string path = "datasets/finance";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".csv") {
            std::filesystem::remove(entry.path());
        }
    }
    std::cout << "All .csv files in the datasets/finance folder have been deleted." << std::endl;
}

#endif  // FETCHDATA_HPP