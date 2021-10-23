#include <iostream>
#include "Ball.h"
#include <chrono>
#include <thread>
#include <string>

void print_ball_position(ball b){
    std::cout << "Ball's position: " << b.get_position().x << " " << b.get_position().y << std::endl;
}

void print_ball_speed(ball b){
    std::cout << "Ball's velocity: " << b.get_velocity().x << " " << b.get_velocity().y << std::endl;
}

int main() {
    //default settings. They are just rewrited by the std::cin later.
    float dt = 0.01;
    point start{0, 1};
    double v_push = 10;
    double a_push = 45;
    double timestep;
    int N;
    std::string prom;
    bool collision_messaging = true;
    bool speed_messaging = true;
    vec line_ray{1, 0};
    point line_point{0,0};
    vec acc{0, -9.8};
    //Getting data from the user
    //Please don't put the ball into the wall. He doesn't like it :) (collision logic will consider it as collision)
    std::cout << "Input starting point: " << std::endl;
    std::cin >> start.x >> start.y;
    std::cout << "Input starting velocity (v, angle): ";
    std::cin >> v_push >> a_push;
    std::cout << "Input earth's gravity vector (x,y): ";
    std::cin >> acc.x >> acc.y;
    std::cout << "Input wall configuration (a directional vector and a point): ";
    std::cin >> line_ray.x >> line_ray.y >> line_point.x >> line_point.y;
    std::cout << "Input timestep duration (s): ";
    std::cin >> dt;
    std::cout << "Input duration(timesteps): ";
    std::cin >> N;
    std::cout << "Should we show collisions? (y/n): ";
    std::cin >> prom;
    collision_messaging = (prom == "y");
    std::cout << "Should we show velocity? (y/n): ";
    std::cin >> prom;
    speed_messaging = (prom == "y");
    //Initializing ball, wall and etc.
    ball b(start, acc);
    line wall{line_point, line_ray};
    b.set_wall(&wall);
    b.push(v_push, a_push);
    b.set_timestep(dt);
    b.set_collision_call(collision_messaging);
    //Simulating the ball and getting results
    for(int n = 0; n<N; n++) {
        b.fly();
        print_ball_position(b);
        if(speed_messaging){
            print_ball_speed(b);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
