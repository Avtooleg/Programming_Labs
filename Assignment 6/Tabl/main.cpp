#include <iostream>
#include <math.h>
#include <stdexcept>

class Table{
    public:
    Table(int size = 0, int* array = nullptr):curr_size(0), max_size(pow(2, round(log2(size)) + 1)){
        if (size > 0){
            start_ptr = (int*) malloc(4*max_size);
            if(array != nullptr){
                for (int i = 0; i < size; i++) {
                    *(start_ptr + i) = array[i];
                    curr_size +=1;
                }
            };
        }
        else{
            start_ptr = array;
        }
    }

    void push(int value){
        if (curr_size < max_size){
            *(start_ptr + curr_size) = value;
            curr_size += 1;
        }
        else{
            max_size = max_size*2;
            int* new_ptr = (int*) malloc(4*max_size);
            move(start_ptr, new_ptr);
            *(start_ptr + curr_size) = value;
            curr_size += 1;
        };
    };

    void pop(){
        if (curr_size >= 1) {
            curr_size -= 1;
            if(curr_size < max_size/4-1){
                max_size = max_size/4;
                int* new_ptr = (int*) malloc(max_size*4);
                move(start_ptr, new_ptr);
            }
        }
        if (curr_size == 0){
            throw std::length_error("Nothing to delete!");
        }
    }

    int& operator[] (int id) const{
        if (id >= curr_size){
            throw std::out_of_range("ID out of bounds!");
        }
        else{
            return *(start_ptr + id);
        };
    };

    int get_size() const{
        return curr_size;
    }

    ~Table(){
        free(start_ptr);
    }

    private:
    int curr_size;
    int max_size;
    int* start_ptr;

    void move(int* old_ptr, int* new_ptr){
        for (int i = 0; i<curr_size; i++){
            *(new_ptr + i) = *(old_ptr + i);
        };
        /*for (int i = 0; i<max_size; i++){
            delete [] (old_ptr + i);
        };*/
        free(old_ptr);
        start_ptr = new_ptr;
    }
};

Table operator+(const  Table& a, const Table& b){
    Table result(a.get_size() + b.get_size());
    for (int i = 0; i < a.get_size(); i++){
        result.push(a[i]);
    };
    for (int i = 0; i < b.get_size(); i++){
        result.push(b[i]);
    };
    return result;
}

std::ostream& operator<<(std::ostream& os, const Table& a){
    os<<"{";
    for (int i = 0; i < a.get_size()-1; i++){
        os << i << " : " << a[i] << ", ";
    };
    os << a.get_size()-1 << " : " << a[a.get_size()-1];
    os<<"}";
    return os;
};


int main() {
    int array_1[3] = {1, 0, -4};
    int array_2[4] = {14, 15, 19, 16};

    Table table_1(3, array_1);
    Table table_2(4, array_2);
    std::cout<<"t1 "<< table_1<<std::endl;
    std::cout<<"t2 "<< table_2<<std::endl;
    table_1.pop();
    std::cout<<"t1 after pop()" << table_1<<std::endl;
    table_2.push(10);
    std::cout<<"t2 after push(10)" << table_2<<std::endl;
    std::cout<<"t2[2] " << table_2[2]<<std::endl;
    std::cout<<"t1+t2" << table_1 + table_2<<std::endl;
    std::cout<<"t2+t1" <<table_2 + table_1<<std::endl;
    std::cout << "t2.push(10) stress test" << std::endl;
    for(int i = 0; i<128; i++){
        table_2.push(10);
    }
    std::cout << table_2 << std::endl;
    std::cout << "t2.pop() stress test: ";
    for(int i = 0; i<128; i++){
        table_2.pop();
    }
    std::cout << table_2 << std::endl;
    std::cout << "Overdeleting table_2" << std::endl;
    for(int i = 0; i<5; i++){
        table_2.pop();
    }
}
