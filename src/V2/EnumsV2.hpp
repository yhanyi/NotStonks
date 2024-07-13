#ifndef ENUMSV2_HPP
#define ENUMSV2_HPP

enum BookSide { BID,
                ASK };

enum OrderType { MARKET,
                 LIMIT };

enum Side { BUY,
            SELL };

enum SimulationMethod {
    RANDOM_WALK,
    BLACK_SCHOLES,
    MONTE_CARLO
};

#endif  // ENUMS_HPP