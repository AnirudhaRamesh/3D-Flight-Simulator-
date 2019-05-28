#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z,color_t color);
    glm::vec3 position, direction_x, direction_y, direction_z;
    float rotation_x;
    float rotation_y ; 
    float rotation_z ; 
    float rotation ; 
    float x_ref ; 
    float y_ref ; 
    float z_ref ;
    int lives ; 
    int fuel ; 
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float return_x() ; 
    float return_y() ; 
    float return_z() ; 
    float return_rotation_z() ; 
    float return_rotation_y() ; 
    void front() ; 
    void turn_left() ; 
    void turn_right() ; 
    void roll_right() ; 
    void roll_left() ; 
    void go_up() ; 
    void go_down() ; 
    void barrel_roll() ; 
    void ldl() ;
    int return_lives() ; 
    void dec_lives() ; 
    int return_fuel() ; 
    void dec_fuel() ; 
    void inc_fuel(int f) ; 
    glm::vec3 return_yaxis() ;
    glm::vec3 return_zaxis() ; 
    glm::vec3 return_xaxis() ; 
    double speed;
    bounding_box_t get_bounding_box() ; 
private:
    VAO *object;
    VAO *object2 ; 
};

#endif // BALL_H
