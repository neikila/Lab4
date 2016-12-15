#include <iostream>
#include <algorithm>
#include <sstream>
#include "WTANeuron.h"
#include "NeuralNet.h"
#include "AllData.h"
#include "Gnuplot.h"

using namespace std;

basic_string createOutName(int nv, int nh, int neuronsAmount, char* filename) {
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

int lab(char* filename) {
    PngImage img;
    int Nv[3];
    int Nh[3];

    Nv[0] = 2;  Nv[1] = 4;  Nv[2] = 8;
    Nh[0] = 2;  Nh[1] = 4;  Nh[2] = 8;

    if (!img.readImage(filename))
        return 1;

    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});

    Gnuplot gnuplot;
    gnuplot.init(filename);

    for (int k = 0; k < 1; k++) {
        cout << "Nv = " << Nv[k] << "; ";
        cout << "Nh = " << Nh[k] << "; ";

        int inputsAmount = Nv[k] * Nh[k];

        int blocksAmount = img.getBlockCount(Nv[k], Nh[k]);
        cout << blocksAmount << endl;

        vector<NPoint> input;
        for (int i = 0; i < blocksAmount; ++i) {
            input.push_back(NPoint(img.getBlock(i, Nv[k], Nh[k])));
        }

        for (int j = 0; j < 10; j++) {
            net.learn(input);
        }

        AllData allData(inputsAmount);
        allData.saveImage(net, input);

        auto results = allData.getImageData(net);
        for (int i = 0; i < results.size(); ++i) {
            img.setBlock(results[i].toUchars(), i, Nv[k], Nh[k]);
        }

        basic_string out_name = createOutName(Nv[k], Nh[k], (int)net.getNeurons().size(), filename);
        img.writeImage(out_name.c_str());
        gnuplot.finish(Nv[k], Nh[k], out_name);

        cerr << "Done..." << endl;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Input/output images not specified" << endl;
        return 0;
    }
    lab(argv[1]);
    return 0;
}