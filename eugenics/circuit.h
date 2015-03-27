#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>
#include "gate.h"
enum GateType { NOT, WIRE, OR, AND };
class Circuit {
    private:
        int output_no;
        std::vector<Gate*> gates;
    public:
        /* Circuit(int num_of_inputs); */
        Circuit(std::vector<bool> inputs);
        void addGate(GateType gate_type, int index_1);
        void addGate(GateType gate_type, int index_1, int index_2);
        std::vector<bool> evaluate();
        /* std::vector<std::vector<bool> > evaluate(); */
};


#endif
