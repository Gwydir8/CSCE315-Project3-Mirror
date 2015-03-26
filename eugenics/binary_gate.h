#ifndef BINARY_GATE_H
#define BINARY_GATE_H

class BinaryGate {
 protected:
  // A and B are inputs
  bool A_, B_;

 public:
  BinaryGate();
  BinaryGate(bool A, bool B) : A_(A), B_(B) {}

  // virtual ~BinaryGate();

  // evaluate gate
  virtual bool evaluate() = 0;
};

class And : public BinaryGate {
 public:
  And();
  And(bool A, bool B) : BinaryGate(A, B) {}

  // virtual ~And();

  // evaluate gate
  bool evaluate() { return A_ && B_; }
};

class Or : public BinaryGate {
 public:
  Or();
  Or(bool A, bool B) : BinaryGate(A, B) {}

  // virtual ~Or();

  // evaluate gate
  bool evaluate() { return A_ || B_; }
};

#endif /* BINARY_GATE_H */
