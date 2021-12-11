#include <iostream>
#include <math.h>


//Works with two sorted half-intervals: [left, middle) and [middle, right)
template <typename T>
void print_arr(T* array, int length){
    for (int i = 0; i<length; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T, class Compare = bool(T&, T&)>
void array_merge(T* array, int left, int middle, int right,
                 Compare *sort_condition){
    T* new_array = new T[right - left];
    int curr_left_el = left;
    int curr_right_el = middle;
    for (int k = 0; k < right-left; k++){
        if (sort_condition(array[curr_left_el], array[curr_right_el])){
            new_array[k] = array[curr_left_el];
            curr_left_el += 1;
            if (curr_left_el == middle){
                for (int j = k+1; j < right-left; j++){
                    new_array[j] = array[curr_right_el];
                    curr_right_el += 1;
                    k = j;
                }
            }
        }
        else{
            new_array[k] = array[curr_right_el];
            curr_right_el += 1;
            if (curr_right_el == right) {
                for (int j = k + 1; j < right - left; j++) {
                    new_array[j] = array[curr_left_el];
                    curr_left_el += 1;
                    k = j;
                }
            }
        }
    }
    for(int i = 0; i < right-left; i++){
        array[left+i] = new_array[i];
    }
    delete[] new_array;
}

//Sorts by [left, right) half-intervals
template <typename T, class Compare = bool(T&, T&)>
void inner_split_sort(T* array, int left, int right,
                      Compare (*sort_condition)){
    if (right - left > 1){
        int middle = (left+right)/2;
        inner_split_sort<T, Compare>(array, left, middle, sort_condition);
        inner_split_sort<T, Compare>(array, middle, right, sort_condition);
        array_merge<T, Compare>(array, left, middle, right, sort_condition);
    }
}

template <typename T, class Compare = bool(T&, T&)>
void split_sort(T* array, std::size_t length, Compare *sort_condition = [](T& first, T& second){return first > second;}) {
    inner_split_sort<T, Compare>(array, 0, length, sort_condition);
}

template <typename T, std::size_t N, class Compare = bool(T&, T&)>
void split_sort(T (&array) [N], Compare *sort_condition = [](T& first, T& second){return first > second;}) {
    inner_split_sort<T, Compare>(array, 0, N, sort_condition);
}

int main(){
    float array[10] = {1.3, 1.6, 0.7, 0.8, 14.2, 7.5, 4.0, 8.1, 10.4, 13.9};
    std::cout << "Initial array" << '\n';
    print_arr<float>(array, 10);
    split_sort<float>(array);
    std::cout << "Sorted by default (decline)" << '\n';
    print_arr<float>(array, 10);
    split_sort<float, bool(float&, float&)>(array, 10,
                                            [](float& one, float& two){return (one - std::trunc(one) < two - std::trunc(two));});
    std::cout << "Sorted by rise of fractional part" << '\n';
    print_arr<float>(array, 10);

    std::cout << "Char sorting" << '\n';
    char* charray = new char[10]{'a', 'f', 'd', 'c', 't', 'j' , 'k', 'e', 'g', 'b'};
    std::cout << "Initial array" << '\n';
    print_arr(charray, 10);
    split_sort<char>(charray, 10);
    std::cout << "Default sort: " << '\n';
    print_arr(charray, 10);

}