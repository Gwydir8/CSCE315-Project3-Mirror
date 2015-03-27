#ifndef IONODE_H
#define IONODE_H

// An IONode is the wire connecting two gates, namely the "parent" and "child"
// gate
class IONode {
 public:
  IONode();
  // IONode(Gate &parent, Gate &child) : parent_(parent), child_(child) {
  //   value_ = parent_->evaluate();
  // }
  // virtual ~IONode();

  // accessors
  bool value() const { return value_; }
  // Gate parent() const { return parent_; }
  // Gate child() const { return child_; }

  // mutators
  void value(bool value) { value_ = value; }

 private:
  // // pointer to parent gate
  // Gate parent_;
  // OutputNode parent_;

  // // pointer to parent gate
  // Gate child_;
  // InputNode child_;

  // value at the node, which is equivalent to the output of the gate before
  // this node.
  bool value_;
};

#endif /* IONODE_H */
