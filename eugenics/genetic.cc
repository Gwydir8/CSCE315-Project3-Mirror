#include "genetic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

Circuit randomCircuit(int input_num, int output_num) {
  if(input_num < 2){
    std::string errmsg = "Need more than 2 inputs to create gate";
  errlog(errmsg);
  exit(-1);
  }
  Circuit c = Circuit(input_num, output_num);
  vector<GateType> gate = {NOT, OR, AND};
  int num_of_gates = 2;// arbitrary...
  srand(time(NULL));
  for(int i = 0; i < num_of_gates; ++i)
    {
      num_of_gates = 0 + rand() % 30; //random number between 1 and 30
      //random number between 0 and 2
      GateType rand_gate= gate[rand() % 2];

      if(rand_gate == NOT){
        c.addGate(rand_gate, c.getGateCount());
      }
      else if (rand_gate == OR || rand_gate == AND){
        c.addGate(rand_gate, c.getGateCount()-2, c.getGateCount() -1);
      }
    }
  return c;
}

Genetic::~Genetic() {}

int Genetic::fitness(Circuit c) {
  int score = 0;
  score += c.getNotCount() * 10000;
  score += c.getAndCount() * 10;
  score += c.getOrCount() * 1;
  return score;
}

void Genetic::splice() {}

void Genetic::split() {}

void Genetic::splitAndSplice() {}

void Genetic::spawnPopulation(int populationSize) {
  for (int i = 0; i < populationSize; ++i) {
    int initial_fitness = 0;
    Circuit c = randomCircuit(expected_inputs.size(), expected_outputs.size());
      std::pair<int, Circuit> zergling(fitness(c), c);
    population.insert(zergling);
  }
}


