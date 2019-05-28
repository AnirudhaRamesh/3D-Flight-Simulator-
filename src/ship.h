#include "main.h"

#ifndef SHIP_H
#define SHIP_H


class Ship {
public:
    Ship() {}
    Ship(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float radius ; 
    void draw(glm::mat4 VP);
    float return_radius() ; 
    glm::vec3 return_position() ; 
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t get_bounding_box() ; 
private:
    VAO *Sides;
    VAO *Base ;
    VAO *Flag ; 
};

#endif // SEA_H
