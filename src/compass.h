#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    glm::vec3 position, direction_x, direction_y, direction_z;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(glm::vec3 x, glm::vec3 y, glm::vec3 z);
    double speed;
private:
    VAO *object1;
    VAO *object2 ;
};

#endif // SEA_H
