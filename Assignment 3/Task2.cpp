#include <iostream>
#include <vector>


bool more_less(float a, float b){
    return a > b;
}

//Works with two sorted half-intervals: [left, middle) and [middle, right)
void array_merge(float* array, int left, int middle, int right, bool (*sort_condition)(float, float) = more_less){
    std::vector<float> new_array;
    int curr_left_el = left;
    int curr_right_el = middle;
    for (int k = 0; k < right-left; k++){
        if (sort_condition(array[curr_left_el], array[curr_right_el])){
            new_array.push_back(array[curr_left_el]);
            curr_left_el += 1;
            if (curr_left_el == middle){
                for (int j = k+1; j < right-left; j++){
                    new_array.push_back(array[curr_right_el]);
                    curr_right_el += 1;
                }
            }
        }
        else{
            new_array.push_back(array[curr_right_el]);
            curr_right_el += 1;
            if (curr_right_el == right) {
                for (int j = k + 1; j < right - left; j++) {
                    new_array.push_back(array[curr_left_el]);
                    curr_left_el += 1;
                }
            }
        }
    }
    for(int i = 0; i < right-left; i++){
        array[left+i] = new_array[i];
    }
}

//Sorts by [left, right) half-intervals
void inner_split_sort(float* array, int left, int right){
    if (right - left > 1){
        int middle = (left+right)/2;
        inner_split_sort(array, left, middle);
        inner_split_sort(array, middle, right);
        array_merge(array, left, middle, right);
    }
}


void split_sort(float* array, int length) {
    inner_split_sort(array, 0, length);
}

void print_arr(float* array, int length){
    for (int i = 0; i<length; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    float array[10] = {1.0, 7.0, 0.0, -4.0, 14.0, 7.0, 4.0, 8.0, 10.0, 15.0};
    split_sort(array, 10);
    print_arr(array, 10);
}