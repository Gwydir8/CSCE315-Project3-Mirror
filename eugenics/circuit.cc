#include "circuit.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include "utility.h"

Circuit::Circuit(std::vector<bool> inputs, int o)
    : output_no(o), input_no(inputs.size()) {
  // initialize statistics to 0
  and_no = or_no = not_no = wire_no = 0;
  mapped_outputs = std::vector<int>(output_no, -1);
  // create initial input wires
  for (unsigned long i = 0; i < inputs.size(); ++i) {
    wire_no++;
    std::string errmsg = "Circuit::Circuit: " + std::to_string(getGateCount()) +
                         " WIRE " + std::to_string(inputs[i]);
    errlog(errmsg);

    Gate* wire = new Wire(inputs[i], i);
    gates.push_back(wire);
  }
}

Circuit::Circuit(int inputs, int o) : output_no(o), input_no(inputs) {
  // initialize statistics to 0
  and_no = or_no = not_no = wire_no = 0;
  mapped_outputs = std::vector<int>(output_no, -1);
  // create initial input wires
  for (int i = 0; i < input_no; ++i) {
    wire_no++;
    std::string errmsg = "Circuit::Circuit: " + std::to_string(getGateCount()) +
                         " WIRE " + std::to_string(i);
    errlog(errmsg);

    Gate* wire = new Wire(false, i);
    gates.push_back(wire);
  }
}

Circuit::~Circuit() {
  // std::cerr << __FUNCTION__ << std::endl << *this << std::endl;
  // std::cerr << "~Circuit :" << std::endl;// << *this << std::endl;
  // std::reverse_iterator<std::vector<Gate*>::iterator> r = gates.rbegin();
  // for (std::size_t i = 0; i < gates.size(); ++i) {
  //   // delete r[i];
  // }
  //  for (Gate* gate: gates) {
  //    delete gate;
  //  }
  // for (std::size_t i = 0; i < gates.size(); ++i) {
  //   if (gates[i] != nullptr) {
  //     // std::cerr << "~Circuit Deleting: " << std::endl
  //     //           << *(gates[i]) << std::endl;
  //     delete gates[i];
  //     gates[i] = nullptr;
  //   }
  // }
}

int Circuit::addGate(GateType gate_type, int index_1) {
  Gate* built_gate = nullptr;
  Gate* input_1 = gates[index_1];
  if (gate_type == NOT) {
    built_gate = new Not(gates.size(), input_1, index_1);
    // increment number of nots
    not_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " NOT  " + std::to_string(index_1);
    errlog(errmsg);
    // warning if not_no exceeds 2
    if (not_no > 2) {
      std::string errmsg =
          "Circuit::addGate: WARNING more than 2 NOTs in circuit";
      errlog(errmsg);
    }
  } else if (gate_type == WIRE) {
    built_gate = new Wire(input_1, index_1);
    // increment number of wires
    wire_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " WIRE " + std::to_string(index_1);
    errlog(errmsg);
    errlog(
        "Circuit::addGate: WARNING you probably want to use mapGateToOutput "
        "instead of adding a Wire");
  }
  assert(built_gate != nullptr);
  gates.push_back(built_gate);
  // gates is zero indexed
  return (gates.size() - 1);
}

int Circuit::addGate(int output_index, GateType gate_type, int index_1) {
  int actual_output_index = addGate(gate_type, index_1);
  assert(output_index == actual_output_index);
  if (output_index != actual_output_index) {
    errlog("Circuit::addGate WARNING output_index != actual_output_index");
  }
  return actual_output_index;
}

int Circuit::addGate(GateType gate_type, int index_1, int index_2) {
  Gate* built_gate = nullptr;
  Gate* input_1 = gates[index_1];
  Gate* input_2 = gates[index_2];
  if (gate_type == AND) {
    built_gate = new And(gates.size(), input_1, input_2);
    // increment number of ands
    and_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " AND  " + std::to_string(index_1) + " " +
                         std::to_string(index_2);
    errlog(errmsg);
  } else if (gate_type == OR) {
    built_gate = new Or(gates.size(), input_1, input_2);
    // increment number of or
    or_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " OR   " + std::to_string(index_1) + " " +
                         std::to_string(index_2);
    errlog(errmsg);
  }
  assert(built_gate != nullptr);
  gates.push_back(built_gate);
  // gates is zero indexed
  return (gates.size() - 1);
}

int Circuit::addGate(int output_index, GateType gate_type, int index_1,
                     int index_2) {
  int actual_output_index = addGate(gate_type, index_1, index_2);
  assert(output_index == actual_output_index);
  return actual_output_index;
}

