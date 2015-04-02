#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <fstream>

#include "utility.h"

// if true gate::evaluate is logged
const bool DEBUG_GATE_EVALUATION = false;

// A Gate is the fundamental circuit component type
// It can be an And, Or, Not or Wire
// A gate is also used to hold the value (val) inputted into a circuit
class Gate {
 public:
  // invalid default constructor
  Gate()
      : input_1(nullptr),
        input_1_index(-1),
        input_2(nullptr),
        input_2_index(-1),
        output_index(-1),
        val(false),
        type("INVALID") {}

  // unary gate or wire
  Gate(Gate* A)
      : input_1(A),
        input_1_index(A->output_index),
        input_2(nullptr),
        input_2_index(-1),
        output_index((A->output_index)),
        val(false) {}
  Gate(int out_index, Gate* A, int in_index)
      : input_1(A),
        input_1_index(in_index),
        input_2(nullptr),
        input_2_index(-1),
        output_index(out_index),
        val(false) {}

  // binary gate
  Gate(Gate* A, Gate* B)
      : input_1(A),
        input_1_index(A->output_index),
        input_2(B),
        input_2_index(B->output_index),
        output_index(B->output_index),
        val(false) {}
  Gate(int out_index, Gate* A, Gate* B)
      : input_1(A),
        input_1_index(A->output_index),
        input_2(B),
        input_2_index(B->output_index),
        output_index(out_index),
        val(false) {}

  // wire input value
  // Gate(bool B) : input_1(nullptr), input_2(nullptr), val(B) {}
  Gate(bool B, int index)
      : input_1(nullptr),
        input_1_index(index),
        input_2(nullptr),
        input_2_index(index),
        output_index(index),
        val(B) {}

  // evaluate returns the output of a gate
  virtual bool evaluate() = 0;

  // write gate to file
  virtual void writeToFile() const = 0;

  // // // print gate to ofstream
  // friend std::ofstream& operator<<(std::ofstream& os, const Gate& gate);

 protected:
  // first input (also only input for Not gates and Wires)
  Gate* input_1;
  // first input index
  int input_1_index;
  // second input for And and Or gates
  Gate* input_2;
  // first input index
  int input_2_index;

  // output index
  int output_index;

  // truth value
  bool val;

  // type can be and, or, not or wire
  std::string type;
};

// std::ofstream& operator<<(std::ofstream& os, const Gate& gate) {
//   // right now this only prints the type, but it can and should be extended
//   // later
//   os << gate.writeToFile();
//   return os;
// }

class Not : public Gate {
 public:
  // invalid constructor
  Not() : Gate() {}
  // not constructor
  Not(Gate* A) : Gate(A) { type = "NOT"; }
  Not(int out_index, Gate* A, int in_index) : Gate(out_index, A, in_index) {
    type = "NOT";
  }

  bool evaluate() {
    bool q = !(input_1->evaluate());
    if (DEBUG_GATE_EVALUATION) {
      std::string errmsg = "Not::evaluate: !" +
                           std::to_string(input_1->evaluate()) + " = " +
                           std::to_string(q);
      errlog(errmsg);
    }
    return q;
  }

  void writeToFile() const {
    // Create filepath
    std::string directory = "";
    std::string filename = "eugenics.circuit";
    // std::string filepath = directory + filename;
    std::string filepath = filename;

    // Open filepath
    std::ofstream circuitfile(filepath, std::ios::app);

    // Write circuit to circuitfile
    circuitfile << output_index << " ";
    circuitfile << type;
    circuitfile << " " << input_1_index;
    circuitfile << std::endl;

    std::string errmsg = "Circuit::writeGateToFile: " +
                         std::to_string(output_index) + " " + type + " " +
                         std::to_string(input_1_index);
    errlog(errmsg);

    circuitfile.close();
  }
};

// a Wire is an usually used as an input node
class Wire : public Gate {
 public:
  // invalid wire
  Wire() : Gate() {}
  // input node
  // Wire(bool B) : Gate(B) {}
  Wire(bool B, int index) : Gate(B, index) { type = "NONE"; }
  // gate connector
  Wire(Gate* A) : Gate(A) { type = "WIRE"; }
  Wire(Gate* A, int index) : Gate(A, index) { type = "WIRE"; }

