#ifndef UNARY_GATE_H
#define UNARY_GATE_H

#include <boost/variant.hpp>

#include "gate.h"
#include "inputnode.h"

// a UngaryGate has one input
class UnaryGate : public Gate {
 public:
  UnaryGate();
  UnaryGate(InputNode A) : A_(A) {}

  // virtual ~UnaryGate();

  // evaluate gate
  virtual bool evaluate() = 0;

 protected:
  // A is only input
  InputNode A_;
};

class Not : public UnaryGate {
 public:
  Not();
  Not(InputNode A) : UnaryGate(A) {}

  // virtual ~Not();

  // evaluate gate
  // virtual bool evaluate() { return !A_; }
  virtual bool evaluate() {
    // evaluate node
    bool q = !(boost::apply_visitor(InputNodeEvaluator(), A_));

    // set Gate's Q_ to q
    Q_ = q;
    return q;
  }
};

#endif /* UNARY_GATE_H */
