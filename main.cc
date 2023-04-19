#include "diplom.hpp"

#define _N 50


double IntegralTrapInf(std::vector<double> _beta, std::vector<double> _m, int _i_, double Fn_1) {
  int i; // счётчик
  double integral; // здесь будет интеграл
  double a = 0.0, b = 1000; // задаём отрезок интегрирования
  double h = 0.1;// задаём шаг интегрирования
  double n; // задаём число разбиений n
  n = (b - a) / h;
  // вычисляем интеграл по формуле центральных прямугольников
  integral = 0.0;
  for(i = 1; i <= n; i++)
	integral = integral + h * fInf(_beta, _m, _i_, a + h * (i - 0.5), Fn_1);
  return integral;
}

double fInf(std::vector<double> _beta, std::vector<double> _m, int i, double x, double Fn_1) {
  return exp(-1 * _beta.at(i) * x) * IntegralTrapU(_m, i, x, Fn_1);
}

double IntegralTrapU(std::vector<double> _m, int _i_, double x, double Fn_1) {
  int i; // счётчик
  double integral; // здесь будет интеграл
  double a = 0.0, b = x; // задаём отрезок интегрирования
  double h = 0.1;// задаём шаг интегрирования
  double n; // задаём число разбиений n
  n = (b - a) / h;
  // вычисляем интеграл по формуле центральных прямугольников
  integral = 0.0;
  for(i = 1; i <= n; i++)
	integral = integral + h * fU(_m, _i_, a + h * (i - 0.5), Fn_1);
  return integral;
}

double fU(std::vector<double> _m, int i, double x, double Fn_1) {
  return exp(-1 * _m.at(i) * x) * Fn_1;
}

double F_n(std::vector<double> _lambda, std::vector<double> _beta, std::vector<double> _m, std::vector<double> x) {
  
  double res = 0;
  int i = _N - 1;
  double a1 = _lambda.at(i) * exp(-1 * _m.at(i) * x.at(i));

  double a2 = _beta.at(i) * _m.at(i) * exp(_beta.at(i) * x.at(i));

  double fi0 = 0;
  double fi = a1;

  // double fi = a1 + a2 * IntegralTrapInf(_beta, _m, 1, fi0);

  for (int i = _N - 2, n = 1; i >= 0 && n < _N; --i, ++n) {
    a1 = _lambda.at(i) * exp(-1 * _m.at(i) * x.at(i));
    a2 = _beta.at(i) * _m.at(i) * exp(_beta.at(i) * x.at(i));
    std::cout << "Iterashion: " << i << std::endl;

    fi = a1 + a2 * IntegralTrapInf(_beta, _m, i, fi);
    std::cout << i << ": " << fi << std::endl;
  }

  return fi;
}

std::vector<double> GenerateRaspr(double l) {
  std::vector<double> res;
  // uncomment to use a non-deterministic generator
   std::random_device gen;
  // std::mt19937 gen(2345);
  std::exponential_distribution<> distr(l);

  std::map<double, int> histogram;
  for (int i = 0; i < _N; ++i) {
    ++histogram[distr(gen)];
  }
  for (const auto& elem : histogram) {
    res.push_back(elem.first);
  }
  return res;
}

std::vector<double> Generate_b() {
  double lambda = 0.0678;
  return GenerateRaspr(lambda);
}

std::vector<double> Generate_m() {
  double lambda = 0.0987;
  return GenerateRaspr(lambda);
}

std::vector<double> Generate_c() {
  double lambda = 0.07;
  return GenerateRaspr(lambda);
}

std::vector<double> Generate_x(double X, std::vector<double> _c) {
  std::vector<double> x;
  x.push_back(X);
  for (int i = 1; i < _N; ++i) {
    x.push_back(x.at(i - 1) * (1 - 1 / _c.at(i)));
  }
  return x;
}

std::vector<double> Math_beta(std::vector<double> _b, std::vector<double> _c) {
  std::vector<double> _beta;
  for (int i = 0; i < _N; ++i) {
    _beta.push_back(_b.at(i)/_c.at(i));
  }
  return _beta;
}

std::vector<double> Math_lambda(std::vector<double> _beta, std::vector<double> _m) {
  std::vector<double> _lambda;
  for (int i = 0; i < _N; ++i) {
    _lambda.push_back(_beta.at(i)/(_m.at(i) + _beta.at(i)));
  }
  return _lambda;
}

void PrintVector(std::vector<double> vec) {
  int counter = 0;
  for (int i = 0; i < vec.size(); i++) {
    std::cout << std::fixed << std::setw(11) << ++counter << ": "
            << std::setw(14) << std::setprecision(10) << vec.at(i) << std::endl;
  }
}

int main() {

  // generate _b(i)  //
  std::vector<double> _b = Generate_b();
  std::cout << "_b generate successful" << std::endl;
  PrintVector(_b);
  // generate _m(i)  //  std::vector<double>
  std::vector<double> _m = Generate_m();
  std::cout << "_m generate successful" << std::endl;
  PrintVector(_m);
  // generate _c(i)  //
  std::vector<double> _c = Generate_c();
  std::cout << "_c generate successful" << std::endl;
  PrintVector(_c);


  //  math _beta(_b(i), _c(i))
  std::vector<double> _beta = Math_beta(_b, _c);
  std::cout << "_beta generate successful" << std::endl;
  PrintVector(_beta);
  //  math _lambda(_b(i), _m(i))
  std::vector<double> _lambda = Math_lambda(_b, _c);
  std::cout << "_lambda generate successful" << std::endl;
  PrintVector(_lambda);


  double X = 100000;


  std::vector<double> x = Generate_x(X, _c);
  //  start call func F
  double F = F_n(_lambda, _beta, _m, x);

  std::cout << "Teori is: " << F << std::endl;


}

// void test(const double l, const int s) {

//     // uncomment to use a non-deterministic generator
//       //  std::random_device gen;
//     std::mt19937 gen(2345);

//     std::exponential_distribution<> distr(l);

//     std::cout << std::endl;
//     std::cout << "min() == " << distr.min() << std::endl;
//     std::cout << "max() == " << distr.max() << std::endl;
//     std::cout << "lambda() == " << std::fixed << std::setw(11) << std::setprecision(10) << distr.lambda() << std::endl;

//     // generate the distribution as a histogram
//     std::map<double, int> histogram;
//     for (int i = 0; i < s; ++i) {
//         ++histogram[distr(gen)];
//     }

//     // print results
//     std::cout << "Distribution for " << s << " samples:" << std::endl;
//     int counter = 0;
//     for (const auto& elem : histogram) {
//         std::cout << std::fixed << std::setw(11) << ++counter << ": "
//             << std::setw(14) << std::setprecision(10) << elem.first << std::endl;
//     }
//     std::cout << std::endl;
// }

// void WOOOOOOW() {
//     double l_dist = 0.5;
//     int samples = 10;

//     std::cout << "Use CTRL-Z to bypass data entry and run using default values." << std::endl;
//     std::cout << "Enter a floating point value for the 'lambda' distribution parameter (must be greater than zero): ";
//     std::cin >> l_dist;
//     std::cout << "Enter an integer value for the sample count: ";
//     std::cin >> samples;

//     test(l_dist, samples);
// }

