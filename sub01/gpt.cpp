#include <iostream>
#include <cmath>
using namespace std;

const int spmax = 5; // 生成物の数

// NASA多項式による燃焼生成物の定圧モルエンタルピーの計算
double calculate_specific_heat(double T, const double coefficients[], int num_coefficients) {
    double H = 0.0;
    double T_power = 1.0;
    for (int i = 0; i < num_coefficients; ++i) {
        H += coefficients[i] * T_power;
        T_power *= T;
    }
    return H;
}

// 定圧変化の関数
double adiabatic_combustion(double T_initial, double equivalence_ratio, const double coefficients[][12], int num_species) {
    double H_final = 0.0;
    // すべての生成物の定圧モルエンタルピーを計算
    for (int i = 0; i < num_species; ++i) {
        double* coeffs = (double*)coefficients[i];
        H_final += equivalence_ratio * calculate_specific_heat(T_initial, coeffs, 6);
    }
    // 燃焼後の温度を求める
    double T_final = T_initial + H_final / (equivalence_ratio * 8.314);
    return T_final;
}

int main() {
    double T_initial = 298; // 燃焼前の温度（K）
    double equivalence_ratio; // 当量比
    cout << "当量比を入力してください: ";
    cin >> equivalence_ratio;

    // NASA多項式の係数
    const double nasaCp[spmax][12] = { /* ここにNASA多項式の係数が入ります */ };
    
    // 生成物の数
    int num_species = sizeof(nasaCp) / sizeof(nasaCp[0]);

    // 定圧変化後の温度を計算
    double T_final = adiabatic_combustion(T_initial, equivalence_ratio, nasaCp, num_species);
    cout << "定圧変化後の温度: " << T_final << " K" << endl;

    return 0;
}
