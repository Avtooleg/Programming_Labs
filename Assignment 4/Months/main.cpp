#include <iostream>
#include <string>

enum class Months {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};


int main(){
    std::string user_statement;
    Months month;
    std::cout << "Enter a number of the month you want to know the number of days within (example: 1 for january): ";
    //The simplest solution I could find. There was one with operator overloading, but it was hard to make sense of and implement, so here we are.
    //I could, of course, just make 12 ifs, but... it makes enum and switch-case-default kinda pointless.
    scanf("%d", &month);
    std::cout << std::endl;
    switch (month){
        case(Months::JANUARY):
            std::cout << "There is 31 days in your month";
            break;
        case(Months::FEBRUARY):
            std::cout << "There is 28 or 29 days, depending on the year in your month";
            break;
        case(Months::MARCH):
            std::cout << "There is 31 days in your month";
            break;
        case(Months::APRIL):
            std::cout << "There is 30 days in your month";
            break;
        case(Months::MAY):
            std::cout << "There is 31 days in your month";
            break;
        case(Months::JUNE):
            std::cout << "There is 30 days in your month";
            break;
        case(Months::JULY):
            std::cout << "There is 31 days in your month";
            break;
        case(Months::AUGUST):
            std::cout << "There is 31 days in your month";
            break;
        case(Months::SEPTEMBER):
            std::cout << "There is 30 days in your month";
            break;
        case(Months::OCTOBER):
            std::cout << "There is 31 days in your month";
            break;
        case(Months::NOVEMBER):
            std::cout << "There is 30 days in your month";
            break;
        case(Months::DECEMBER):
            std::cout << "There is 31 days in your month";
            break;
        default:
            std::cout << "There is no such a month!";
    }
}