#include <iostream>
#include <functional>
#include <vector>
#include <math.h>

double calculate(double a, double b, std::function<double(double, double)> &lambda){
    return lambda(a, b);
}

int main(){
    std::vector<std::function<double(double, double)>> operators = {
            [](double a, double b){return a + b;},
            [](double a, double b){return a - b;},
            [](double a, double b){return a*b;},
            [](double a, double b){return b != 0 ? a/b : 0;},
            [](double a, double b){return b != 0 ? a*a/b/b/b : 0;},
            [](double a, double b){return abs(b) <= 1 ? a*sqrt(1 - b*b)*(b-18)*a + b*a : 0;},
            [](double a, double b){return std::pow(a, b);},
            [](double a, double b){return std::pow(b, a);}
    };
    double a;
    double b;
    std::cout << "Let the magic begin! Please enter two numbers: ";
    std::cin >> a;
    std::cin >> b;
    for(int i = 0; i < operators.size(); i++){
        std::cout << "The result of operator number " << i << " is as follows: " << calculate(a, b, operators[i]) << std::endl;
    }
}