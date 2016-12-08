//
// Created by ws on 12/8/16.
//

#ifndef LAB4_NEURALNET_H
#define LAB4_NEURALNET_H

#include "WTANeuron.h"

class NeuralNet {
private:
    vector<WTANeuron> neurons;

    size_t inputSize;

public:
    NeuralNet(size_t inputSize) {
        neurons = vector<WTANeuron>();
    }

    WTANeuron& findWinner(vector<double> input) {
        NPoint inputWrapper(input);


        vector<WTANeuron>::iterator n = neurons.begin();

        WTANeuron* winner = &neurons.front();
        int maxValue = winner->f(input);

    }
};

#endif //LAB4_NEURALNET_H
