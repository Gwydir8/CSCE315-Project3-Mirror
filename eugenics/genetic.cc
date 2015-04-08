#include "genetic.h"

#include <string>
#include <sstream>
#include <iostream>
#include <utility>    // std::map
#include <algorithm>  // std::max
#include <random>     // std::mt19937_64

#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <ctime>  // std::time

#include "gate.h"
#include "genetic_circuit.h"
#include "utility.h"

BooleanTable transposeBooleanTable(BooleanTable original);
std::vector<int> splitMapping(int split_index, std::vector<int> original_map);

Genetic::Genetic(int n, BooleanTable outputs, int population_size)
    : input_no(n),
      average_fitness(0),
      correct_found(false),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()) {
  population = spawnPopulation(population_size);
}

std::pair<std::vector<Gate *>, std::vector<Gate *>> Genetic::split(
    GeneticCircuit circuit, int split_index) {
  std::vector<Gate *> a = circuit.getGates();
  std::vector<Gate *> lhs_gates(a.begin(), a.begin() + split_index);
  std::vector<Gate *> rhs_gates(a.begin() + split_index, a.end());

  // split circuit and c2 into a and b at dist(rand_engine)
  return std::pair<std::vector<Gate *>, std::vector<Gate *>>(lhs_gates,
                                                             rhs_gates);
}

GeneticCircuit Genetic::splice(std::vector<Gate *> base_part,
                               std::vector<Gate *> appended_part) {
  std::vector<Gate *> combined_gates = base_part;
  std::vector<Gate *> a = appended_part;

  combined_gates.insert(std::end(combined_gates), std::begin(a), std::end(a));

  GeneticCircuit new_circuit(input_no, expected_outputs.front().size(),
                             &rand_engine, combined_gates);

  return new_circuit;
}

// favor c_1
std::pair<GeneticCircuit, GeneticCircuit> Genetic::splitAndSplice(
    GeneticCircuit c_1, GeneticCircuit c_2) {
  std::pair<GeneticCircuit, GeneticCircuit> swapped_circuits(c_1, c_2);

  // Generate random index to split at
  // half the time, pick one close to edge

  std::size_t max_index = std::min(c_1.getGateCount(), c_2.getGateCount()) - 1;
  std::size_t min_index =
      std::min(c_1.getSmallestSafeCut(), c_2.getSmallestSafeCut());

  std::uniform_int_distribution<> dist{static_cast<int>(min_index),
                                       static_cast<int>(max_index)};

  std::size_t split_index = dist(rand_engine);

  if (c_1.getGateCount() <= input_no || c_2.getGateCount() <= input_no) {
    split_index = input_no;
  }

  std::vector<int> split_map_of_c1 =
      splitMapping(split_index, c_1.getMapping());
  std::vector<int> split_map_of_c2 =
      splitMapping(split_index, c_2.getMapping());

  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_1_halves =
      split(c_1, split_index);
  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_2_halves =
      split(c_2, split_index);

  swapped_circuits.first = splice(c_1_halves.first, c_2_halves.second);
  swapped_circuits.second = splice(c_2_halves.first, c_1_halves.second);

  swapped_circuits.first.setMapping(split_map_of_c1);
  swapped_circuits.second.setMapping(split_map_of_c2);

  return swapped_circuits;
}

/* void GeneticCircuit::insertIntoPopulation(GeneticCircuit c){ */
/*   c.setFitness(generateFitness(c)); */
/*   std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c); */
/*   population.insert(zergling); */
/* } */

std::map<std::size_t, GeneticCircuit> *Genetic::spawnPopulation(
    std::size_t populationSize) {
  std::map<std::size_t, GeneticCircuit> *spawned_pop =
      new std::map<std::size_t, GeneticCircuit>;
  while (spawned_pop->size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    mapAndSetFitness(&c);

    std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c);
    if (spawned_pop->find(c.hash_circ()) == spawned_pop->end()) {
      spawned_pop->insert(zergling);
    }
  }

  return spawned_pop;
}

void Genetic::spawnMore(int x) {
  for (int i = 0; i < x; ++i) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    mapAndSetFitness(&c);

    std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c);
    population->insert(zergling);
  }
}
// temporary...
int getRealMapped(std::vector<int> map) {
  int total = 0;
  for (int mapping : map) {
    if (mapping > -1) {
      ++total;
      /* errlog("keeping a mapping", ); */
    }
  }
  return total;
}

void Genetic::cullHerd() {
  int initial_size = 300;
  int avg = 0;
  double total = 0.0;
  // double avg_not = 0.0;
  double avg_mapped = 0.0;

  std::map<std::size_t, GeneticCircuit>::iterator it;
  for (it = population->begin(); it != population->end(); ++it) {
    int fit = it->second.getFitness();
    total += fit;
    // avg_not += (double)it->second.getNotCount() / population->size();
    if (getRealMapped(it->second.getMapping()) > 0) {
      // std::cout << "MAPPED SO THE FITNESS IS : " << it->second.getFitness()
      //  * << std::endl;
    }
  }
  avg = total / population->size();
  errlog("Fitness Average is: " + std::to_string(avg));
  average_fitness = avg;
  errlog("Avg # of mapped gates are" + std::to_string(avg_mapped));

  it = population->begin();
  while ((it != population->end()) &&
         (population->size() > (std::size_t)(initial_size / 2))) {
    if (it->second.getFitness() > avg) {
      it = population->erase(it);
    } else {
      ++it;
    }
  }

  std::string errmsg =
      "Deleted stuff. Population is now: " + std::to_string(population->size());
  errlog(errmsg);
}

