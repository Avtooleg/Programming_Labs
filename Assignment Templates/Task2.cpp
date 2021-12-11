#include <iostream>

template <typename T>
class Group{
public:

    typedef std::size_t index;

    Group(){
        my_array = new T[2];
        my_size = 0;
        my_cap = 2;
    }
    Group(T* array, index size): my_array(array), my_size(size), my_cap(size){}
    //A copy constructor
    Group(Group& original): my_size(original.size()), my_cap(original.capacity()){
        my_array = new T[original.capacity()];
        for(index i = 0; i < my_size; i++){
            my_array[i] = original[i];
        }

    }
    //Move constructor
    Group(Group&& group){
        delete[] my_array;
        my_array = std::move(group.my_array);
        my_size = std::move(group.my_size);
        my_cap = std::move(group.my_cap);
    }

    //Copy operator
    T& operator=(const T& other){
        delete[] my_array;
        my_array = new T[other.capacity()];
        for(index i = 0; i < other.size(); i++){
            my_array[i] = other[i];
        }
        my_size = other.size();
        my_cap = other.capacity();
        return *this;
    }
    //Move operator
    T& operator=(T&& other){
        delete[] my_array;
        my_array = std::move(other.my_array);
        my_size = std::move(other.my_size);
        my_cap = std::move(other.my_cap);
        return *this;
    }


    void push_back(T& element) {
        if (my_cap < my_size + 1) {
            resize(my_size*2);
        };
        my_array[my_size] = element;
        my_size += 1;
    }

    void swap(index first, index last){
        T prom = my_array[first];
        my_array[first] = my_array[last];
        my_array[last] = prom;
    };

    index size(){
        return my_size;
    };

    index capacity(){
        return my_cap;
    };

    void resize(index new_size){
        T* new_array = new T[new_size];
        my_cap = new_size;
        for(index i = 0; i < my_size; i++){
            new_array[i] = my_array[i];
        }
        delete[] my_array;
        my_array = new_array;
    }

    T& operator[](index ind){
        return my_array[ind];
    }

    // just for debug
    void print(){
        std::cout << "[";
        for(index i = 0; i < my_size; i++){
            std::cout << my_array[i];
            if(i < my_size - 1){
                std::cout << ", ";
            }
        };
        std::cout << "]" << '\n';
    }

    ~Group(){
        delete[] my_array;
    }

private:

    T* my_array;
    index my_size;
    index my_cap;
};

template <typename T>
void print_arr(T* array, int length){
    for (int i = 0; i<length; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    Group<char> group1(new char[10]{'a', 'f', 'd', 'c', 't', 'j' , 'k', 'e', 'g', 'b'}, 10);
    Group<char> group2 = group1;
    char added = 'r';
    group2.push_back(added);
    std::cout << "Initial group ";
    group1.print();
    std::cout << "Modified group ";
    group2.print();
    std::cout << "Swapping 1-st and last in initial group ";
    group1.swap(0, 9);
    group1.print();
    std::cout << "Size and capacity of initial: " << group1.size() << ' ' << group1.capacity() << '\n';
    std::cout << "Resize to 20: ";
    group1.resize(20);
    std::cout << "New size and capacity and itself: " << group1.size() << ' ' << group1.capacity() << '\n';
    group1.print();
    std::cout << "Changing b for h: ";
    group1[0] = 'h';
    group1.print();
    std::cout << "And the third is... " << group1[2] << "!";
}