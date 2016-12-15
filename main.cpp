#include <iostream>
#include <algorithm>
#include <sstream>
#include "WTANeuron.h"
#include "NeuralNet.h"
#include "AllData.h"
#include "Gnuplot.h"
#include "Test.h"

using namespace std;

string createOutName(int nv, int nh, int neuronsAmount, char* filename) {
    string name_base;
    name_base.append(filename);
    name_base = name_base.substr(0, name_base.find_first_of('.'));

    ostringstream s;
    s.str("");
    s << name_base << "_" << nh << "_" << nv << "_" << neuronsAmount << ".png";

    string out_name;
    out_name.clear();
    out_name.assign(s.str());
    return out_name;
}

void executeWith(int nv, int nh, int neuronsAmount, PngImage& img, Gnuplot& gnuplot, char* filename) {
    cout << "Nv = " << nv << "; ";
    cout << "Nh = " << nh << "; ";

    int inputsAmount = nv * nh;
    NeuralNet net({WTANeuron({1, 0, 0, 0}), WTANeuron({0, 1, 0, 0}), WTANeuron({0, 0, 1, 0}), WTANeuron({0, 0, 0, 1})});

    if (net.getNeurons()[0].getWeights().getCoords().size() != inputsAmount) {
        cerr << "Wrong params!";
        return;
    }

    int blocksAmount = img.getBlockCount(nv, nh);
    cout << blocksAmount << endl;

    vector<NPoint> input;
    for (int i = 0; i < blocksAmount; ++i)
        input.push_back(NPoint(img.getBlock(i, nv, nh)));

    int evolutionsAmount = 10;
    for (int j = 0; j < evolutionsAmount; j++)
        net.learn(input);

    AllData allData(inputsAmount);
    allData.saveImage(net, input);
    auto results = allData.getImageData(net);

    for (int i = 0; i < results.size(); ++i)
        img.setBlock(results[i].toUchars(), i, nv, nh);

    string out_name = createOutName(nv, nh, (int)net.getNeurons().size(), filename);
    img.writeImage(out_name.c_str());
    gnuplot.finish(nv, nh, out_name);
}

int lab(char* filename) {
    PngImage img;
    int Nv[3];
    int Nh[3];
    int NeuronsAmount[3];

    Nv[0] = 2;  Nv[1] = 4;  Nv[2] = 8;
    Nh[0] = 2;  Nh[1] = 4;  Nh[2] = 8;
    NeuronsAmount[0] = 2;  NeuronsAmount[1] = 4;  NeuronsAmount[2] = 8;

    if (!img.readImage(filename))
        return 1;

    Gnuplot gnuplot;
    gnuplot.init(filename);

    for (int k = 0; k < 1; k++) {
        executeWith(Nv[k], Nh[k], NeuronsAmount[k], img, gnuplot, filename);
        cerr << "Done..." << endl;
    }
    return 0;
}

int main(int argc, char **argv) {
    lab((char *) "test1.png");

    return 0;
}