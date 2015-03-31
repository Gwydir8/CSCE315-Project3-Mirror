#include <vector>
#include "jvalgorithm.h"
#include "utility.h"

using namespace std;

Ckt_Algo::Ckt_Algo(Circuit circuit) : circ_output() { ex_list.push_back(circuit); }

bool Ckt_Algo::circuit_matches_desired(Circuit x, vector<vector<bool>> desired) {
  // generates an output set based on the circuit
  circ_output = x.evaluateAllInputs();

  // compares output set of current circuit and desired
  // make sure generated set and desired are same size
  // and NOT gates are less then or equal to 2
  if (desired == circ_output) {
    errlog("Ckt_Algo::Ckt_Algo circuit output == desired output");
    // sets generated output set to global set
    return true;
  } else {
    errlog("Ckt_Algo::Ckt_Algo circuit output != desired output");
    return false;
  }
}

void Ckt_Algo::add_not(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list[0];
    next.addGate(NOT, i);
    // check if next circuit is equal to a circuit in vector
    bool equal_to_vector = false;
    for (int j = 0; j < ex_list.size(); ++j) {
      if(next.evaluateAllInputs() == ex_list[j].evaluateAllInputs()) {
      	// it's a duplicate so don't put into vector
      	equal_to_vector = true;
      	break;
      }
    } 
    if (equal_to_vector == false) {
      ex_list.push_back(next);
      std::string errmsg = "Ckt_Algo::add_not [" + std::to_string(i) + "] = " +
	                       std::to_string(next.getGateCount()) + " NOT " +
	                       std::to_string(i);
	  errlog(errmsg);
    }   
  }
}

void Ckt_Algo::add_and(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list[0];
      next.addGate(AND, i, j);
      // check if next circuit is equal to a circuit in vector
      bool equal_to_vector = false;
      for (int k = 0; k < ex_list.size(); ++k) {
      	if(next.evaluateAllInputs() == ex_list[k].evaluateAllInputs()) {
      	  // it's a duplicate so don't put into vector
      	  equal_to_vector = true;
      	  break;
      	}
      }
      if (equal_to_vector == false) {
      	ex_list.push_back(next);
      	std::string errmsg = "Ckt_Algo::add_and [" + std::to_string(i) + "][" +
      		                std::to_string(j) + "] = " +
       	                    std::to_string(next.getGateCount()) + " AND " +
                            std::to_string(i) + " " + std::to_string(j);
      	errlog(errmsg);
  	  }	
    }
  }
}

void Ckt_Algo::add_or(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list[0];
      next.addGate(OR, i, j);
      // check if next circuit is equal to a circuit in vector
      bool equal_to_vector = false;
      for (int k = 0; k < ex_list.size(); ++k) {
      	if(next.evaluateAllInputs() == ex_list[k].evaluateAllInputs()) {
      	  // it's a duplicate so don't put into vector
      	  equal_to_vector = true;
      	  break;
      	}
      }
      if (equal_to_vector == false) {
      	ex_list.push_back(next);
      	std::string errmsg = "Ckt_Algo::add_or [" + std::to_string(i) + "][" +
      		                std::to_string(j) + "] = " +
       	                    std::to_string(next.getGateCount()) + " OR " +
                            std::to_string(i) + " " + std::to_string(j);
      	errlog(errmsg);
  	  }	
    }
  }
}



vector<vector<bool>> Ckt_Algo::search(vector<vector<bool>> desired) {
  // compares circuits wires to desired outputs

  // somehow use mapoutput function
  if (circuit_matches_desired(ex_list[0], desired) == false) {
    errlog("Ckt_Algo::search circuit did not match desired, search continuing");

    // adds NOT/AND/OR gate
    add_not(ex_list[0].getGateCount());
    add_and(ex_list[0].getGateCount());
    add_or(ex_list[0].getGateCount());

    // remove "first" element
    ex_list.erase(ex_list.begin());

    // search the next circuit
    search(desired);

  } else {
    errlog("Ckt_Algo::search found correct circuit!");
    return circ_output;
  }
}
