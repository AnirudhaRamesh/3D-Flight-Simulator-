#include "compass.h"
#include "main.h"


Compass::Compass(float x, float y, float z) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1 ; 

    static GLfloat vertex_buffer_data_one[] = {
        0.2,0.0,0.0,
        0.0,0.4,0.0,
        -0.2,0.0,0.0,
    } ; 

    static GLfloat vertex_buffer_data_two[] = {
        0.2,0.0,0.0,
        -0.2,0.0,0.0,
        0.0,-0.4,0.0,
    } ; 

    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_one, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_two, COLOR_BLACK, GL_FILL);

}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate ;
    rotate[0] = glm::vec4(direction_x, 0.0) ; 
    rotate[1] = glm::vec4(direction_y, 0.0) ; 
    rotate[2] = glm::vec4(direction_z, 0.0) ; 
    rotate[3] = glm::vec4(0.0,0.0,0.0,1.0) ;
    
    glm::mat4 rotate2 ; 
    glm::vec3 y_rot = glm::normalize(glm::vec3(direction_z.x, direction_z.z, 0.0)) ; 
    glm::vec3 z_rot = glm::normalize(glm::vec3(0.0,0.0,1.0)) ; 
    glm::vec3 x_rot = glm::normalize(glm::cross(y_rot,z_rot)) ; 
   
    rotate2[0] = glm::normalize(glm::vec4(x_rot,0.0)) ; 
    rotate2[1] = glm::normalize(glm::vec4(y_rot,0.0)) ; 
    rotate2[2] = glm::normalize(glm::vec4(glm::vec3(0.0,0.0,1.0),0.0)) ; 
    rotate2[3] = glm::vec4(0.0,0.0,0.0,1.0) ; 
    
    Matrices.model *= (translate * rotate * rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2); 

}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick(glm::vec3 x_axis, glm::vec3 y_axis, glm::vec3 z_axis) {
    direction_x = x_axis ; 
    direction_y = y_axis ; 
    direction_z = z_axis ; 
}

