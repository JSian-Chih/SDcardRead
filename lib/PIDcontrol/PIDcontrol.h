#ifndef PID_GimbalController
#define PID_GimbalController

class PIDcontrol{
    private:
        double alpha_1, alpha_2;
        double beta_0, beta_1, beta_2;
        double KP, KI, KD;
        double dt;
        double u = 0;
        double u_pre, u_pre2;
        double e, e_pre, e_pre2;
        double tau_lowpass;
    
    public:
    PIDcontrol(int pid_type, double *gain, double T);
    PIDcontrol(int pid_type, double *gain, double T, double fc);
    double PIDupdate(double x_d, double x);
};

enum PID_TYPE{
    BACKWARD,
    BILINEAR,
    BilinearLowpass
};




#endif