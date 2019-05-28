#include "cannon_ball.h"
#include "ball.h"
#include "main.h"

CannonBall::CannonBall(float x, float y, float z, glm::vec3 z_axis, int type, Ball b ) {
    this->position = glm::vec3(x, y, z);
    this->direction_x = glm::vec3(1,0,0) ; 
    this->direction_y = glm::vec3(0,1,0) ; 
    this->direction_z = glm::vec3(0,0,1) ; 
    this->rotation_x = 0;
    this->rotation_y = 0;
    this->rotation_z = 0;
    this->rotation = 0 ; 
    speed = 1;
    this->type = type ; 
    this->x_speed = 0 ; 
    this->y_speed = 0 ; 
    this->z_speed = 0 ; 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->radius = 1.0 ; 
    // cylinder first 

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

    this->object = create3DObject(GL_TRIANGLES, 36 , vertex_buffer_data, COLOR_BLACK, GL_FILL);

    // to determine plane position in 5 seconds 
    float new_x, new_y, new_z ; 
    if(rand()%2 == 0)
    {
        new_x = b.return_x() - z_axis.x * 10; 
        new_y = b.return_y() - z_axis.y * 10; 
        new_z = b.return_z() - z_axis.z * 10;
    }else{
        new_x = b.return_x(); 
        new_y = b.return_y(); 
        new_z = b.return_z();
    }
    this->x_speed = (new_x - this->position.x) / 30; 
    this->y_speed = (new_y - this->position.y) / 30; 
    this->z_speed = (new_z - this->position.z) / 30; 

}

void CannonBall::draw(glm::mat4 VP) {
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
    draw3DObject(this->object2); 
}

float CannonBall::return_x(){
    return this->position.x ;
}

float CannonBall::return_y(){
    return this->position.y ; 
}

float CannonBall::return_z(){
    return this->position.z ; 
}


int CannonBall::return_type(){
    return this->type ; 
}

bounding_box_t CannonBall::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.height = b.width = this->radius * 2 ; 
    b.depth = 2.0 ; 

    return b ; 
}

void CannonBall::tick() {
    this->position.x += x_speed ; 
    this->position.y += y_speed ; 
    this->position.z += z_speed ; 
}

