#ifndef VOLTAGRAMA_H
#define VOLTAGRAMA_H

#include <QVector>
#include <QString>

class Voltagrama
{
public:

    struct Voltamm
    {
        // data
            QVector<double> xVoltaje;
            QVector<double> yAmplitudeP;
            QVector<double> yAmplitudeN;

            QVector<double> yAmplitudeD; // Diference of amplitudes, full differential.

            int Npoints; //Number of samples
         // amplitude parameters
            int vdiff;      // step height mV
            int vmmm;       // step height mV
            int voffset;    // IV offset mV
            int vminp;      // V initial mV
            int vmaxp;      // V final   mV
            int vclean;     // v clean   mV
            int vrest;      // V rest    mV

         // time parameters
            int t_InitToSample;  // mseg
            int t_SampleToEnd;  // mseg
            int t_ElectroDep;   // seg
            int t_WaitToStart;  // mseg
            int t_clean;        // seg
            int Ncycles;        // cyclic voltammetry

         // technique and mode of pulse

            int technique; // cyclicVoltammetry, normalVoltammetry, strippingVoltammetry []
            int  mode; // SquareWave, Pulse, Staircase []

            int gain;
    };

    Voltagrama(const Voltamm& voltamp);

    void SetfileTosave();
    void addPlotVoltagrama();
    Voltamm currentvoltamp;

};

#endif // VOLTAGRAMA_H
