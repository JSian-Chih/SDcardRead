#ifndef CommandPreFilter
#define CommandPreFilter

class CPFilter{
    private:
        double fc;
        double dT;
        double tau;
        double tau5;
        double tau4;
        double tau3;
        double tau2;
        double tau1;
        double x0d_d_y, x0d_d_k, x0d_d_last;
        double x1d_d_y, x1d_d_k, x1d_d_last;
        double x2d_d_y, x2d_d_k, x2d_d_last;
        double x3d_d_y, x3d_d_k, x3d_d_last;
        double x4d_d_y, x4d_d_k, x4d_d_last; 

    public:
        CPFilter(double f, double t);
        void output(double uink);
        double dx_out(int flag);
};

#endif

