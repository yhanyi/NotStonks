#ifndef GENETICALGORITHM_HPP
#define GENETICALGORITHM_HPP

#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <vector>

class GeneticAlgorithm {
   public:
    using Individual = std::vector<double>;

    GeneticAlgorithm(int population_size, int num_generations, double mutation_rate, int chromosome_length);

    Individual optimize(const std::function<double(const Individual&)>& fitness_function);

   private:
    int population_size;
    int num_generations;
    double mutation_rate;
    int chromosome_length;

    std::vector<Individual> population;
    std::vector<double> fitness;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution{0.0, 1.0};

    void initialize_population();

    void evaluate_fitness(const std::function<double(const Individual&)>& fitness_function);

    void select_parents();

    void perform_crossover();

    void perform_mutation();

    void replace_population();

    Individual get_best_individual();
};

#endif  // GENETICALGORITHM_HPP
