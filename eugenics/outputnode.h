#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include <boost/variant.hpp>

#include "ionode.h"

typedef boost::variant<bool, IONode> OutputNode;

class OutputNodeEvaluator : public boost::static_visitor<bool> {
 public:
  OutputNodeEvaluator() {}

  bool operator()(IONode const& node) const { return node.value(); }
  bool operator()(bool const& value) const { return value; }
};



#endif /* OUTPUTNODE_H */
