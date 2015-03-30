#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <fstream>

#include "utility.h"

// A Gate is the fundamental circuit component type
// It can be an And, Or, Not or Wire
// A gate is also used to hold the value (val) inputted into a circuit
class Gate {
 public:
  // invalid default constructor
  Gate() : input_1(nullptr), input_2(nullptr), val(false), type("INVALID") {}

  // unary gate or wire
  Gate(Gate* A) : input_1(A), input_2(nullptr), val(false) {}
  // binary gate
  Gate(Gate* A, Gate* B) : input_1(A), input_2(B), val(false) {}
  // wire input value
  Gate(bool B) : input_1(nullptr), input_2(nullptr), val(B) {}

  // evaluate returns the output of a gate
  virtual bool evaluate() = 0;

  // // print gate to ofstream
  // friend std::ofstream& operator<<(std::ofstream& os, const Gate& gate) {
  //   // right now this only prints the type, but it can and should be extended
  //   // later
  //   os << gate.type;
  //   return os;
  // }


 protected:
  // first input (also only input for Not gates and Wires)
  Gate* input_1;
  // second input for And and Or gates
  Gate* input_2;

  // truth value
  bool val;

  // type can be and, or, not or wire
  std::string type;
};

class Not : public Gate {
 public:
  // invalid constructor
  Not() : Gate() {}
  // not constructor
  Not(Gate* A) : Gate(A) {}

  bool evaluate() {
    bool q = !(input_1->evaluate());
    std::string errmsg = "Not::evaluate: !" +
                         std::to_string(input_1->evaluate()) + " = " +
                         std::to_string(q);
    errlog(errmsg);
    return q;
  }
};

// a Wire is an usually used as an input node
class Wire : public Gate {
 public:
  // invalid wire
  Wire() : Gate() {}
  // input node
  Wire(bool B) : Gate(B) {}
  // gate connector
  Wire(Gate* A) : Gate(A) {}

  bool evaluate() {
    if (input_1 == nullptr) {
      // input node
      std::string errmsg = "Wire::evaluate:(bool) " + std::to_string(val);
      errlog(errmsg);

      return val;
    } else {
      // gate connector
      bool a = input_1->evaluate();

      std::string errmsg = "Wire::evaluate:(Gate*) " + std::to_string(a);
      errlog(errmsg);

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
};

class And : public Gate {
 public:
  // invalid constructor
  And() : Gate() {}
  // and constructor
  And(Gate* A, Gate* B) : Gate(A, B) {}

  bool evaluate() {
    bool a = input_1->evaluate();
    bool b = input_2->evaluate();
    bool q = a && b;

    std::string errmsg = "And::evaluate: " + std::to_string(a) + " && " +
                         std::to_string(b) + " = " + std::to_string(q);
    errlog(errmsg);
    return q;
  }
};

class Or : public Gate {
 public:
  // invalid constructor
  Or() : Gate() {}
  // or constructor
  Or(Gate* A, Gate* B) : Gate(A, B) {}

  bool evaluate() {
    bool a = input_1->evaluate();
    bool b = input_2->evaluate();
    bool q = a || b;

    std::string errmsg = "Or::evaluate: " + std::to_string(a) + " || " +
                         std::to_string(b) + " = " + std::to_string(q);
    errlog(errmsg);

    return q;
  }
};

#endif /* GATE_H*/
