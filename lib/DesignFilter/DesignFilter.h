#ifndef DesignFilter_class_1
#define DesignFilter_class_1

class DesignFilter{
    private:
        double fc1;
        double fc2;
        double dT;
        int flag;
        /*
        1:1LPF
        2:1HPF
        3:2LPF
        4:2HPF
        5:APD
        */
        double A0f = 0.0;
        double A1f = 0.0;
        double A2f = 0.0;
        double B0f = 0.0;
        double B1f = 0.0;
        double B2f = 0.0;
        double A0D = 0.0;
        double A1D = 0.0;
        double A2D = 0.0;
        double B0D = 0.0;
        double B1D = 0.0;
        double B2D = 0.0;
    
    public:
        double uoutk;
        double uoutk_1;
        double uoutk_2;
        double uink_1;
        double uink_2;

        DesignFilter(int N, double f, double t);
        DesignFilter(int N, double f1, double f2, double t);
        double output(double uink);
};

enum Filter_TYPE{
    LPF1st,
    HPF1st,
    LPF2nd,
    HPF2nd,
    APD
};



#endif