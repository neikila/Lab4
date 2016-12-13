#include <iostream>
#include <algorithm>
#include "WTANeuron.h"
#include "NeuralNet.h"

using namespace std;

void test() {
    WTANeuron neuron(3);
    vector<double> input({10, 12, 13});
    cout << neuron.f(input) << endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    NeuralNet net({WTANeuron({1, 2, 3}), WTANeuron({-1, -2, -3})});

    cout << net.findWinner(vector<double>{1, 1, 1}) << endl;
    cout << net.findWinner(vector<double>{-1, -1, -1}) << endl;

    vector<NPoint> learning = {
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1})),
            NPoint(vector<double>({-1, -1, -1})),
            NPoint(vector<double>({1, 1, 1}))
    };

    net.learn(learning);

    cout << net << endl;

    return 0;
}