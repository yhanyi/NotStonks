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

    GeneticAlgorithm(int population_size, int num_generations, double mutation_rate, int chromosome_length)
        : population_size(population_size), num_generations(num_generations), mutation_rate(mutation_rate), chromosome_length(chromosome_length) {}

    Individual optimize(const std::function<double(const Individual&)>& fitness_function) {
        initialize_population();
        for (int generation = 0; generation < num_generations; ++generation) {
            evaluate_fitness(fitness_function);
            select_parents();
            perform_crossover();
            perform_mutation();
            replace_population();
        }
        return get_best_individual();
    }

   private:
    int population_size;
    int num_generations;
    double mutation_rate;
    int chromosome_length;

    std::vector<Individual> population;
    std::vector<double> fitness;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution{0.0, 1.0};

    void initialize_population() {
        population.clear();
        for (int i = 0; i < population_size; ++i) {
            Individual individual(chromosome_length);
            std::generate(individual.begin(), individual.end(), [this]() { return distribution(generator); });
            population.push_back(individual);
        }
    }

    void evaluate_fitness(const std::function<double(const Individual&)>& fitness_function) {
        fitness.clear();
        for (const auto& individual : population) {
            fitness.push_back(fitness_function(individual));
        }
    }

    void select_parents() {
        // Simple tournament selection
        std::vector<Individual> selected;
        for (int i = 0; i < population_size; ++i) {
            int a = std::rand() % population_size;
            int b = std::rand() % population_size;
            selected.push_back(fitness[a] > fitness[b] ? population[a] : population[b]);
        }
        population = selected;
    }

    void perform_crossover() {
        std::vector<Individual> offspring;
        for (int i = 0; i < population_size; i += 2) {
            if (i + 1 < population_size) {
                Individual parent1 = population[i];
                Individual parent2 = population[i + 1];
                Individual child1 = parent1;
                Individual child2 = parent2;
                if (distribution(generator) < 0.7) {  // Crossover probability
                    int crossover_point = std::rand() % chromosome_length;
                    for (int j = 0; j < crossover_point; ++j) {
                        std::swap(child1[j], child2[j]);
                    }
                }
                offspring.push_back(child1);
                offspring.push_back(child2);
            }
        }
        population = offspring;
    }

    void perform_mutation() {
        for (auto& individual : population) {
            for (auto& gene : individual) {
                if (distribution(generator) < mutation_rate) {
                    gene = distribution(generator);
                }
            }
        }
    }

    void replace_population() {
        // Here we just replace the entire population with the offspring
    }

    Individual get_best_individual() {
        auto max_it = std::max_element(fitness.begin(), fitness.end());
        return population[std::distance(fitness.begin(), max_it)];
    }
};

#endif  // GENETICALGORITHM_HPP
