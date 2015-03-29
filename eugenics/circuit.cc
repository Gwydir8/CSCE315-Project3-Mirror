#include "circuit.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <string>

#include "utility.h"

using namespace std;

Circuit::Circuit(vector<bool> inputs, int o)
    : output_no(o), input_no(inputs.size()) {
  // initialize statistics to 0
  and_no = or_no = not_no = wire_no = 0;
  mapped_outputs = vector<int>(output_no, -1);
  // create initial input wires
  for (bool input : inputs) {
    wire_no++;
    std::string errmsg = "Circuit::Circuit: " + std::to_string(numGates()) +
                         " WIRE " + std::to_string(input);
    errlog(errmsg);

    Gate* wire = new Wire(input);
    gates.push_back(wire);
  }
}
Circuit::Circuit(int inputs, int o) : output_no(o), input_no(inputs){
  // initialize statistics to 0
  and_no = or_no = not_no = wire_no = 0;
  mapped_outputs = vector<int>(output_no, -1);
  // create initial input wires
  for (int i = 0; i < input_no; ++i) {
    wire_no++;
    std::string errmsg = "Circuit::Circuit: " + std::to_string(numGates()) +
                         " WIRE " + std::to_string(false);
    errlog(errmsg);

    Gate* wire = new Wire(false);
    gates.push_back(wire);
  }
}

int Circuit::addGate(GateType gate_type, int index_1) {
  Gate* built_gate = nullptr;
  Gate* input_1 = gates[index_1];
  if (gate_type == NOT) {
    built_gate = new Not(input_1);
    // increment number of nots
    not_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " NOT  " + std::to_string(index_1);
    errlog(errmsg);
  } else if (gate_type == WIRE) {
    built_gate = new Wire(input_1);
    // increment number of wires
    wire_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " WIRE " + std::to_string(index_1);
    errlog(errmsg);
  }
  assert(built_gate != nullptr);
  gates.push_back(built_gate);
  // gates is zero indexed
  return (gates.size() - 1);
}

int Circuit::addGate(int output_index, GateType gate_type, int index_1) {
  int actual_output_index = addGate(gate_type, index_1);
  assert(output_index == actual_output_index);
  return actual_output_index;
}

int Circuit::addGate(GateType gate_type, int index_1, int index_2) {
  Gate* built_gate = nullptr;
  Gate* input_1 = gates[index_1];
  Gate* input_2 = gates[index_2];
  if (gate_type == AND) {
    built_gate = new And(input_1, input_2);
    // increment number of ands
    and_no++;
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) +
                         " AND  " + std::to_string(index_1) + " " +
                         std::to_string(index_2);
    errlog(errmsg);
  } else if (gate_type == OR) {
    built_gate = new Or(input_1, input_2);
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

vector<vector<bool>> Circuit::evaluateAllInputs() {
  printStatistics();
  vector<vector<bool>> inputs = generateInputSet();
  vector<vector<bool>> outputs;
  for (vector<bool> input : inputs) {
    outputs.push_back(evaluateInputSet(input));
  }
  assert(!outputs.empty());
  return outputs;
}

vector<bool> Circuit::evaluateInputSet(vector<bool> input_set) {
  printStatistics();
  // initalize input wires to input_set values
  for (int i = 0; i < input_no; ++i) {
    (dynamic_cast<Wire*>(gates[i]))->setInput(input_set[i]);

    std::string errmsg = "Circuit::evaluateInputSet: input_set[" +
                         std::to_string(i) + "] = " +
                         std::to_string(input_set[i]);
    errlog(errmsg);
  }

  vector<bool> result;
  // evaluate gates in reverse order, i.e. from input to output
  reverse_iterator<vector<Gate*>::iterator> r = gates.rbegin();
  for (int i = output_no-1; i >= 0; --i) {
    Gate* output_gate = ((mapped_outputs[i] != -1) ? gates[mapped_outputs[i]] : r[i]);
    bool output = output_gate->evaluate();
    //gates_reversed = {2, 1, 0}
    //i = {2,1,0}
    //result  = { 0, 1, 2}
    result.push_back(output);

    std::string errmsg = "Circuit::evaluateInputSet: output[" +
                         std::to_string(i) + "] = " + std::to_string(output) +
                         "Current Mapped Output = [" + std::to_string(mapped_outputs[i]) + "]"
                         ;
    errlog(errmsg);
  }

  return result;
}

vector<vector<bool>> Circuit::generateInputSet() {
  vector<vector<bool>> inputset;

  // a truth table is input_no columns wide and 2^{input_no} rows tall
  for (int i = 0; i < pow(2, input_no); ++i) {
    std::string errmsg =
        "Circuit::generateInputSet: row[" + std::to_string(i) + "] = { ";

    vector<bool> row;
    for (int j = input_no - 1; j >= 0; --j) {
      int current_bit = (i >> j) & 1;
      row.push_back(current_bit);
      errmsg += std::to_string(current_bit) + " ";
    }
    errmsg += " }";
    errlog(errmsg);

    assert(row.size() == (unsigned int)input_no);
    inputset.push_back(row);
  }
  return inputset;
}

void Circuit::mapGateToOutput(int gate_index, int desired_output_index) {
    std::string errmsg = "Called with: [" + std::to_string(gate_index) + "] ";
    errlog(errmsg);
    int actual_output_index = output_no - 1 - desired_output_index;
    mapped_outputs[actual_output_index] = gate_index;
}

void Circuit::printStatistics() {
  std::string errmsg =
      "Circuit::printStatistics: WIREs = " + std::to_string(wire_no) +
      " ANDs = " + std::to_string(and_no) + " ORs = " + std::to_string(or_no) +
      " NOTs = " + std::to_string(not_no);
  errlog(errmsg);
}
