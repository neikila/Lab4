#ifndef NEURON_H
#define NEURON_H

class Neuron
{
    int     inputSize;
    double *w;
    double  nu;

    void initWeigth();
public:
    Neuron(int N = 2);

    double  compute(double *inputs);
    double  getW(int index) const;
    void    setNu(double value);
    void    norm(double* inputs);

    void    trainOuter(double error, double *inputs);
    void    trainInner(double *errors,
                       double *weights,
                       double *inputs, int outs);
};

#endif // NEURON_H
