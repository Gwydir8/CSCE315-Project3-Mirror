#include "genetic_circuit.h"

#include <vector>

#include <cassert>
#include <cstdlib>
#include <functional>  // std::hash
#include <sstream>

#include "utility.h"

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::mt19937_64* rand_eng)
    : Circuit(input_num, output_num), rand_engine_ptr(rand_eng), fitness(0) {
  assert(input_num >= 2);

  // minimum number of gates
  int min_number_gates = 0;
  // maximum number of gates
  int max_number_gates = 36;

  std::vector<GateType> gate_types{NOT, OR, AND};

  std::uniform_int_distribution<> number_dist{min_number_gates,
                                              max_number_gates};

  int num_of_gates = number_dist(*rand_engine_ptr);  // random number between
                                                     // min_number_gates and
                                                     // max_number_gates

  // distribution for random number between min_number of gates and number of
  // gates chosen for this circuit
  std::uniform_int_distribution<> gate_max_dist{min_number_gates, num_of_gates};

  // if you want to print out the random numbers:
  // std::ostringstream errstream;
  // errstream << "Random Number: " << gate_max_dist(*rand_engine_ptr);
  // errlog(errstream.str());

  for (int i = 0; i < num_of_gates; ++i) {
    // random number between 0 and 2
    GateType rand_gate = gate_types[gate_max_dist(*rand_engine_ptr) % 3];
    if (i == num_of_gates - 1) {
      addGate(GateType(NOT), getGateCount() - 1);
    }

    if ((rand_gate == NOT) && (getNotCount() < 1) && (i % 4 == 0)) {
      // only add a NOT if we don't have 2 already
      addGate(rand_gate, gate_max_dist(*rand_engine_ptr) % getGateCount());
    } else if ((rand_gate == OR) || (rand_gate == AND)) {
      addGate(rand_gate, gate_max_dist(*rand_engine_ptr) % getGateCount(),
              gate_max_dist(*rand_engine_ptr) % getGateCount());
    // } else {
    //   errlog("GeneticCircuit::GeneticCircuit FATAL Unknown Gate Encountered");
    //   std::exit(EXIT_FAILURE);
    }
  }
}

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::mt19937_64* rand_eng,
                               std::vector<Gate*> gates)
    : Circuit(input_num, output_num), rand_engine_ptr(rand_eng) {
  for (Gate* gate : gates) {
    if (gate->type == "WIRE") {
      errlog("GeneticCircuit::GeneticCircuit Wires are not added");
    } else if (gate->type == "NONE") {
      errlog("GeneticCircuit::GeneticCircuit NONE Wires are not added");
    } else if (gate->type == "NOT") {
      if (getNotCount() < 2) {
        addGate(GateType(NOT), gate->input_1_index);
      } else {
        addGate(GateType(OR), gate->input_1_index, gate->input_1_index);
      }
    } else if (gate->type == "AND") {
      addGate(GateType(AND), gate->input_1_index, gate->input_2_index);
    } else if (gate->type == "OR") {
      addGate(GateType(OR), gate->input_1_index, gate->input_2_index);
    } else if (gate->type == "INVALID") {
      errlog("GeneticCircuit::GeneticCircuit FATAL Invalid Gate Encountered");
      std::exit(EXIT_FAILURE);
    // } else {
    //   errlog("GeneticCircuit::GeneticCircuit FATAL Unknown Gate Encountered");
    //   std::exit(EXIT_FAILURE);
    }
  }
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

int GeneticCircuit::getSmallestSafeCut() {
  int smallest_safe_cut = input_no;
  for (int potential : mapped_outputs) {
    if (potential > smallest_safe_cut && potential < getGateCount() - 1) {
      smallest_safe_cut = potential;
    }
  }
  // temporary logging to see if mapping is working
  /* if(smallest_safe_cut > input_no){ */
  /*   std::cout << "MAPPING IS WORKING!!!" << std::endl; */
  /* } */
  return smallest_safe_cut;
}







// index starts at 0
// helper function to avoid conversions.
void GeneticCircuit::mapOutputToOutput(int to_map, int index_to_be_mapped) {
  if (mapped_outputs[index_to_be_mapped] != -1) {
    return;  // already mapped don't remap
  }
  // convert
  int converted_gate_index = getGateCount() - getOutputCount() + to_map;
  /* errlog("Mapping " + std::to_string(converted_gate_index) + " to " +
   * std::to_string(index_to_be_mapped) ); */

  if (converted_gate_index >= getGateCount()) {
    errlog("WOAHHH NELLY");
    exit(1);
  }

  mapGateToOutput(converted_gate_index, index_to_be_mapped);
}
