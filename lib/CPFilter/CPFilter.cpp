#include "Arduino.h"

#include "CPFilter.h"

CPFilter::CPFilter(double f, double t){
    this -> fc = f;
    this -> dT = t;
    this -> tau = 1.0*pow(2.0*PI*fc,-1.0);
    this -> tau5 = pow(tau,-5.0);
    this -> tau4 = pow(tau,-4.0);
    this -> tau3 = pow(tau,-3.0);
    this -> tau2 = pow(tau,-2.0);
    this -> tau1 = pow(tau,-1.0);
}

void CPFilter::output(double uink){

    x0d_d_last = x1d_d_k*dT +x0d_d_k;
    x1d_d_last = x2d_d_k*dT +x1d_d_k;
    x2d_d_last = x3d_d_k*dT +x2d_d_k;
    x3d_d_last = x4d_d_k*dT +x3d_d_k;
    x4d_d_last = (-1.0*tau5*x0d_d_k -5.0*tau4*x1d_d_k -10.0*tau3*x2d_d_k -10.0*tau2*x3d_d_k -5.0*tau1*x4d_d_k +uink)*dT +x4d_d_k;

    x0d_d_y = 1.0*tau5*x0d_d_k;
    x1d_d_y = 1.0*tau5*x1d_d_k;
    x2d_d_y = 1.0*tau5*x2d_d_k;
    x3d_d_y = 1.0*tau5*x3d_d_k;
    x4d_d_y = 1.0*tau5*x4d_d_k;

    x0d_d_k = x0d_d_last;
    x1d_d_k = x1d_d_last;
    x2d_d_k = x2d_d_last;
    x3d_d_k = x3d_d_last;
    x4d_d_k = x4d_d_last;

}

double CPFilter::dx_out(int flag){
    double out = 0.0;
    switch (flag) {
    case 0:
        out = x0d_d_y;
        break;
    case 1:
        out = x1d_d_y;
        break;
    case 2:
        out = x2d_d_y;
        break;
    case 3:
        out = x3d_d_y;
        break;
    case 4:
        out = x4d_d_y;
        break;
    default:
        break;
    }
    return out;
}

