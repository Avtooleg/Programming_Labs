#include "Ball.h"
#include <math.h>
#include <iostream>

ball::ball(point start, vec acc, double timestep){
    q = start;
    a = acc;
    dt = timestep;
}

void ball::set_wall(line* new_wall) {
    wall = new_wall;
}

void ball::set_timestep(double timestep) {
    dt = timestep;
}
void ball::set_collision_call(bool decision) {
    collision_messaging = decision;
}
void ball::push(double v_applied, double a){
    const double pi = 3.1415;
    v.x += v_applied*cos(pi*a/180);
    v.y += v_applied*sin(pi*a/180);
}
void ball::fly(){
    double t_c = collission_alarm();
    if (wall_set && (t_c < dt)){
        if(collision_messaging){
            std::cout << "Collision happened!" << std::endl;
        }
        q.x += v.x * t_c + a.x * t_c * t_c / 2;
        q.y += v.y * t_c + a.y * t_c * t_c / 2;
        v.x += a.x * t_c;
        v.y += a.y * t_c;
        //collision logic
        if (wall->A == 0){
            v.y = -v.y;
        }
        else if(wall->B == 0){
            v.x = -v.x;
        }
        else{
            double old_v_y = v.y;
            double old_v_x = v.x;
            //these formulas were derived from the notion that V_n = -V_n_0, V_tang = V_0_tang
            v.x = (2*old_v_y + old_v_x*(wall->A/wall->B - wall->B/wall->A))/(-wall->A/wall->B - wall->B/wall->A);
            v.y = (2*old_v_x + old_v_y*(wall->B/wall->A - wall->A/wall->B))/(-wall->A/wall->B - wall->B/wall->A);
        }
        //after the collision
        t_c = dt - t_c;
        q.x += v.x * t_c + a.x * t_c * t_c / 2;
        q.y += v.y * t_c + a.y * t_c * t_c / 2;
        v.x += a.x * t_c;
        v.y += a.y * t_c;
    }
    else {
        q.x += v.x * dt + a.x * dt * dt / 2;
        q.y += v.y * dt + a.y * dt * dt / 2;
        v.x += a.x * dt;
        v.y += a.y * dt;
    }
}
double ball::collission_alarm() {
    //Evaluating k1*t^2 + k2*t + k3 = 0 (searching for a collision time)
    double k1 = (wall->A*a.x + wall->B*a.y);
    double k2 = (wall->A*v.x + wall->B*v.y);
    double k3 = (wall->C + wall->A*q.x + wall->B*q.y);
    double D = k2*k2 - 4*k1*k3;
    if (abs(k1) < epsilon){
        if (abs(k2) < epsilon){
            //Костыль to make it realize, that there won't be a collision
            return dt+1;
        }
        double t = -k3/k2;
        return (t>0) ? t : (dt+1);
    }
    if (D<0){
        return dt+1;
    }
    else {
        double t1 = (-k2 + sqrt(D))/(2*k1);
        double t2 = (-k2 - sqrt(D))/(2*k1);
        if(t1 < 0){
            return (abs(t1) < epsilon) ? 0 : dt+1;
        }
        else if(t2 < 0){
            return t1;
        }
        else{
            return t2;
        }
    }
}