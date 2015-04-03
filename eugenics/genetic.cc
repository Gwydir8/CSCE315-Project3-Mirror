#include "genetic.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <functional>
#include <string>
#include <time.h>
using namespace std;


Genetic::~Genetic() {}

int Genetic::fitness(GeneticCircuit c) {
  int score = 0;
  score += c.getNotCount() * 10000;
  score += c.getAndCount() * 10;
  score += c.getOrCount() * 1;
  return score;
}

void Genetic::splice() {}

void Genetic::split() {}

void Genetic::splitAndSplice() {}

size_t hash_circ(GeneticCircuit c){
    string s = "";
    std::hash<std::string> hash_fn;
    BooleanTable outputs = c.evaluateAllInputs();
    for(vector<bool> column : outputs ){
      for(bool bit : column){
        s += to_string((int)bit);
      }
    }

    cout << "Hashing..." << endl;
    size_t hash = hash_fn(s);
    cout << "Done Hashing..: " << hash << endl;
    cout << " NOT: " << c.getNotCount() << " AND: " << c.getAndCount() << " OR: " << c.getOrCount();
    return hash;
}

void Genetic::spawnPopulation(int populationSize) {
  srand(time(NULL));
  for (int i = 0; i < populationSize; ++i) {
    int initial_fitness = 0;
    GeneticCircuit c = GeneticCircuit(expected_inputs.size(), expected_outputs.size());
    c.setFitness(fitness(c));
    std::pair<int, Circuit> zergling(hash_circ(c), c);
    population.insert(zergling);
    //std::pair<iterator,bool> result_of_insert =
  }
}

