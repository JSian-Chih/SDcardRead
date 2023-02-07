#include "Arduino.h"

#include "DesignFilter.h"


DesignFilter::DesignFilter(int N, double f, double t){
    this->flag = N;
    this->fc1 = f;
    this->fc2 = f;
    this->dT = t;
    this->uoutk = 0.0;
    this->uoutk_1 = 0.0;
    this->uoutk_2 = 0.0;
    this->uink_1 = 0.0;
    this->uink_2 = 0.0;

    switch (N){
    case LPF1st: //1stLPF
        this->B2f = 1.0;
        this->A1f = 1.0/(2.0*PI*fc1);
        this->A2f = 1.0;
        break;
    case HPF1st: //1stHPF
        this->B1f = 1.0/(2.0*PI*fc1);
        this->A1f = 1.0/(2.0*PI*fc1);
        this->A2f = 1.0;
        break;
    case LPF2nd: //2ndLPF
        this->B2f = 4.0*pow(PI,2.0)*fc1*fc2;
        this->A0f = 1.0;
        this->A1f = 2.0*PI*(fc1+fc2);
        this->A2f = this->B2f;
        break;
    case HPF2nd: //2ndHPF
        this->B2f = 1.0;
        this->A0f = 1.0;
        this->A1f = 2*PI*(fc1+fc2);
        this->A2f = 4.0*pow(PI,2.0)*fc1*fc2;
        break;
    case APD: //APD
        this->B1f = 1.0;
        this->A1f = 1.0 / (PI*fc1);
        this->A2f = 1.0;
        break;
    default:
        break;
    }

    this->A0D = this->A0f * 4.0 / pow(this->dT,2.0) + this->A1f * 2.0 / this->dT + this->A2f;
    this->A1D = -2.0 * this->A0f * 4.0 / pow(this->dT,2.0) + 2.0 * this->A2f;
    this->A2D = this->A0f * 4.0 / pow(this->dT,2.0) - this->A1f * 2.0 / this->dT + this->A2f;
    this->B0D = this->B0f * 4.0 / pow(this->dT,2.0) + this->B1f * 2.0 / this->dT + this->B2f;
    this->B1D = -2.0 * this->B0f * 4.0 / pow(this->dT,2.0) + 2.0 * this->B2f;
    this->B2D = this->B0f * 4.0 / pow(this->dT,2.0) - this->B1f * 2.0 / this->dT + this->B2f;

}

DesignFilter::DesignFilter(int N, double f1, double f2, double t){
    this->flag = N;
    this->fc1 = f1;
    this->fc2 = f2;
    this->dT = t;
    this->uoutk = 0.0;
    this->uoutk_1 = 0.0;
    this->uoutk_2 = 0.0;
    this->uink_1 = 0.0;
    this->uink_2 = 0.0;
}

double DesignFilter::output(double uink){

    this->uoutk = 1.0 / this->A0D * (-this->A1D * this->uoutk_1 - this->A2D * this->uoutk_2 + this->B0D * uink + this->B1D * this->uink_1 + this->B2D * this->uink_2);

    this->uink_2 = this->uink_1;
    this->uoutk_2 = this->uoutk_1;
    this->uink_1 = uink;
    this->uoutk_1 = this->uoutk;

    return this->uoutk;
}

