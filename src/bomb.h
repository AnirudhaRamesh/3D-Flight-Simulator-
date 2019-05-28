#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, glm::vec3 z_axis);
    glm::vec3 position, direction_x, direction_y, direction_z;
    float rotation_x;
    float rotation_y ; 
    float rotation_z ; 
    float rotation ; 
    float x_ref ; 
    float y_ref ; 
    float z_ref ;
    float radius ;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float return_x() ; 
    float return_y() ; 
    float return_z() ; 
    bounding_box_t get_bounding_box() ; 
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
