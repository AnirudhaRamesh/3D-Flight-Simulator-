#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float radius ; 
    void draw(glm::mat4 VP);
    float return_radius() ; 
    glm::vec3 return_position() ; 
    void set_position(float x, float y);
    void tick();
    bounding_box_t get_bounding_box() ; 
    double speed;
private:
    VAO *Mountain;
    VAO *Lava ;
};

#endif // SEA_H
