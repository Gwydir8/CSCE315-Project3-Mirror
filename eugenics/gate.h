#ifndef GATE_H
#define GATE_H

#include <iostream>

#include "utility.h"

class Gate {
 public:
  Gate(Gate* A) : input_1(A) {}
  Gate(Gate* A, Gate* B) : input_1(A), input_2(B) {}
  Gate(bool B) : val(B) {}
  /* virtual bool evaluate() = 0; */
  virtual bool evaluate() { return false; };

 protected:
  bool val;
  Gate* input_1 = nullptr;
  Gate* input_2;
};

class Not : public Gate {
 protected:
 public:
  Not();
  Not(Gate* A) : Gate(A) {}

  bool evaluate() {
    bool q = !(input_1->evaluate());
    std::string errmsg = "Not::evaluate: !" +
                         std::to_string(input_1->evaluate()) + " = " +
                         std::to_string(q) + ".";
    errlog(errmsg);
    return q;
  }
};

class Wire : public Gate {
 public:
  Wire();
  Wire(bool B) : Gate(B) {}
  Wire(Gate* A) : Gate(A) {}

  bool evaluate() {
    if (input_1 == nullptr) {
      std::string errmsg = "Wire::evaluate:(bool) " + std::to_string(val);
      errlog(errmsg);
      return val;
    } else {
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
      std::cerr << "Wire isn't an input wire\n";
    }
  }
};

class And : public Gate {
 public:
  And();
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
 protected:
 public:
  Or();
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