  bool evaluate() {
    if (input_1 == nullptr) {
      // input node
      if (DEBUG_GATE_EVALUATION) {
        std::string errmsg = "Wire::evaluate:(bool) " + std::to_string(val);
        errlog(errmsg);
      }

      return val;
    } else {
      // gate connector
      bool a = input_1->evaluate();

      if (DEBUG_GATE_EVALUATION) {
        std::string errmsg = "Wire::evaluate:(Gate*) " + std::to_string(a);
        errlog(errmsg);
      }

      return a;
    }
  }
  void setInput(bool new_input) {
    if (input_1 == nullptr) {
      val = new_input;

      std::string errmsg = "Wire::setInput: " + std::to_string(val);
      errlog(errmsg);
    } else {
      errlog("Wire isn't an input wire", true);
    }
  }

  void writeToFile() const {
    // Create filepath
    std::string directory = "";
    std::string filename = "eugenics.circuit";
    // std::string filepath = directory + filename;
    std::string filepath = filename;

    // Open filepath
    std::ofstream circuitfile(filepath, std::ios::app);

    if (type == "NONE") {
      // Write circuit to circuitfile
      circuitfile << output_index << " ";
      circuitfile << "NONE";
      circuitfile << " " << input_1_index;
      circuitfile << std::endl;
    } else {
      errlog("Gate::writeToFile() Wires are not printed to file.");
    }

    std::string errmsg = "Circuit::writeGateToFile: " +
                         std::to_string(output_index) + " " + type + " " +
                         std::to_string(input_1_index);
    errlog(errmsg);

    circuitfile.close();
  }
};

class And : public Gate {
 public:
  // invalid constructor
  And() : Gate() {}
  // and constructor
  And(Gate* A, Gate* B) : Gate(A, B) { type = "AND"; }
  And(int out_index, Gate* A, Gate* B) : Gate(out_index, A, B) { type = "AND"; }

  bool evaluate() {
    bool a = input_1->evaluate();
    bool b = input_2->evaluate();
    bool q = a && b;

    if (DEBUG_GATE_EVALUATION) {
      std::string errmsg = "And::evaluate: " + std::to_string(a) + " && " +
                           std::to_string(b) + " = " + std::to_string(q);
      errlog(errmsg);
    }
    return q;
  }

  void writeToFile() const {
    // Create filepath
    std::string directory = "";
    std::string filename = "eugenics.circuit";
    // std::string filepath = directory + filename;
    std::string filepath = filename;

    // Open filepath
    std::ofstream circuitfile(filepath, std::ios::app);

    // Write circuit to circuitfile
    circuitfile << output_index << " ";
    circuitfile << type;
    circuitfile << " " << input_1_index;
    circuitfile << " " << input_2_index;
    circuitfile << std::endl;

    std::string errmsg = "Circuit::writeGateToFile: " +
                         std::to_string(output_index) + " " + type + " " +
                         std::to_string(input_1_index) + " " +
                         std::to_string(input_2_index);
    errlog(errmsg);

    circuitfile.close();
  }
};

class Or : public Gate {
 public:
  // invalid constructor
  Or() : Gate() {}
  // or constructor
  Or(Gate* A, Gate* B) : Gate(A, B) { type = "OR"; }
  Or(int out_index, Gate* A, Gate* B) : Gate(out_index, A, B) { type = "OR"; }

  bool evaluate() {
    bool a = input_1->evaluate();
    bool b = input_2->evaluate();
    bool q = a || b;

    if (DEBUG_GATE_EVALUATION) {
      std::string errmsg = "Or::evaluate: " + std::to_string(a) + " || " +
                           std::to_string(b) + " = " + std::to_string(q);
      errlog(errmsg);
    }

    return q;
  }
  void writeToFile() const {
    // Create filepath
    std::string directory = "";
    std::string filename = "eugenics.circuit";
    // std::string filepath = directory + filename;
    std::string filepath = filename;

    // Open filepath
    std::ofstream circuitfile(filepath, std::ios::app);

    // Write circuit to circuitfile
    circuitfile << output_index << " ";
    circuitfile << type;
    circuitfile << " " << input_1_index;
    circuitfile << " " << input_2_index;
    circuitfile << std::endl;

    std::string errmsg = "Circuit::writeGateToFile: " +
                         std::to_string(output_index) + " " + type + " " +
                         std::to_string(input_1_index) + " " +
                         std::to_string(input_2_index);
    errlog(errmsg);

    circuitfile.close();
  }
};

#endif /* GATE_H*/
