// Запуск g++ -o pngexam main.cpp network.cpp neuron.cpp -lpng -lz -lm


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "network.h"
#include "../pngimage.h"

using namespace std;

int main(int argc, char **argv)
{
    PngImage img;
    string name_base;
    string out_name;
    int Nv[3];
    int Nh[3];
    int L[3];

    Nv[0] = 2;  Nv[1] = 4;  Nv[2] = 8;
    Nh[0] = 2;  Nh[1] = 4;  Nh[2] = 8;
    L[0]  = 2;  L[1]  = 2;  L[2]  = 6;

    if (argc != 2) {
        cerr << "Input/output images not specified" << endl;
        return 0;
    }

    Network *net;
    vector<uchar> block;
    vector<uchar> out;
    ofstream plot;
    ostringstream s;


    int blocks;
    if (!img.readImage(argv[1])) return 1;
    name_base.append(argv[1]);
    name_base = name_base.substr(0, name_base.find_first_of('.'));

    plot.open("plot.plt", ofstream::out | ofstream::trunc);

    plot << "set multiplot layout 2,2 rowsfirst" << endl;
    plot << "unset key; unset tics; unset border" << endl;
    plot << "set size ratio 1" << endl;

    plot << "set title \"Source image\"" << endl;
    plot << "plot \"" << argv[1] << "\" binary filetype=png with rgbimage" << endl;

    for (int k = 0; k < 1; k++) {
        cout << "Nv = " << Nv[k] << "; ";
        cout << "Nh = " << Nh[k] << "; ";
        cout << "L = " << L[k] << endl;
        net = new Network(Nv[k] * Nh[k], L[k]);

        blocks = img.getBlockCount(Nv[k], Nh[k]);
        cout << blocks << endl;

        for (int j = 0; j < 10; j++) {
            block = img.getBlock(0, Nv[k], Nh[k]);
            for (int i = 1; !block.empty(); i++) {
                net->trainStep(block);
                block = img.getBlock(i, Nv[k], Nh[k]);
            }
        }
        for (int i = 0; i < blocks; i++) {
            block = img.getBlock(i, Nv[k], Nh[k]);
            out = net->compute(block);
            img.setBlock(out, i, Nv[k], Nh[k]);
        }
        s.str("");
        s << name_base << "_" << Nh[k] << "_" << Nv[k] << "_" << L[k] << ".png";
        out_name.clear();
        out_name.assign(s.str());
        img.writeImage(out_name.c_str());

        plot << "set title \"Image Nv = " << Nv[k]
             << ", Nh = "<< Nh[k]
             << ", L = " << L[k] << "\"" << endl;
        plot << "plot \"" << out_name
             << "\" binary filetype=png with rgbimage\n" << endl;

        delete net;

        cerr << "Done..." << endl;
    }

//    plot << "unset multiplot" << endl;

    plot.close();

    return 0;
}
