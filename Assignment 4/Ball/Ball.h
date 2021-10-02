#ifndef INFO_SEM_3_BALL_H
#define INFO_SEM_3_BALL_H

struct point{
    double x, y;
};
//in the end decided to separate it from the point, to make cod more readable.
struct vec{
    double x, y;
};

struct line{
    //using a generalized line equation Ax + By + C = 0
    double A, B, C;
    //Constructing using a directional vector and a point (just easier): r = r0 + a*t, t from R
    line(point p0, vec a) :
    A(a.y),
    B(-a.x),
    C(a.x*p0.y - a.y*p0.x)
    {}
};

struct ball{
    point q;
    vec v = {0,0};
    vec a;
    line* wall;
    double epsilon = 1e-16;
    bool wall_set;
    bool collision_messaging = true;
    double dt;
    ball(point start, vec acc, double timestep = 0.01);
    void set_wall(line* new_wall);
    void set_timestep(double timestep);
    void set_collision_call(bool);
    void push(double v, double a);
    void fly();
    double collission_alarm();
};
#endif //INFO_SEM_3_BALL_H
