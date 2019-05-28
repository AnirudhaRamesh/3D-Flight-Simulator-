#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, color_t color);
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
