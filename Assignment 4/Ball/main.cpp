#include <iostream>
#include "Ball.h"
#include <chrono>
#include <thread>

void print_ball_position(ball b){
    std::cout << b.q.x << " " << b.q.y << std::endl;
}

int main() {
    float dt = 0.01;
    point start{0, 0};
    double v_push = 100;
    double a_push = 45;
    //std::cout << "Input starting point: " << std::endl;
    //std::cin >> start.x >> start.y;
    //std::cout << "Input starting velocity (v, angle): ";
    //std::cin >> v_push >> a_push;
    vec acc{0, -9.8};
    ball b(start, acc);
    vec line_ray{1, 0};
    point line_point{0,0};
    line ground{line_point, line_ray};
    b.set_wall(&ground);
    b.push(v_push, a_push);
    std::cout << "bugfix " << "v_x " << b.v.x << " v_y " << b.v.y << std::endl;
    for(int n = 0; n<10; n++) {
        b.fly();
        print_ball_position(b);
        std::cout << "bugfix " << "v_x " << b.v.x << " v_y " << b.v.y << std::endl;
        //If this (std::this_thread...) string is comment, ball goes upwards. If this string is not a comment - ball goes downwards. Magic!
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
