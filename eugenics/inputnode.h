#ifndef INPUTNODE_H
#define INPUTNODE_H

#include <boost/variant.hpp>

#include "ionode.h"

// An InputNode is an input to a gate
typedef boost::variant<bool, IONode> InputNode;

#endif /* INPUTNODE_H */
