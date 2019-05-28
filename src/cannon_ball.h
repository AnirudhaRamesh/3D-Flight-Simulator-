#include "main.h"
#include "ball.h"

#ifndef CANNON_BALL_H
#define CANNON_BALL_H


class CannonBall {
public:
    CannonBall() {}
    CannonBall(float x, float y, float z, glm::vec3 z_axis, int type, Ball ball1);
    glm::vec3 position, direction_x, direction_y, direction_z;
    float rotation_x;
    float rotation_y ; 
    float rotation_z ; 
    float rotation ; 
    float x_ref ; 
    float y_ref ; 
    float z_ref ;
    float radius ;
    int type ; 
    float x_speed ; 
    float y_speed ; 
    float z_speed ; 
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
    glm::vec3 return_yaxis() ;
    glm::vec3 return_zaxis() ; 
    glm::vec3 return_xaxis() ; 
    int return_type() ; 
    bounding_box_t get_bounding_box() ; 
    double speed;
private:
    VAO *object;
    VAO *object2 ; 
};

#endif // BALL_H
