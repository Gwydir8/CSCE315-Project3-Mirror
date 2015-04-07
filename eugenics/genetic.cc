#include "genetic.h"

#include <string>
#include <sstream>
#include <iostream>
#include <utility>    // std::map
#include <algorithm>  // std::max
#include <random>     // std::mt19937

#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <ctime>  // std::time

#include "gate.h"
#include "genetic_circuit.h"
#include "utility.h"

Genetic::Genetic(int n, BooleanTable outputs, int population_size)
    : input_no(n),
      expected_outputs(outputs),
      correct_found(false),
      rand_engine(std::random_device{}()) {
  population = spawnPopulation(population_size);
}

std::pair<std::vector<Gate *>, std::vector<Gate *> > Genetic::split(
    GeneticCircuit circuit, int split_index) {

  std::vector<Gate *> a = circuit.getGates();
  std::vector<Gate *> lhs_gates(a.begin(), a.begin() + split_index);
  std::vector<Gate *> rhs_gates(a.begin() + split_index, a.end());

  // split circuit and c2 into a and b at dist(rand_engine)
  return std::pair<std::vector<Gate *>, std::vector<Gate *> >(lhs_gates,
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

std::pair<GeneticCircuit, GeneticCircuit> Genetic::splitAndSplice(
    GeneticCircuit c_1, GeneticCircuit c_2) {
  std::pair<GeneticCircuit, GeneticCircuit> swapped_circuits(c_1, c_2);

  // Generate random index to split at
  // half the time, pick one close to edge
  //
  int max_index = std::min(c_1.getGateCount(), c_2.getGateCount()) - 1;
  int min_index = std::min(c_1.getSmallestSafeCut(), c_2.getSmallestSafeCut());
  std::uniform_int_distribution<> dist{
      input_no, max_index};

  int split_index = dist(rand_engine);

  if (c_1.getGateCount() <= input_no || c_2.getGateCount() <= input_no) {
    split_index = input_no;
  }

  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_1_halves =
      split(c_1, split_index);
  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_2_halves =
      split(c_2, split_index);

  swapped_circuits.first = splice(c_1_halves.first, c_2_halves.second);
  swapped_circuits.second = splice(c_2_halves.first, c_1_halves.second);

  return swapped_circuits;
}

/* void GeneticCircuit::insertIntoPopulation(GeneticCircuit c){ */
/*   c.setFitness(generateFitness(c)); */
/*   std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c); */
/*   population.insert(zergling); */
/* } */

std::map<std::size_t, GeneticCircuit>* Genetic::spawnPopulation(
    std::size_t populationSize) {
  std::map<std::size_t, GeneticCircuit>* spawned_pop = new std::map<std::size_t, GeneticCircuit>;
  while (spawned_pop->size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    c.setFitness(generateFitness(c));


    std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c);
    if(spawned_pop->find(c.hash_circ()) == spawned_pop->end()){
      spawned_pop->insert(zergling);
    }
  }

  return spawned_pop;
}

void Genetic::cullHerd() {
  int initial_size = 1000;
  int avg = 0;
  double total = 0.0;
  double avg_not = 0.0;
  std::map<std::size_t, GeneticCircuit>::iterator it;
  for (it = population->begin(); it != population->end(); ++it) {
    int fit = generateFitness(it->second);
    total += fit;
    /* avg_not += (double)it->second.getNotCount() / population->size(); */
  }
  avg  = total / population->size();
  errlog("Fitness Average is: " + std::to_string(avg), true);
  /* errlog("Avg Not" + std::to_string(avg_not), true); */
  //keep going until either deletes most or half
  /* while(population->size() > (initial_size / 1.8)){ */
  /*   avg /= 1.5; */
    it = population->begin();
    while (it != population->end() && population->size() > initial_size / 2) {
      if (generateFitness(it->second) > avg) {
        it = population->erase(it);
      } else {
        ++it;
      }
  }

  std::string errmsg =
    "Deleted stuff. Population is now: " + std::to_string(population->size());
  errlog(errmsg, true);
}

GeneticCircuit Genetic::evolve(){
  while(correct_found == false){
    errlog("Don't have it yet, starting cull..", true);
    cullHerd();
    std::vector<GeneticCircuit *> breedable;
    std::map<std::size_t, GeneticCircuit>::iterator it;
    for (it = population->begin(); it != population->end(); ++it) {
      //all are breedable, but one is alpha af.
      breedable.push_back(&(it->second));
      /* if(it->second.getFitness() < best_fitness || best_fitness == -1){ */
      /*   most_breedable = &(it->second); */
      /*   best_fitness = most_breedable->getFitness(); */
      /* } */
    }

    std::uniform_int_distribution<> dist{
        0, breedable.size() -1};


    /* for (std::size_t i = 0; i < breedable.size() - 1; i += 2) { */
    for (std::size_t i = 0; i < 10; ++i) {
    int circ_1 = dist(rand_engine);
    int circ_2 = dist(rand_engine);
      std::pair<GeneticCircuit, GeneticCircuit> twins =
        /* splitAndSplice(*breedable[i], *breedable[i + 1]); */
        splitAndSplice(*breedable[circ_1], *breedable[circ_2]);
      twins.first.setFitness(generateFitness(twins.first));
      twins.second.setFitness(generateFitness(twins.second));


      auto first_success = population->insert(std::pair<std::size_t, GeneticCircuit>(
            twins.first.hash_circ(), twins.first));
      auto second_success = population->insert(std::pair<std::size_t, GeneticCircuit>(
            twins.second.hash_circ(), twins.second));

      /* if(first_success.second == false || second_success.second == false){ */
      /*       --i; */
      /* } */

    }
    errlog(std::to_string(population->size()), true);
  }
  GeneticCircuit result = population->at(hashExpectedOutput());
  return result;
}

int Genetic::generateFitness(GeneticCircuit c) {
  int score = 0;
  bool tentative_is_correct = true;
  BooleanTable actual_output = c.evaluateAllInputs();

    BooleanTable transposed_actual(actual_output[0].size());
    BooleanTable transposed_expected(actual_output[0].size());
    //transposes our vectors to work easily with columns later
      for (int i = 0; i < actual_output[0].size(); ++i) {
        for (int j = 0; j < actual_output.size(); ++j) {
          transposed_actual[i].push_back(actual_output[j][i]);
          transposed_expected[i].push_back(expected_outputs[j][i]);
          std::cout << transposed_expected[i][j];
        }
          std::cout << std::endl;
      }

  for (std::size_t i = 0; i < transposed_actual.size(); ++i) {
    if (transposed_actual[i] != transposed_expected[i]) {
      score += 10000;
      tentative_is_correct = false;
    }
    else{
      std::cout << "Got one right" << std::endl;
    }
  }

  /* for (std::size_t i = 0; i < actual_output.size(); ++i) { */
  /*   if (actual_output[i] != expected_outputs[i]) { */
  /*     score += 10000; */
  /*     tentative_is_correct = false; */
  /*   } */
  /* } */
  score += c.getNotCount() * 1000;
  //favor equal distribution of or : and gates
  score += std::abs(c.getOrCount() - c.getAndCount()) * 100;
  /* score += (c.getOrCount() + c.getAndCount()) * 10; */
  if (tentative_is_correct) {
    correct_found = true;
  }
  return score;
}

size_t Genetic::hashExpectedOutput(){
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

