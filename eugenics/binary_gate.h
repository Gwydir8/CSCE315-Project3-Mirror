#ifndef BINARY_GATE_H
#define BINARY_GATE_H

#include <boost/variant.hpp>

#include "gate.h"
#include "inputnode.h"

class BinaryGate : public Gate {
 public:
  BinaryGate();
  BinaryGate(InputNode A, InputNode B) : A_(A), B_(B) {}

  // virtual ~BinaryGate();

  // evaluate gate
  virtual bool evaluate() = 0;

 protected:
  // A and B are inputs
  InputNode A_, B_;
};

class And : public BinaryGate {
 public:
  And();
  And(InputNode A, InputNode B) : BinaryGate(A, B) {}

  // virtual ~And();

  // evaluate gate
  virtual bool evaluate() {
    // evaluate node
    bool a = (boost::apply_visitor(InputNodeEvaluator(), A_));
    bool b = (boost::apply_visitor(InputNodeEvaluator(), B_));
    bool q = a && b;

    // set Gate's Q_ to q
    Q_ = q;
    return q;
  }
};

class Or : public BinaryGate {
 public:
  Or();
  Or(InputNode A, InputNode B) : BinaryGate(A, B) {}

  // virtual ~Or();

  // evaluate gate
  virtual bool evaluate() {
    // evaluate node
    bool a = (boost::apply_visitor(InputNodeEvaluator(), A_));
    bool b = (boost::apply_visitor(InputNodeEvaluator(), B_));
    bool q = a || b;

    // set Gate's Q_ to q
    Q_ = q;
    return q;
  }
};

#endif /* BINARY_GATE_H */
