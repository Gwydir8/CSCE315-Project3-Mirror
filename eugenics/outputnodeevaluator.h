#ifndef OUTPUTNODEEVALUATOR_H
#define OUTPUTNODEEVALUATOR_H

#include <boost/variant.hpp>

#include "ionode.h"

class OutputNodeEvaluator : public boost::static_visitor<bool> {
 public:
  OutputNodeEvaluator() {}

  bool operator()(IONode const& node) const { return node.value(); }
  bool operator()(bool const& value) const { return value; }
};

#endif /* OUTPUTNODEEVALUATOR_H */
