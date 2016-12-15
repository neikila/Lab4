#include "neuron.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
void Neuron::initWeigth()
{
    w = new double[inputSize];

    for (int i = 0; i < inputSize; i++) {
        w[i] = 0.01 - (rand() % 40) / 1000.0;
    }
}

Neuron::Neuron(int N)
{
    inputSize = N;
    initWeigth();
    nu = 0.00001;
}

double Neuron::compute(double *inputs)
{
    double result = 0;
    for (int i = 0; i < inputSize; i++) {
        result += inputs[i] * w[i];
    }
    return result * 0.02;
}

double Neuron::getW(int index) const
{
    return w[index];
}

void Neuron::setNu(double value)
{
    nu = value;
}

void Neuron::trainOuter(double error, double *inputs)
{
    double sumW = 0.0;
    for (int i = 0; i < inputSize; i++) {
        w[i] -= nu * 0.02 * (error * inputs[i])/* / fabs(error * inputs[i])*/;
        sumW += w[i];
    }
    //std::cout << "sum = " << sumW << std::endl;
}

void Neuron::trainInner(double *errors, double *weights, double *inputs, int outs)
{
    double temp = 0;
    for (int i = 0; i < inputSize; i++) {
        temp = 0;
        for (int j = 0; j < outs; j++) {
            temp += errors[j] * weights[j] * inputs[i];
        }
        w[i] -= nu * (0.02 * temp)/* / fabs(temp * inputs[i])*/;
    }
}
