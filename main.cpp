#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "WTANeuron.h"
#include "NeuralNet.h"
#include "Zipped.h"
#include "AllData.h"
#include "pngimage.h"

using namespace std;

void test() {
    WTANeuron neuron(3);
    vector<double> input({10, 12, 13});
    cout << neuron.f(input) << endl;
}

void test2() {
    vector<double> v = {3.0, 4.0};
    NPoint p(v);
    cout << p.normalize() << endl;
}

void test3() {
    AllData allData(3);

    NPoint data({1, 3, 4, 5, 6, 7});

    auto frames = allData.convertImageToFrames(data.getCoords(), 3);
    cout << "Size = " << frames.size() << endl;
    cout << frames[0] << endl;
    cout << frames[1] << endl;

    cout << "Image: " << endl << NPoint(allData.convertFramesToImage(frames)) << endl;
}

void test4() {
    NeuralNet net({WTANeuron({1, 2, 3}), WTANeuron({-1, -2, -3})});

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
}

void test5() {
    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
    cout << "Net to save " << net << endl;

    AllData allData(3);
    allData.saveNet(net);

    cout << "Restored net: " << allData.createNet() << endl;
}

void test6() {
    NeuralNet net({WTANeuron({1, 1, 1}), WTANeuron({-1, 1, 1}), WTANeuron({1, -1, -1})});
    cout << "Net to save " << net << endl;

    AllData allData(3);
    allData.saveNet(net);

    cout << "Restored net: " << allData.createNet() << endl;
}

void test7() {
    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
    vector<double> imageData = {2, 0, 0,
                                0, 3, 0,
                                0, 0, 5};
    AllData allData(3);

    cout << "Compressed:\n" << allData.saveImage(net, imageData).getImage() << endl;
}

void test8() {
    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
    vector<double> imageData = {2, 0, 0,
                                0, 3, 0,
                                0, 0, 5,
                                0, 9, 0,
                                7, 0, 0,
                                0, 0, 2};
    AllData allData(3);
    cout << "Restored:\n" << NPoint(allData.saveImage(net, imageData).getImageData()) << endl;
}

void test9() {
    vector<NPoint> learning = {
            NPoint(vector<double>({5, 0, 0})),
            NPoint(vector<double>({0, 8, 0})),
            NPoint(vector<double>({0, 0, 4})),
            NPoint(vector<double>({100, 0, 0})),
            NPoint(vector<double>({0, 13, 0})),
            NPoint(vector<double>({0, 0, 16})),
            NPoint(vector<double>({10, 0, 0})),
            NPoint(vector<double>({0, 22, 0})),
            NPoint(vector<double>({0, 0, 33})),
            NPoint(vector<double>({55, 0, 0})),
            NPoint(vector<double>({0, 60, 0})),
            NPoint(vector<double>({0, 0, 70})),
            NPoint(vector<double>({80, 0, 0})),
            NPoint(vector<double>({0, 90, 0})),
            NPoint(vector<double>({0, 0, 100})),
            NPoint(vector<double>({89, 0, 0})),
            NPoint(vector<double>({0, 91, 0})),
            NPoint(vector<double>({0, 0, 14})),
            NPoint(vector<double>({19, 0, 0})),
            NPoint(vector<double>({0, 20, 0})),
            NPoint(vector<double>({0, 0, 44})),
    };
    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
    net.learn(learning);

    cout << net << endl;
}

void test10() {
    vector<NPoint> learning = {
            NPoint(vector<double>({5, 0, 0})),
            NPoint(vector<double>({0, 8, 0})),
            NPoint(vector<double>({0, 0, 4})),
            NPoint(vector<double>({100, 0, 0})),
            NPoint(vector<double>({0, 13, 0})),
            NPoint(vector<double>({0, 0, 16})),
            NPoint(vector<double>({10, 0, 0})),
            NPoint(vector<double>({0, 22, 0})),
            NPoint(vector<double>({0, 0, 33})),
            NPoint(vector<double>({55, 0, 0})),
            NPoint(vector<double>({0, 60, 0})),
            NPoint(vector<double>({0, 0, 70})),
            NPoint(vector<double>({80, 0, 0})),
            NPoint(vector<double>({0, 90, 0})),
            NPoint(vector<double>({0, 0, 100})),
            NPoint(vector<double>({89, 0, 0})),
            NPoint(vector<double>({0, 91, 0})),
            NPoint(vector<double>({0, 0, 14})),
            NPoint(vector<double>({19, 0, 0})),
            NPoint(vector<double>({0, 20, 0})),
            NPoint(vector<double>({0, 0, 44})),
    };
    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
    net.learn(learning);

    vector<double> imageData = {2, 0, 0,
                                0, 3, 0,
                                0, 0, 5,
                                0, 9, 0,
                                7, 0, 0,
                                0, 0, 2};
    AllData allData(3);
    cout << "Restored:\n" << NPoint(allData.saveImage(net, imageData).getImageData()) << endl;
}

int lab(int argc, char* argv[]) {
    PngImage img;
    int Nv[3];
    int Nh[3];

    Nv[0] = 2;  Nv[1] = 4;  Nv[2] = 8;
    Nh[0] = 2;  Nh[1] = 4;  Nh[2] = 8;

    if (argc != 2) {
        cerr << "Input/output images not specified" << endl;
        return 0;
    }

    NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});

    if (!img.readImage(argv[1])) return 1;

    ofstream plot;
    plot.open("plot.plt", ofstream::out | ofstream::trunc);

    plot << "set multiplot layout 2,2 rowsfirst" << endl;
    plot << "unset key; unset tics; unset border" << endl;
    plot << "set size ratio 1" << endl;

    plot << "set title \"Source image\"" << endl;
    plot << "plot \"" << argv[1] << "\" binary filetype=png with rgbimage" << endl;


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
//        for (int i = 0; i < blocks; i++) {
//            block = img.getBlock(i, Nv[k], Nh[k]);
//            out = net->compute(block);
//            img.setBlock(out, i, Nv[k], Nh[k]);
//        }

        auto results = allData.getImageData(net);
        for (int i = 0; i < results.size(); ++i) {
            img.setBlock(results[i].toUchars(), i, Nv[k], Nh[k]);
        }

        string name_base;
        name_base.append(argv[1]);
        name_base = name_base.substr(0, name_base.find_first_of('.'));

        ostringstream s;
        s.str("");
        s << name_base << "_" << Nh[k] << "_" << Nv[k] << ".png";

        string out_name;
        out_name.clear();
        out_name.assign(s.str());
        img.writeImage(out_name.c_str());

        plot << "set title \"Image Nv = " << Nv[k]
             << ", Nh = "<< Nh[k]
             << "\"" << endl;
        plot << "plot \"" << out_name
             << "\" binary filetype=png with rgbimage\n" << endl;

        cerr << "Done..." << endl;
    }

//    plot << "unset multiplot" << endl;

    plot.close();

    return 0;
}

int main() {
    test10();
    return 0;
}