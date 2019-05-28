#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position,direction_x, direction_y, direction_z ; 
    float rotation ; 
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
    VAO *object2;
};

#endif // BALL_H
