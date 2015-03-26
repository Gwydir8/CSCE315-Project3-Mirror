#ifndef UNARY_GATE_H
#define UNARY_GATE_H

class UnaryGate {
 protected:
  // A is only input
  bool A_;

 public:
  UnaryGate();
  UnaryGate(bool A) : A_(A) {}

  // virtual ~UnaryGate();

  // evaluate gate
  virtual bool evaluate() = 0;
};

class Not : public UnaryGate {
 public:
  Not();
  Not(bool A) : UnaryGate(A) {}

  // virtual ~Not();

  // evaluate gate
  bool evaluate() { return !A_; }
};

#endif /* UNARY_GATE_H */
