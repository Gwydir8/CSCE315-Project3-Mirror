#ifndef INPUTNODEEVALUATOR_H
#define INPUTNODEEVALUATOR_H

#include <boost/variant.hpp>

#include "inputnode.h"

class InputNodeEvaluator : public boost::static_visitor<bool> {
 public:
  InputNodeEvaluator() {}

  bool operator()(IONode const& node) const { return node.value(); }
  bool operator()(bool const& value) const { return value; }
};


#endif /* INPUTNODEEVALUATOR_H */
