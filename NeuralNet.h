//
// Created by ws on 12/8/16.
//

#ifndef LAB4_NEURALNET_H
#define LAB4_NEURALNET_H

#include <list>
#include <algorithm>
#include "WTANeuron.h"

class NeuralNet {
private:
    vector<WTANeuron> neurons;

    double sMin = 1;
    double sMax = 10;

    int iteration = 0;
    int iterationAmount;

    double nuMin = 0.1;
    double nuMax = 2;
public:
    NeuralNet(size_t inputSize, size_t neuronsAmount) {
        neurons = vector<WTANeuron>();
        for (size_t i = 0; i < neuronsAmount; ++i) {
            neurons.push_back(WTANeuron(inputSize));
        }
    }

    NeuralNet(vector<WTANeuron> neurons) {
        this->neurons = neurons;
    }

    void learn(vector<NPoint> inputs) {
        iterationAmount = inputs.size();
        for (iteration = 0; iteration < inputs.size(); ++iteration) {
            learn(inputs[iteration]);
            cout << "Iteration num = " << iteration << endl << *this << endl;
        }
    }

    void learn(NPoint input) {
        vector<WTANeuron> sortedNeurons = sorted(input);
        for (size_t i = 0; i < sortedNeurons.size(); ++i) {
            sortedNeurons[i].adjust(nu(), gNeighbor(i), input);
        }
        neurons = sortedNeurons;
    }

    WTANeuron &findWinner(vector<double> input) {
        return findWinner(NPoint(input));
    }

    WTANeuron &findWinner(NPoint input) {
        vector<WTANeuron>::iterator n = neurons.begin();

        WTANeuron *winner = &neurons.front();
        double maxValue = winner->f(input);

        for (++n; n != neurons.end(); ++n) {
            double temp = n->f(input);
            if (temp > maxValue) {
                maxValue = temp;
                winner = &(*n);
            }
        }
        return *winner;
    }

    vector<WTANeuron> sorted(NPoint& input) {
        vector<WTANeuron> neurons(this->neurons);
        std::sort(neurons.begin(), neurons.end(),
                  [&input]( const WTANeuron &a, const WTANeuron &b ) { return a.delta(input) <= b.delta(input); });
        return neurons;
    }

    double nu() {
        return nuMax * pow(nuMin / nuMax, ((double)iteration) / iterationAmount);
    }

    double sk() {
        return sMax * pow(sMin / sMax, ((double)iteration) / iterationAmount);
    }

    double gNeighbor(size_t position) {
        return exp(-1.0 * position / sk());
    }

    friend ostream& operator<<(ostream& os, const NeuralNet& p);
};

ostream &operator<<(ostream &os, const NeuralNet &p) {
    vector<WTANeuron>::const_iterator it = p.neurons.begin();
    os << "NeuralNet: " << endl;
    for(; it != p.neurons.end(); ++it)
        os << *it << endl;
    return os;
}

#endif //LAB4_NEURALNET_H
