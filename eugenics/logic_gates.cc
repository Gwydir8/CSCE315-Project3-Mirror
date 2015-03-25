#include <iostream>
#include <string>
#include <sstream>
#include "logic_gates.h"
using namespace std;

// Evaluation function for the And_Gate
// It checks all possible combinations
// Not sure if I should reduce it to just two checks for efficiency.
int And_Gate::And_Evaluate(int input_1, int input_2) {
  if (input_1 == 0 && input_2 == 0) {
    set_output(0);
    return output;
  } else if (input_1 == 0 && input_2 == 1) {
    set_output(0);
    return output;
  } else if (input_1 == 1 && input_2 == 0) {
    set_output(0);
    return output;
  } else if (input_1 == 1 && input_2 == 1) {
    set_output(1);
    return output;
  } else
    cerr << "Invalid Logical Values";
}

// Evaluation function for the Or_Gate
// It checks all possible combinations
// Not sure if I should reduce it to just two checks for efficiency.
int Or_Gate::Or_Evaluate(int input_1, int input_2) {
  if (input_1 == 0 && input_2 == 0) {
    set_output(0);
    return output;
  } else if (input_1 == 0 && input_2 == 1) {
    set_output(1);
    return output;
  } else if (input_1 == 1 && input_2 == 0) {
    set_output(1);
    return output;
  } else if (input_1 == 1 && input_2 == 1) {
    set_output(1);
    return output;
  } else
    cerr << "Invalid Logical Values";
}

// Evaluation function for the Not_Gate
int Not_Gate::Not_Evaluate(int input_1) {
  //if input_1 ? return true : return false;
  if(input_1 == 0){
	set_output(1);
	return output;
  } else if (input_2 == 1){
	set_output(0);
	return output;
  }
  
}

