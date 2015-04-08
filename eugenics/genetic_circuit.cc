#include "genetic_circuit.h"

#include <vector>

#include <cassert>
#include <cstdlib>
#include <functional>  // std::hash
#include <sstream>

#include "utility.h"

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::mt19937* rand_eng)
    : Circuit(input_num, output_num), rand_engine_ptr(rand_eng), fitness(0) {
  assert(input_num >= 2);

  std::vector<GateType> gate_types{NOT, OR, AND};

  int num_of_gates =
      number_dist(*rand_engine_ptr);  // random number between 0 and 28
  std::uniform_int_distribution<> gate_max_dist{0, num_of_gates};

  for (int i = 0; i < num_of_gates; ++i) {
    // random number between 0 and 2
    GateType rand_gate = gate_types[gate_max_dist(*rand_engine_ptr) % 3];

    if ((rand_gate == NOT) && (getNotCount() < 2) && i % 4 == 0) {
      // only add a NOT if we don't have 2 already
      addGate(rand_gate, gate_max_dist(*rand_engine_ptr) % getGateCount());
    } else if ((rand_gate == OR) || (rand_gate == AND)) {
      addGate(rand_gate, gate_max_dist(*rand_engine_ptr) % getGateCount(),
              gate_max_dist(*rand_engine_ptr) % getGateCount());
    }
    /* else{ */
    /*     --i; //didn't add a gate(prbly due to not constraints failing */
    /* } */
  }
}

GeneticCircuit::GeneticCircuit(int input_num, int output_num,
                               std::mt19937* rand_eng, std::vector<Gate*> gates)
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
    } else {
      errlog("GeneticCircuit::GeneticCircuit FATAL Unknown Gate Encountered");
      std::exit(EXIT_FAILURE);
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
   * std::to_string(index_to_be_mapped) , true); */

  if (converted_gate_index >= getGateCount()) {
    errlog("WOAHHH NELLY", true);
    exit(1);
  }

  mapGateToOutput(converted_gate_index, index_to_be_mapped);
}
