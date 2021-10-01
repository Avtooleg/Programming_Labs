#include <iostream>

long fibonachi(int n){
    if(n<0){
        return 0;
    }
    return n>1 ? (fibonachi(n-1) + fibonachi(n-2)) : 1;
}

int main(){
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    long result = fibonachi(n);
    if (result == 0){
        std::cout << "Input is invalid (<0)" << std::endl;
    }
    else{
        std::cout << "Here is your fibonachi number: " << result << std::endl;
    }
}