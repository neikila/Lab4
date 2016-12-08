//
// Created by ws on 12/8/16.
//

#ifndef LAB4_WTANEURON_H
#define LAB4_WTANEURON_H


#include <numeric>
#include "NPoint.h"

class WTANeuron {
private:
    NPoint weights;

public:
    WTANeuron(size_t size) {
        vector<double> weights = vector<double>();
        for (size_t i = 0; i < size; ++i)
            weights.push_back(0);

        this->weights = NPoint(weights);
    }

    double f(NPoint input) {
        vector<double>& result = (weights * input).getCoords();
        return std::accumulate(result.begin(), result.end(), 0.0);
    }
};


#endif //LAB4_WTANEURON_H
