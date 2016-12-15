#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "neuron.h"

typedef unsigned char uchar;

class Network
{
    int inputsSize;
    int hiddenSize;
    int outputSize;

    std::vector< Neuron > hidden;
    std::vector< Neuron > output;

    void init();
public:
    Network(int inN, int hiddenN);

    std::vector<double> compute(std::vector<double> inputs);
    std::vector<uchar>  compute(std::vector<uchar> inputs);
    void   backProp(std::vector<std::vector<double> > inputs);
    void   trainStep(std::vector<double> inputs);
    void   trainStep(std::vector<unsigned char> inputs);
};

#endif // NETWORK_H
