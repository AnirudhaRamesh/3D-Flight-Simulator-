#include "main.h"

#ifndef SPECIALENEMY_H
#define SPECIALENEMY_H


class SpecialEnemy {
public:
    SpecialEnemy() {}
    SpecialEnemy(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float radius ; 
    int lives ; 
    void draw(glm::mat4 VP);
    float return_radius() ; 
    glm::vec3 return_position() ; 
    void set_position(float x, float y);
    int get_lives() ; 
    void dec_life() ; 
    void tick();
    double speed;
    int turn ; 
    bounding_box_t get_bounding_box() ; 
private:
    VAO *Mountain ; 
    VAO *Sides;
    VAO *Base ;
    VAO *Flag ; 
};

#endif // SEA_H
