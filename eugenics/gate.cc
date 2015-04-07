#include "gate.h"

std::ostream& operator<<(std::ostream& os, const Gate& gate) {
  // Write circuit to circuitfile
  if (gate.type == "INVALID") {
    errlog("INVALID Gate Encountered");
  } else if (gate.type != "WIRE") {
    os << (gate.output_index + 1) << " ";
    os << gate.type;
    os << " " << (gate.input_1_index + 1);
    if (gate.input_2 != nullptr) {
      os << " " << (gate.input_2_index + 1);
    }
    os << std::endl;

    std::string errmsg =
        "ofstream<<Gate: " + std::to_string((gate.output_index + 1)) + " " +
        gate.type + " " + std::to_string((gate.input_1_index + 1));
    // if gate has two inputs, log both
    if (gate.input_2 != nullptr) {
      errmsg += " " + std::to_string((gate.input_2_index + 1));
    }
    errlog(errmsg);
  } else {
    std::string errmsg = "ofstream<<Gate: ";
    if (gate.input_1 != nullptr) {
      errmsg += std::to_string((gate.output_index + 1)) + " " + gate.type +
                " " + std::to_string((gate.input_1_index + 1));
    }
    if (gate.input_2 != nullptr) {
      errmsg += " " + std::to_string((gate.input_2_index + 1));
    }
    errmsg += " (NOT WRITTEN)";
    errlog(errmsg);
  }
  return os;
}
