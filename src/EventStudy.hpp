#ifndef EVENTSTUDY_HPP
#define EVENTSTUDY_HPP

#include <vector>

class EventStudy {
   public:
    static std::vector<double> calculate_abnormal_returns(const std::vector<double>& returns, const std::vector<double>& market_returns);
    static double cumulative_abnormal_return(const std::vector<double>& abnormal_returns);
};

#endif  // EVENTSTUDY_HPP
