#include "genetic_circuit.h"

#include <vector>

#include <cassert>
#include <cstdlib>
#include <functional>  // std::hash
#include <sstream>

#include "utility.h"

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::minstd_rand* rand_eng)
    : Circuit(input_num, output_num), rand_engine_ptr(rand_eng), fitness(0) {
  assert(input_num >= 2);

  std::vector<GateType> gate_types{NOT, OR, AND};

  // random number between 0 and 40
  int num_of_gates = number_dist(*rand_engine_ptr);

  std::uniform_int_distribution<> gate_max_dist{0, num_of_gates};

  for (int i = 0; i < num_of_gates; ++i) {
    // random number between 0 and 2
    GateType rand_gate = gate_types[gate_max_dist(*rand_engine_ptr) % 3];

    if ((rand_gate == NOT) && (getNotCount() < 2)) {
      // only add a NOT if we don't have 2 already
      addGate(rand_gate, gate_max_dist(*rand_engine_ptr) % getGateCount());
    } else if ((rand_gate == OR) || (rand_gate == AND)) {
      addGate(rand_gate, gate_max_dist(*rand_engine_ptr) % getGateCount(),
              gate_max_dist(*rand_engine_ptr) % getGateCount());
    }
  }
  generateFitness();
}

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::minstd_rand* rand_eng,
                               std::vector<Gate*> gates)
    : Circuit(input_num, output_num), rand_engine_ptr(rand_eng) {
  for (Gate* gate : gates) {
    if (gate->type == "WIRE") {
      errlog("GeneticCircuit::GeneticCircuit Wires are not added");
    } else if (gate->type == "NONE") {
      errlog("GeneticCircuit::GeneticCircuit NONE Wires are not added");
    } else if (gate->type == "NOT") {
      addGate(GateType(NOT), gate->input_1_index);
    } else if (gate->type == "AND") {
      addGate(GateType(AND), gate->input_1_index, gate->input_2_index);
    } else if (gate->type == "OR") {
      addGate(GateType(OR), gate->input_1_index, gate->input_2_index);
    } else if (gate->type == "INVALID") {
      errlog("GeneticCircuit::GeneticCircuit FATAL Invalid Gate Encountered");
      std::exit(EXIT_FAILURE);
    } else {
      errlog("GeneticCircuit::GeneticCircuit FATAL Unknown Gate Encountered");
      std::exit(EXIT_FAILURE);
    }
  }
  generateFitness();
}

int GeneticCircuit::generateFitness() {
  int score = 0;
  score += getNotCount() * 10000;
  score += getAndCount() * 10;
  score += getOrCount() * 1;
  fitness = score;
  return score;
}


std::size_t GeneticCircuit::hash_circ() {
  std::string s = "";
  std::hash<std::string> hash_fn;

  BooleanTable outputs = evaluateAllInputs();

  for (std::vector<bool> row : outputs) {
    for (bool bit : row) {
      s += std::to_string((int)bit);
    }
  }

  /* std::cout << "Hashing..." << std::endl; */
  std::size_t hash = hash_fn(s);
  /* std::cout << "Done Hashing..: " << hash << std::endl; */
  if (SHOW_POPULATION_LOG) {
    std::ostringstream errstream;
    errstream << " NOT: " << getNotCount() << " AND: " << getAndCount()
              << " OR: " << getOrCount();
    errlog(errstream.str(), SHOW_POPULATION_LOG);
  }
  return hash;
}
