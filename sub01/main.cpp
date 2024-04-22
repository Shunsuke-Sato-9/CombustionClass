#include<iostream>
#include<vector>

using namespace std;

#define spmax 5

//初期のモル分率を計算する関数
void cal_X0(vector<double> &x0, double phi){
    double A = 1 / (phi + (19/2) + (19/2)*(79/21)) ;
    double sum = 0.0;

    x0[0] =  A*phi; 
    x0[1] = (19/2) * A;
    x0[2] = 0;
    x0[3] = 0;
    sum = x0[0] + x0[1] + x0[2] + x0[3];
    x0[4] = 1- sum;
}

//定積変化の関数

//定変化の関数

int main(int argc, char* argv[]){           //argc 引数の数、argv,引数の配列をchar型のポインタを受け取っている
//初期条件
    double T_initial = 300; //初期温度
    double P_initial  ;    //初期圧力
    double phi;             //当量比
    const double R =8.31;   //一般気体定数

    vector<double> X0(spmax, 0.0);
    phi = atof(argv[1]); 
    
    cout << "Equiavalent raito is " << phi << endl;     //当量比の出力
    cal_X0(X0, phi);
    /*for (double i: X0) {
        cout << i << endl;
    }*/
    return 0;
}

const double nasaCp[spmax][12] = {     /*  C6H14 (low) /   1.836174 ,  5.10E-02 ,  1.26E-05 , -4.43E-08 ,  1.87E-11 ,  -2.29E+04,     /  C6H14 (high) / 22.804718 ,  2.10E-02 , -3.53E-06 , -5.47E-10 ,  1.48E-13 ,  -3.07E+04,     /  02  (low) /     3.78E+00 , -3.00E-03 ,  9.85E-06 , -9.68E-09 ,  3.24E-12 ,  -1.06E+03,     /  02  (high) /    3.66E+00 ,  6.56E-04 , -1.41E-07 ,  2.06E-11 , -1.30E-15 ,  -1.22E+03,     /  CO2  (low) /    2.36E+00 ,  8.98E-03 , -7.12E-06 ,  2.46E-09 , -1.43E-13 ,  -4.84E+04,     /  CO2  (high) /   4.64E+00 ,  2.74E-03 , -9.96E-07 ,  1.60E-10 , -9.16E-15 ,  -4.90E+04,     /  H2O  (low) /    4.20E+00 , -2.04E-03 ,  6.52E-06 , -5.49E-09 ,  1.77E-12 ,  -3.03E+04,     /  H2O  (high) /   2.68E+00 ,  2.97E-03 , -7.74E-07 ,  9.44E-11 , -4.27E-15 ,  -2.99E+04,     /  N2  (low) /     3.53E+00 , -1.24E-04 , -5.03E-07 ,  2.44E-09 , -1.41E-12 ,  -1.05E+03,     /  N2  (high) */    2.95E+00 ,  1.40E-03 , -4.93E-07 ,  7.86E-11 , -4.61E-15 ,  -9.24E+02  };