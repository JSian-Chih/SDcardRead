# Gimbal_Thrust_Control_Sample

* 我懷疑 加了Kd會震是noise的問題
* S1_output & S2_output 是Servo 打出去的角度

## DesignFilter_class.h

This header define:
1. first order LPF
2. first order HPF
3. second order LPF
4. second order HPF
5. APD

## CPFilter.h

This header define the fifth order command prefilter.