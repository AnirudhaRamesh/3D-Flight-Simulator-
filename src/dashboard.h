#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z, color_t color);
    glm::vec3 position, direction_x, direction_y, direction_z;
    float rotation;
    void draw(glm::mat4 VP, int score);
    void set_position(float x, float y, float z);
    void tick(glm::vec3 x, glm::vec3 y, glm::vec3 z);
    double speed;
private:
    VAO *object1;
    VAO *object2 ;
    VAO *object3 ;
    VAO *object4 ;  
    VAO *object5 ;  
    VAO *object6 ;  
    VAO *object7 ;  

};

#endif // SEA_H
