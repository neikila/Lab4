#include "network.h"
#include <cstdlib>
#include <iostream>

void Network::init()
{
    hidden.clear();
    output.clear();
    for (int i = 0; i < hiddenSize; i++) {
        Neuron n(inputsSize);
        hidden.push_back(n);
    }
    for (int i = 0; i < outputSize; i++) {
        Neuron n(hiddenSize);
        output.push_back(n);
    }
}

Network::Network(int inN, int hiddenN) :
    inputsSize(inN),
    hiddenSize(hiddenN),
    outputSize(inN)
{
    init();
}

std::vector<double> Network::compute(std::vector<double> inputs)
{
    std::vector<double> temp;
    std::vector<double> result;
    double t;

    temp.clear();
    result.clear();

    for (int i = 0; i < hiddenSize; i++) {
        temp.push_back(hidden.at(i).compute(inputs.data()));
    }
    for (int i = 0; i < outputSize; i++) {
        t = output.at(i).compute(temp.data());
        result.push_back(t);
    }
    return result;
}

std::vector<uchar> Network::compute(std::vector<uchar> inputs)
{
    std::vector<double> convert;
    std::vector<double> temp;
    std::vector<unsigned char> result;
    double t;

    temp.clear();
    result.clear();

    for (int i = 0; i < inputs.size(); i++) {
        convert.push_back((double)(inputs.at(i)));
    }

    for (int i = 0; i < hiddenSize; i++) {
        result.push_back(hidden.at(i).compute(convert.data()));
    }
    for (int i = 0; i < outputSize; i++) {
        t = output.at(i).compute(temp.data());
        result.push_back((unsigned char)t);
    }
    return result;
}

void Network::trainStep(std::vector<double> inputs)
{
    std::vector< double > results = compute(inputs);
    std::vector< double > errors;
    std::vector< double > temp;
    std::vector< std::vector< double > > weigths;

    weigths.resize(hiddenSize);
    for (int i = 0; i < inputsSize; i++) {
        errors.push_back(results[i] - inputs[i]);

        for (int j = 0; j < hiddenSize; j++) {
            weigths.at(j).push_back(output[i].getW(j));
        }
    }

    temp.clear();

    for (int i = 0; i < hiddenSize; i++) {
        temp.push_back(hidden.at(i).compute(inputs.data()));
    }

    for (int i = 0; i < hiddenSize; i++) {
	
        hidden[i].trainInner(errors.data(),
                             weigths.at(i).data(),
                             inputs.data(),
                             inputsSize);
        //std::cout << "weight[" << i << "] = " << weigths.at(i).at(i) << "\n";
    } //???
    double sumW = 0.0;
    for (int i = 0; i < inputsSize; i++) {
        output[i].trainOuter(errors[i], temp.data());
        for (int j = 0; j < hiddenSize; ++j) {
            sumW += output[i].getW(j);
        }
        //std::cout << "out[" << i << "] " << output[i].getW(i) << std::endl;
    }
    std::cout << sumW << std::endl;

    // } //???
}

void Network::trainStep(std::vector<unsigned char> inputs)
{
    std::vector<double> nInput;
    for (std::vector<unsigned char>::iterator t = inputs.begin(); t != inputs.end(); t++) {
        nInput.push_back((double)(*t));
    }
    trainStep(nInput);
}
