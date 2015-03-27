#include "circuit.h"
#include <cassert>
#include <cstddef>
#include <iterator>
using namespace std;

Circuit::Circuit(vector<bool> inputs) {
    for(bool input : inputs){
        Gate* wire = new Wire(input);
        gates.push_back(wire);
        output_no = inputs.size();
    }
}
void Circuit::addGate(GateType gate_type, int index_1){
    Gate* built_gate = nullptr;
    Gate* input_1 = gates[index_1];
    if(gate_type == NOT){
        built_gate = new Not(input_1);
    }
    else if(gate_type == WIRE){
        built_gate = new Wire(input_1);
    }
    assert(built_gate != nullptr);
    gates.push_back(built_gate);
}


void Circuit::addGate(GateType gate_type, int index_1, int index_2){
    Gate* built_gate = nullptr;
    Gate* input_1 = gates[index_1];
    Gate* input_2 = gates[index_2];
    if(gate_type == AND){
        built_gate = new And(input_1, input_2);
    }
    else if(gate_type == OR){
        built_gate = new Or(input_1, input_2);
    }
    assert(built_gate != nullptr);
    gates.push_back(built_gate);
}

vector<bool> Circuit::evaluate(){
    vector<bool> result;
    reverse_iterator<vector<Gate*>::iterator > r = gates.rbegin();
    for(int i = 0; i<output_no; ++i){
        bool output = r[i]->evaluate();
        result.insert(result.begin(), output);
    }
    return result;
}
