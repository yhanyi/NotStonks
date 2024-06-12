#ifndef FINANCIALDATA_HPP
#define FINANCIALDATA_HPP

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
    FinancialData(const std::string& filename);

    const std::vector<DataRow>& get_data() const;
    std::vector<double> get_closing_prices() const;

   private:
    std::vector<DataRow> data;
    void read_csv(const std::string& filename);
};

#endif  // FINANCIALDATA_HPP