#include "fuel.h"
#include "main.h"

Fuel::Fuel(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 5;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     
    float c1_r = 2.1 ; 
    this->radius = c1_r ; 
    static GLfloat vertex_buffer_data[] = {
        1.8,0.0,0.0,
        1.8,-4.2,0.0,
        2.4,0.0,0.0,
        2.4,0.0,0.0,
        2.4,-4.2,0.0,
        1.8,-4.2,0.0, // vertical rect
        0.0,-1.8,0.0,
        0.0,-2.4,0.0,
        4.2,-1.8,0.0,
        4.2,-1.8,0.0,
        4.2,-2.4,0.0,
        0.0,-2.4,0.0,
    } ; 

    this->Mountain = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color  , GL_FILL);
    // this->Lava = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data_lava, COLOR_LAVA, GL_FILL ) ; 
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->rotation += 3 ; 
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Mountain);
}

void Fuel::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Fuel::return_position(){
    return this->position ; 
}

float Fuel::return_radius(){
    return this->radius ; 
}

bounding_box_t Fuel::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ;
    b.z = this->position.z ; 
    b.depth = b.height = b.width = this->radius * 2 ;  
    return b ; 
}

void Fuel::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

