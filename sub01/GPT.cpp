#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void enthalpy(double T, double R, double& h_bar, double a, double b, double c, double d, double e, double f) {
    h_bar = a * T * R + b * pow(T, 2) * R / 2 + c * pow(T, 3) * R / 3 + d * pow(T, 4) * R / 4 + e * pow(T, 5) * R / 5 + f * R;
}

void h_after_lean(double fai, double* h, double& h_aft) {
    h_aft = 2 * fai * h[3] + 3 * fai * h[4] + 3.5 * 79.0 / 21.0 * h[2] + 3.5 * (1 - fai) * h[1];
}

void h_after_rich(double fai, double* h, double& h_aft) {
    h_aft = 2 * h[3] + 3 * h[4] + 3.5 * 79.0 / 21.0 * h[2] + (fai - 1) * h[0];
}

void total_enthalpy_lean(double T, double R, double& h_aft, double* a, double* b, double* c, double* d, double* e, double* f, double fai) {
    double h[5];
    if (T < 1000) {
        for (int j = 0; j < 9; j += 2) {
            enthalpy(T, R, h[j / 2], a[j], b[j], c[j], d[j], e[j], f[j]);
        }
        h_after_lean(fai, h, h_aft);
    } else {
        for (int j = 1; j < 10; j += 2) {
            enthalpy(T, R, h[j / 2], a[j], b[j], c[j], d[j], e[j], f[j]);
        }
        h_after_lean(fai, h, h_aft);
    }
}

void total_enthalpy_rich(double T, double R, double& h_aft, double* a, double* b, double* c, double* d, double* e, double* f, double fai) {
    double h[5];
    if (T < 1000) {
        for (int j = 0; j < 9; j += 2) {
            enthalpy(T, R, h[j / 2], a[j], b[j], c[j], d[j], e[j], f[j]);
        }
        h_after_rich(fai, h, h_aft);
    } else {
        for (int j = 1; j < 10; j += 2) {
            enthalpy(T, R, h[j / 2], a[j], b[j], c[j], d[j], e[j], f[j]);
        }
        h_after_rich(fai, h, h_aft);
    }
}

int main() {
    const double R = 8.3144;
    double T0 = 300, T1 = 300, T2 = 3000, epsilon = 0.01;
    double fai, h_bar, h_bef, h_aft1, h_aft2, h_aftm, Tm, f1, f2, fm, V1, V2;
    double a[10], b[10], c[10], d[10], e[10], f[10];
    
    ifstream data("data_a.csv");
    ofstream output("T_fai.out");
    
    for (int i = 0; i < 10; ++i) {
        data >> a[i] >> b[i] >> c[i] >> d[i] >> e[i] >> f[i];
    }
    
    fai = 0.10;
    while (fai <= 3.00) {
        T1 = 300;
        T2 = 3000;
        
        for (int i = 0; i < 9; i += 2) {
            enthalpy(T0, R, h_bar, a[i], b[i], c[i], d[i], e[i], f[i]);
        }
        
        V1 = (fai + 3.5 + 3.5 * 79.0 / 21.0) * R * T1;
        h_bef = fai * h_bar + 3.5 * h_bar + 3.5 * 79.0 / 21.0 * h_bar;
        
        if (fai < 1.00) {
            while (abs(T2 - T1) > epsilon) {
                total_enthalpy_lean(T1, R, h_aft1, a, b, c, d, e, f, fai);
                total_enthalpy_lean(T2, R, h_aft2, a, b, c, d, e, f, fai);
                Tm = (T1 + T2) / 2;
                total_enthalpy_lean(Tm, R, h_aftm, a, b, c, d, e, f, fai);

                f1 = h_aft1 - h_bef;
                f2 = h_aft2 - h_bef;
                fm = h_aftm - h_bef;
                
                if (f1 * fm >= 0) {
                    T1 = Tm;
                } else {
                    T2 = Tm;
                }
            }
            V2 = (2 * fai + 3 * fai + 3.5 * 79.0 / 21.0 + 3.5 * (1 - fai)) * R * T1;
        } else {
            while (abs(T2 - T1) > epsilon) {
                total_enthalpy_rich(T1, R, h_aft1, a, b, c, d, e, f, fai);
                total_enthalpy_rich(T2, R, h_aft2, a, b, c, d, e, f, fai);
                Tm = (T1 + T2) / 2;
                total_enthalpy_rich(Tm, R, h_aftm, a, b, c, d, e, f, fai);

                f1 = h_aft1 - h_bef;
                f2 = h_aft2 - h_bef;
                fm = h_aftm - h_bef;
                
                if (f1 * fm >= 0) {
                    T1 = Tm;
                } else {
                    T2 = Tm;
                }
            }
            V2 = (2 + 3 + 3.5 * 79.0 / 21.0 + fai - 1) * R * T1;
        }
        
        cout << fai << "  " << T1 << "  " << V2 / V1 << endl;
        output << fai << "  " << T1 << "  " << V2 / V1 << endl;
        fai += 0.05;
    }
    
    data.close();
    output.close();

    return 0;
}
