#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Logic_Gates {
 protected:
  int input_1, input_2;
  int output;

 public:
  // This first constructor used for the NOT Gate. Takes in one input to
  // evaluate.
  Logic_Gates(const int& input_1) : input_1(input_1);

  // This second constructor used for And and Or Gates. Takes in two inputs to
  // evaluate.
  Logic_Gates(const int& input_1, const int& input_2)
      : input_1(input_1), input_2(input_2);

  // Simple Get and Set functions. Don't know if we really need it at the
  // moment.
  // But it is nice to have them made just in case.
  int get_input_1() const { return input_1; }
  int get_input_2() const { return input_2; }
  int get_output() const { return output; }
  void set_input_1(int x) { input_1 = x; }
  void set_input_2(int x) { input_2 = x; }
  void set_output(int x) { output = x; }
};

// And Gate: Takes in two inputs. True if both are true. False if this is not
// the case.
class And_Gate : public Logic_Gates {
 protected:
  int output;

 public:
  And_Gate(int x, int y) : Logic_Gates(input_1, input_2) {}
  int And_Evaluate(int input_1, int input_2);
  void set_output(int x) { output = x; }
};

// Or Gate: Takes in two inputs. True if either or both are true. False if this
// is not the case.
class Or_Gate : public Logic_Gates {
 protected:
  int output;

 public:
  Or_Gate(int x, int y) : Logic_Gates(input_1, input_2) {}
  int Or_Evaluate(int input_1, int input_2);
  void set_output(int x) { output = x; }
};

// Not Gate: Takes in one input. Opposite of whatever input is given.
class Not_Gate : public Logic_Gates {
 protected:
  int output;

 public:
  Not_Gate(int x) : Logic_Gates(input_1) {}
  int Not_Evaluate(int input_1);
  void set_input_2() { input_2 = -1; }
  void set_output(int x) { output = x; }
};

#endif
