#ifndef GATE_H
#define GATE_H

#include "inputnode.h"
#include "outputnode.h"

class Gate {
 public:
  Gate() {}

  // virtual ~Gate() = 0;

  virtual bool evaluate() = 0;

  OutputNode Q() { return Q_; }

 protected:
  // All gates have one output, Q
  OutputNode Q_;
};

#endif /* GATE_H */
