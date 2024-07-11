#ifndef FINANCIALDATA_HPP
#define FINANCIALDATA_HPP

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct DataRow {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double adj_close;
    double volume;
};

class FinancialData {
   public:
    FinancialData(const std::string& filename) {
        read_csv(filename);
    }

    const std::vector<DataRow>& get_data() const {
        return data_;
    }
    std::vector<double> get_closing_prices() const {
        std::vector<double> closing_prices;
        for (const auto& row : data_) {
            closing_prices.push_back(row.close);
        }
        return closing_prices;
    }

   private:
    std::vector<DataRow> data_;

    void read_csv(const std::string& filename) {
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

            data_.push_back(row);
        }
    }
};

#endif  // FINANCIALDATA_HPP