GeneticCircuit Genetic::evolve() {
  cullHerd();
  int count_loop = 0;
  while (correct_found == false) {
    if (count_loop % 20 == 10) {
      spawnMore(300);
    }
    errlog("Don't have it yet, starting cull..");
    std::vector<GeneticCircuit *> breedable;
    std::vector<GeneticCircuit *> best_stock;
    std::map<std::size_t, GeneticCircuit>::iterator it;
    for (it = population->begin(); it != population->end(); ++it) {
      // all are breedable, but one is alpha af.
      if (it->second.getFitness() < average_fitness - 2000) {
        best_stock.push_back(&(it->second));
      } else {
        breedable.push_back(&(it->second));
      }
    }

    // std::cout << best_stock.size() << std::endl;

    std::uniform_int_distribution<> dist{
        0, static_cast<int>(breedable.size() - 1)};
    /* for (std::size_t i = 0; i < breedable.size() - 1; i += 2) { */
    // for (std::size_t i = 0; i < breedable.size() - 1; i += 2) {

    int index = 10;

    if (count_loop % 20 == 10) {
      index = 100;
    }

    for (int i = 0; i < index; ++i) {
      int circ_1 = dist(rand_engine);
      int circ_2 = dist(rand_engine);
      std::pair<GeneticCircuit, GeneticCircuit> twins = splitAndSplice(
          *best_stock[circ_1 % best_stock.size()], *breedable[circ_2]);
      // splitAndSplice(*breedable[i], *breedable[i + 1]);

      mapAndSetFitness(&twins.first);
      mapAndSetFitness(&twins.second);

      // auto first_success =
      population->insert(std::pair<std::size_t, GeneticCircuit>(
          twins.first.hash_circ(), twins.first));
      // auto second_success =
      population->insert(std::pair<std::size_t, GeneticCircuit>(
          twins.second.hash_circ(), twins.second));
      // if(first_success.second == false || second_success.second == false){
      //       --i;
      // }
    }
    errlog(std::to_string(population->size()));
    cullHerd();
    ++count_loop;
    this->writeFitnessToFile();
  }
  GeneticCircuit result = population->at(hashExpectedOutput());
  return result;
}

int Genetic::generateFitness(GeneticCircuit c) {
  int score = 0;
  bool tentative_is_correct = true;
  BooleanTable actual_output = c.evaluateAllInputs();

  // transposes our vectors to work easily with columns later
  BooleanTable transposed_actual = transposeBooleanTable(actual_output);
  BooleanTable transposed_expected = transposeBooleanTable(expected_outputs);

  for (std::size_t i = 0; i < transposed_actual.size(); ++i) {
    if (transposed_actual[i] != transposed_expected[i]) {
      score += 10000;
      tentative_is_correct = false;
    } else {
      /* std::cout << "Got one right" << std::endl; */
    }
  }
  score += c.getNotCount() * 1000;
  // favor equal distribution of or : and gates
  /* score += std::abs(c.getOrCount() - c.getAndCount()) * 100; */
  score += (c.getGateCount()) * 10;
  if (tentative_is_correct) {
    correct_found = true;
  }
  return score;
}

size_t Genetic::hashExpectedOutput() {
  std::string s = "";
  std::hash<std::string> hash_fn;
  for (std::vector<bool> row : expected_outputs) {
    for (bool bit : row) {
      s += std::to_string((int)bit);
    }
  }
  std::size_t hash = hash_fn(s);
  return hash;
}

void Genetic::mapAndSetFitness(GeneticCircuit *c) {
  BooleanTable transposed_actual =
      transposeBooleanTable(c->evaluateAllInputs());
  BooleanTable transposed_expected = transposeBooleanTable(expected_outputs);
  for (std::size_t i = 0; i < transposed_actual.size(); ++i) {
    for (std::size_t j = 0; j < transposed_actual.size(); ++j) {
      if (transposed_actual[i] == transposed_expected[j]) {
        c->mapOutputToOutput(i, j);
      }
    }
  }
  int fitness = generateFitness(*c);
  c->setFitness(fitness);
}

BooleanTable transposeBooleanTable(BooleanTable original) {
  BooleanTable transposed(original.front().size());

  for (std::size_t i = 0; i < original.front().size(); ++i) {
    for (std::size_t j = 0; j < original.size(); ++j) {
      transposed[i].push_back(original[j][i]);
    }
  }

  return transposed;
}
std::vector<int> splitMapping(int split_index, std::vector<int> original_map) {
  std::vector<int> split_map = original_map;
  for (std::size_t i = 0; i < split_map.size(); ++i) {
    if (split_map[i] >= split_index) {
      split_map[i] = -1;
      // errlog("Killing a mapping");
    } else if (split_map[i] > -1) {
      // errlog("keeping a mapping");
    }
  }
  return split_map;
}

void Genetic::writeFitnessToFile() const {
  // Create filepath
  std::string directory = "";
  std::string filename = "genetic.fitness";

  // std::string filepath = directory + filename;
  std::string filepath = filename;

  // Open filepath
  std::ofstream circuitfile(filepath, std::ios::app);

  std::string errmsg = "Circuit::writeCircuitToFile: " + filepath;
  errlog(errmsg);

  // Write circuit to circuitfile
  circuitfile << average_fitness << "\n-\n";
  errlog("Circuit::writeCircuitToFile: write complete");

  circuitfile.close();
}
