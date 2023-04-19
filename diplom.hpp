#ifndef DIPLOM_H_
#define DIPLOM_H_

#include <random>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <cmath>

double IntegralTrapInf(std::vector<double> _beta, std::vector<double> _m, int _i_, double Fn_1);
double fInf(std::vector<double> _beta, std::vector<double> _m, int i, double x, double Fn_1);
double IntegralTrapU(std::vector<double> _m, int _i_, double x, double Fn_1);
double fU(std::vector<double> _m, int i, double x, double Fn_1);
double F_n(std::vector<double> _lambda, std::vector<double> _beta, std::vector<double> _m, std::vector<double> x);
std::vector<double> GenerateRaspr(double l);
std::vector<double> Generate_b();
std::vector<double> Generate_m();
std::vector<double> Generate_c();
std::vector<double> Generate_x(double X, std::vector<double> _c);
std::vector<double> Math_beta(std::vector<double> _b, std::vector<double> _c);
std::vector<double> Math_lambda(std::vector<double> _beta, std::vector<double> _m);
void PrintVector(std::vector<double> vec);
#endif  // DIPLOM_H_