#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float radius ; 
    void draw(glm::mat4 VP);
    float return_radius() ; 
    glm::vec3 return_position() ; 
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *Mountain;
    VAO *Lava ;
};

#endif // SEA_H
