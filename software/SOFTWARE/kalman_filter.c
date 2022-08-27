#include "kalman_filter.h"
#include "usart.h"

float K = 0;            // 卡尔曼增益
float x_est = 0;        // 先验估计
float u = 0;            // 控制量
//float d_t = 0.01;       // 采样时间
float P_est = 0;        // 先验估计协方差
float P = 1;            // 后验估计协方差
float Q = 0.01;         // 过程噪声协方差
float R = 0.1;          // 测量噪声协方差
float x = 3.7;          // 后验估计


float KF_Filter(float z)
{
    x_est = x;
    P_est = P + Q;
    K = P_est / (P_est + R);
    x = x_est + K * (z - x_est);
    P = (1 - K) * P_est;
    
    return x;
}

