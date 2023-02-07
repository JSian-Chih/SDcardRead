#include "Arduino.h"

#include "PIDcontrol.h"

PIDcontrol::PIDcontrol(int pid_type, double *gain, double T){
    this->KP = gain[0];
    this->KI = gain[1];
    this->KD = gain[2];
    this->dt = T;

    switch (pid_type)
    {
    case BACKWARD:
        this->alpha_1 = 1.0;
        this->alpha_2 = 0.0;
        this->beta_0 = (this->KD + this->KP * this->dt + this->KI * this->dt * this->dt) / this->dt;
        this->beta_1 = (-2.0 * this->KD - this->KP * this->dt) / this->dt;
        this->beta_2 = this->KD / this->dt;
        break;
    case BILINEAR:
        this->alpha_1 = 0.0;
        this->alpha_2 = 1.0;
        this->beta_0 = (2.0 * this->KD + this->KP * this->dt + 0.5 * this->KI * this->dt * this->dt) / this->dt;
        this->beta_1 = (-4.0 * this->KD + this->KI * this->dt * this->dt) / this->dt;
        this->beta_2 = (2.0 * this->KD - this->KP * this->dt + 0.5 * this->KI * this->dt * this->dt) / this->dt;
        break;
    }
}

PIDcontrol::PIDcontrol(int pid_type, double *gain, double T, double fc){
    this->KP = gain[0];
    this->KI = gain[1];
    this->KD = gain[2];
    this->dt = T;
    this->tau_lowpass =  1.0*pow(2.0*PI*fc,-1.0);

    switch (pid_type){
    case BACKWARD:
        this->alpha_1 = 1.0;
        this->alpha_2 = 0.0;
        this->beta_0 = (this->KD + this->KP * this->dt + this->KI * this->dt * this->dt) / this->dt;
        this->beta_1 = (-2.0 * this->KD - this->KP * this->dt) / this->dt;
        this->beta_2 = this->KD / this->dt;
        break;
    case BILINEAR:
        this->alpha_1 = 0.0;
        this->alpha_2 = 1.0;
        this->beta_0 = (2.0 * this->KD + this->KP * this->dt + 0.5 * this->KI * this->dt * this->dt) / this->dt;
        this->beta_1 = (-4.0 * this->KD + this->KI * this->dt * this->dt) / this->dt;
        this->beta_2 = (2.0 * this->KD - this->KP * this->dt + 0.5 * this->KI * this->dt * this->dt) / this->dt;
        break;
    case BilinearLowpass:
        this->alpha_1 = (8.0 * this->tau_lowpass) / (4.0 * this->tau_lowpass + 2.0 * dt);
        this->alpha_2 = (-4.0 * this->tau_lowpass + 2.0 * dt) / (4.0 * this->tau_lowpass + 2.0 * dt);
        this->beta_0 = (4.0 * this->KD + 2.0 * this->KP * this->dt + this->KI * this->dt * this->dt) / (4.0 * this->tau_lowpass + 2.0 * this->dt);
        this->beta_1 = (-8.0 * this->KD + 2.0 * this->KI * this->dt * this->dt) / (4.0 * this->tau_lowpass + 2.0 * this->dt);
        this->beta_2 = (4.0 * this->KD - 2.0 * this->KP * this->dt + this->KI * this->dt * this->dt) / (4.0 * this->tau_lowpass + 2.0 * this->dt);
        break;
    }
}

double PIDcontrol::PIDupdate(double x_d, double x){
    this->e = x_d - x;
    this->u = this->alpha_1 * this->u_pre + this->alpha_2 * this->u_pre2 + this->beta_0 * this->e + this->beta_1 * this->e_pre + this->beta_2 * this->e_pre2;

    this->e_pre2 = this->e_pre;
    this->e_pre = this->e;
    this->u_pre2 = this->u_pre;
    this->u_pre = this->u;
    return this->u;
}