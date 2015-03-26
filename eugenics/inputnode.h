#ifndef INPUTNODE_H
#define INPUTNODE_H

#include <boost/variant.hpp>

#include "ionode.h"

// An InputNode is an input to a gate
typedef boost::variant<bool, IONode> InputNode;

class InputNodeEvaluator : public boost::static_visitor<bool> {
 public:
  InputNodeEvaluator() {}

  bool operator()(IONode const& node) const { return node.value(); }
  bool operator()(bool const& value) const { return value; }
};



#endif /* INPUTNODE_H */
