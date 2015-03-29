#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include <boost/variant.hpp>

#include "ionode.h"

// An OutputNode is *the* output of a gate
typedef boost::variant<bool, IONode> OutputNode;

#endif /* OUTPUTNODE_H */
