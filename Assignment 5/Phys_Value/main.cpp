#include <iostream>
#include <string>

class IPhysValue
{
    public:
    //Initially, there was an enumerator class of measures, which was to be redefined in each of childs
    //But C++ just can't redefine pure virtual functions in this case, because it needs enumaration class in parent, and separates it from enumarator in child, and signatures of functions differ.
    virtual double get_value(std::string measure) = 0;
    virtual void set_value(double value, std::string measure) = 0;
    virtual ~IPhysValue() {};
};

class Energy: public IPhysValue
{
    public:

    constexpr static const double to_erg = 1e7;
    constexpr static const double to_evolt = 1/1.60218e-19;

    explicit Energy(double value = 0): IPhysValue(), energy(value){};

    virtual double get_value(std::string measure)
    {
        if(measure == "erg"){
                return energy*to_erg;
        }
        else if(measure == "evolts") {
            return energy*to_evolt;
        }
        else if(measure == "joules") {
            return energy;
        }
        return 0;
    };

    virtual void set_value(double value, std::string measure) override
    {
        if(measure == "erg"){
            energy = value/to_erg;
        }
        else if(measure == "evolts") {
            energy = value/to_evolt;
        }
        else if(measure == "joules"){
            energy = value;
        }
    };

    ~Energy() = default;

private:
    double energy; //In Joules
};

int main(){

    Energy energy(0);
    double value;
    std::string measure;
    int choice;

    while (true) {
        std::cout << "Do you want to load, read, or close? (1, 2, 3): ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Enter value of energy: ";
            std::cin >> value;
            std::cout << "Enter measure of energy (erg, evolts, joules): ";
            std::cin >> measure;
            std::cout << std::endl;
            energy.set_value(value, measure);
        }
        else if (choice == 2) {
            std::cout << "Enter measure of energy (erg, evolts, joules): ";
            std::cin >> measure;
            std::cout <<std::endl<< "Energy is " << energy.get_value(measure) << " " << measure << std::endl;
        }
        else{
            break;
        }
    }
    return 0;
}