BooleanTable Circuit::evaluateAllInputs() {
  printStatistics();
  BooleanTable inputs = generateInputSet();
  BooleanTable outputs;
  for (std::vector<bool> input : inputs) {
    std::vector<bool> output = evaluateInputSet(input);
    outputs.push_back(output);
  }
  assert(!outputs.empty());

  for (std::vector<bool> row : outputs) {
    std::string errmsg = "Circuit::evaluateAllInputs { ";
    for (bool val : row) {
      errmsg += std::to_string(val) + " ";
    }
    errmsg += "}";
    errlog(errmsg);
  }
  return outputs;
}

std::vector<bool> Circuit::evaluateInputSet(std::vector<bool> input_set) {
  printStatistics();
  // initalize input wires to input_set values
  for (int i = 0; i < input_no; ++i) {
    (dynamic_cast<Wire*>(gates[i]))->setInput(input_set[i]);

    std::string errmsg = "Circuit::evaluateInputSet: input_set[" +
                         std::to_string(i) + "] = " +
                         std::to_string(input_set[i]);
    errlog(errmsg);
  }

  std::vector<bool> result;
  // evaluate gates in reverse order, i.e. from input to output
  std::reverse_iterator<std::vector<Gate*>::iterator> r = gates.rbegin();
  for (int i = output_no - 1; i >= 0; --i) {
    Gate* output_gate =
        ((mapped_outputs[i] != -1) ? gates[mapped_outputs[i]] : r[i]);
    bool output = output_gate->evaluate();
    // gates_reversed = {2, 1, 0}
    // i = {2,1,0}
    // result  = { 0, 1, 2}
    result.push_back(output);

    // std::string errmsg = "Circuit::evaluateInputSet: output[" +
    //                      std::to_string(i) + "] = " + std::to_string(output)
    //                      +
    //                      " Current Mapped Output = [" +
    //                      std::to_string(mapped_outputs[i]) + "]";
    std::string map_string = "NONE";
    if (mapped_outputs[i] == -1) {
      map_string = std::to_string(i);
    } else {
      map_string = std::to_string(mapped_outputs[i]);
    }
    std::string errmsg = "Circuit::evaluateInputSet: output[" +
                         std::to_string(i) + "] = " + std::to_string(output) +
                         " (Current Mapping: " + map_string + " -> " +
                         std::to_string(i) + ")";
    errlog(errmsg);
  }

  return result;
}

BooleanTable Circuit::generateInputSet() {
  BooleanTable inputset;

  // a truth table is input_no columns wide and 2^{input_no} rows tall
  for (int i = 0; i < pow(2, input_no); ++i) {
    std::string errmsg =
        "Circuit::generateInputSet: row[" + std::to_string(i) + "] = { ";

    std::vector<bool> row;
    for (int j = input_no - 1; j >= 0; --j) {
      int current_bit = (i >> j) & 1;
      row.push_back(current_bit);
      errmsg += std::to_string(current_bit) + " ";
    }
    errmsg += "}";
    errlog(errmsg);

    assert(row.size() == (unsigned int)input_no);
    inputset.push_back(row);
  }
  return inputset;
}

void Circuit::mapGateToOutput(int gate_index, int desired_output_index) {
  // int actual_output_index = output_no - 1 - desired_output_index;
  int actual_output_index = mapped_outputs.size() - 1 - desired_output_index;
  std::string errmsg = "Circuit::mapGateToOutput actual_output_index: " +
                       std::to_string(mapped_outputs.size()) + " - 1 - " +
                       std::to_string(desired_output_index);
  errlog(errmsg);
  errmsg = "Circuit::mapGateToOutput mapping: " + std::to_string(gate_index) +
           " -> " + std::to_string(actual_output_index);
  errlog(errmsg);
  mapped_outputs[actual_output_index] = gate_index;
}

void Circuit::printStatistics() {
  std::string errmsg =
      "Circuit::printStatistics: WIREs = " + std::to_string(wire_no) +
      " ANDs = " + std::to_string(and_no) + " ORs = " + std::to_string(or_no) +
      " NOTs = " + std::to_string(not_no);
  errlog(errmsg);
}

// std::istream& operator>>(std::istream& is, Circuit& circuit) {

// }

std::ostream& operator<<(std::ostream& os, const Circuit& circuit) {
  for (Gate* gate : circuit.gates) {
    os << *gate;
  }

  return os;
}

Circuit Circuit::writeCircuitToFile() const {
  // Create filepath
  std::string directory = "";
  std::string filename = "eugenics.circuit";
  // std::string filepath = directory + filename;
  std::string filepath = filename;

  // Open filepath
  std::ofstream circuitfile(filepath, std::ios::app);

  std::string errmsg = "Circuit::writeCircuitToFile: " + filepath;
  errlog(errmsg);

  // Write circuit to circuitfile
  circuitfile << *this;
  errlog("Circuit::writeCircuitToFile: write complete");

  circuitfile.close();
  return *this;
}
