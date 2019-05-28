#include "ship.h"
#include "main.h"

Ship::Ship(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    float c1_r = 15 ; 
    this->radius = c1_r ; 

    static GLfloat vertex_buffer_data[] = {
        -5.0f,-5.0f,-5.0f, // triangle 5 : begin
        -5.0f,-5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f, // triangle 5 : end
        5.0f, 5.0f,-5.0f, // triangle 2 : begin
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f, // triangle 2 : end
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f
    };

    static GLfloat vertex_buffer_data_base[] = {
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
    } ; 

    static GLfloat  vertex_buffer_data_flag[] = {
        0.0,-5.0,-0.5,
        0.0, -5.0,0.5,
        0.0, 10.0, 0.5,
        0.0, 10.0, -0.5,
        0.0, -5.0,-0.5,
        0.0, 10.0, 0.5,
        -0.5,-5.0,-0.0,
        0.5, -5.0,0.0,
        0.5, 10.0, 0.0,
        -0.5,10.0, -0.0,
        -0.5, -5.0,0.0,
        0.5, 10.0, 0.0,
    } ; 

    this->Sides = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data, COLOR_SHIP_SIDES, GL_FILL);
    this->Base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_base, COLOR_SHIP_BASE, GL_FILL);
    this->Flag = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data_flag, COLOR_RED, GL_FILL) ; 
}

void Ship::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Sides);
    draw3DObject(this->Base) ;
    draw3DObject(this->Flag) ; 

}

void Ship::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Ship::return_position(){
    return this->position ; 
}

float Ship::return_radius(){
    return this->radius ; 
}

bounding_box_t Ship::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.height = b.width = 10 ; 
    b.depth = 10 ; 

    return b ; 
}

void Ship::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

