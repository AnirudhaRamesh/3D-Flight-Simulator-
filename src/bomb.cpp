#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z, glm::vec3 z_axis) {
    this->position = glm::vec3(x, y, z);
    this->direction_x = glm::vec3(1,0,0) ; 
    this->direction_y = glm::vec3(0,1,0) ; 
    this->direction_z = glm::vec3(0,0,1) ; 
    this->rotation_x = 0;
    this->rotation_y = 0;
    this->rotation_z = 0;
    this->rotation = 0 ; 
    speed = 1;
    // this->direction_z = z_axis ; 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->radius = 1 ; 

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };


    this->object = create3DObject(GL_TRIANGLES, 36 , vertex_buffer_data, COLOR_GREEN, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, c1_nos*3*2*2 , vertex_buffer_data, COLOR_BLACK, GL_LINE);

    // to determine plane position in 5 seconds 

}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate ;
    rotate[0] = glm::vec4(direction_x, 0.0) ; 
    rotate[1] = glm::vec4(direction_y, 0.0) ; 
    rotate[2] = glm::vec4(direction_z, 0.0) ; 
    rotate[3] = glm::vec4(0.0,0.0,0.0,1.0) ;

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

float Bomb::return_x(){
    return this->position.x ;
}

float Bomb::return_y(){
    return this->position.y ; 
}

float Bomb::return_z(){
    return this->position.z ; 
}


bounding_box_t Bomb::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.height = b.width = this->radius * 2 ; 
    b.depth = 2.0;  

    return b ; 
}

void Bomb::tick() {
    this->position.x -= direction_z.x ; 
    this->position.y -= direction_z.y ; 
    this->position.z -= direction_z.z ; 
    this->position.y -= 4; 
}

