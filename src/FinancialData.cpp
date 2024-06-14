#include "FinancialData.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

FinancialData::FinancialData(const std::string& filename) {
    read_csv(filename);
}

const std::vector<DataRow>& FinancialData::get_data() const {
    return data;
}

std::vector<double> FinancialData::get_closing_prices() const {
    std::vector<double> closing_prices;
    for (const auto& row : data) {
        closing_prices.push_back(row.close);
    }
    return closing_prices;
}

void FinancialData::read_csv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        DataRow row;

        std::getline(lineStream, row.date, ',');
        std::getline(lineStream, cell, ',');
        row.open = std::stod(cell);
        std::getline(lineStream, cell, ',');
        row.high = std::stod(cell);
        std::getline(lineStream, cell, ',');
        row.low = std::stod(cell);
        std::getline(lineStream, cell, ',');
        row.close = std::stod(cell);
        std::getline(lineStream, cell, ',');
        row.adj_close = std::stod(cell);
        std::getline(lineStream, cell, ',');
        row.volume = std::stod(cell);

        data.push_back(row);
    }
}
