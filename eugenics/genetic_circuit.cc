#include "genetic_circuit.h"

#include <vector>

#include <cstdlib>
#include <functional>  // std::hash
#include <sstream>

#include "utility.h"

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::mt19937* rand_eng)
    : Circuit(input_num, output_num), rand_engine(rand_eng), fitness(0) {
  if (input_num < 2) {
    std::string errmsg =
        "GeneticCircuit::GeneticCircuit FATAL Need more than 2 inputs to "
        "create gate";
    errlog(errmsg);
    std::exit(EXIT_FAILURE);
  }
  std::vector<GateType> gate;
  gate.push_back(NOT);
  gate.push_back(OR);
  gate.push_back(AND);

  int num_of_gates =
      number_dist(*rand_engine);  // random number between 0 and 40
  for (int i = 0; i < num_of_gates; ++i) {
    // random number between 0 and 2
    GateType rand_gate = gate[gate_dist(*rand_engine)];

    if ((rand_gate == NOT) && (getNotCount() < 2)) {
      // only add a NOT if we don't have 2 already
      addGate(rand_gate, number_dist(*rand_engine) % 2);
    } else if ((rand_gate == OR) || (rand_gate == AND)) {
      addGate(rand_gate, number_dist(*rand_engine) % getGateCount(),
              number_dist(*rand_engine) % getGateCount());
    }
  }
}

void GeneticCircuit::setFitness(int f) { fitness = f; }

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
  std::ostringstream errstream;
  errstream << " NOT: " << getNotCount() << " AND: " << getAndCount()
            << " OR: " << getOrCount();
  errlog(errstream.str(), SHOW_POPULATION_LOG);
  return hash;
}
