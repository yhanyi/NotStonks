#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <map>
#include <string>
#include <vector>

#include "EventDrivenBacktesting.hpp"
#include "FinancialData.hpp"
#include "MeanReversion.hpp"
#include "RiskAdjustedPerformance.hpp"

class Benchmark {
   public:
    Benchmark(const std::string& csv_file);
    void run();

   private:
    FinancialData fd;
    std::map<std::string, double> evaluate_strategy(const std::vector<int>& signals);
    void report_results(const std::map<std::string, double>& results, const std::string& strategy_name);
};

#endif  // BENCHMARK_HPP
