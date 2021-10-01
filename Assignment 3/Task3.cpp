#include <iostream>
#include <vector>
#include <algorithm>

void print_arr(std::vector<int>& array, int length){
    for (int i = 0; i<length; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    //std::vector<int> array = {1, 18, 6, 15, 9, 0, -4, 13, 87, -15};
    int N;
    int prom;
    std::vector<int> array;
    std::cout << "Enter size of array: ";
    std::cin >> N;
    std::cout << "Enter an array: ";
    for (int i = 0; i<N; i++) {
        std::cin >> prom;
        array.push_back(prom);
    }
    //Descending order
    std::sort(array.begin(), array.end(), [](int a, int b){return a>b;});
    print_arr(array, array.size());
    //Ascending order
    std::sort(array.begin(), array.end(), [](int a, int b){return a<b;});
    print_arr(array, array.size());
}