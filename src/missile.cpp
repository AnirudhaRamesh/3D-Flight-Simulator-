#include "missile.h"
#include "ball.h"
#include "main.h"

Missile::Missile(float x, float y, float z, glm::vec3 z_axis, int type, Ball b ) {
    this->position = glm::vec3(x, y, z);
    this->direction_x = glm::vec3(1,0,0) ; 
    this->direction_y = glm::vec3(0,1,0) ; 
    this->direction_z = glm::vec3(0,0,1) ; 
    this->rotation_x = 0;
    this->rotation_y = 0;
    this->rotation_z = 0;
    this->rotation = 0 ; 
    speed = 1;
    this->direction_z = z_axis ; 
    this->type = type ; 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
   
    static GLfloat vertex_buffer_data[2000] ; 
    GLfloat x_coord[25], y_coord[25] ; 
    float c1_r = 0.25 ; 
    int c1_nos = 20 ;
    this->radius = c1_r ; 
    // cylinder first 

    for(int i = 0 ; i < c1_nos ; i++ )
    {
        x_coord[i] = c1_r * cos(2*M_PI*i/c1_nos) ; 
        y_coord[i] = c1_r * sin(2*M_PI*i/c1_nos) ; 
    }

    for(int i = 0 ; i < c1_nos ; i++ )
    {
        vertex_buffer_data[18*i]   = x_coord[i] ; 
        vertex_buffer_data[18*i+1] = y_coord[i] ; 
        vertex_buffer_data[18*i+2] = 2.0 ; 
        vertex_buffer_data[18*i+3] = x_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+4] = y_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+5] = 2.0 ; 
        vertex_buffer_data[18*i+6] = x_coord[i] ; 
        vertex_buffer_data[18*i+7] = y_coord[i] ; 
        vertex_buffer_data[18*i+8] = -2.0 ; 
        vertex_buffer_data[18*i+9] = x_coord[i] ; 
        vertex_buffer_data[18*i+10] = y_coord[i] ; 
        vertex_buffer_data[18*i+11] = -2.0 ; 
        vertex_buffer_data[18*i+12] = x_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+13] = y_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+14] = -2.0 ; 
        vertex_buffer_data[18*i+15] = x_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+16] = y_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+17] = 2.0 ; 
    }

    for(int i = 0 ; i < c1_nos ; ++i)
    {
        vertex_buffer_data[18*i + 360] = x_coord[i] ; 
        vertex_buffer_data[18*i+1 + 360] = y_coord[i] ; 
        vertex_buffer_data[18*i+2 + 360] = -2.0 ; 
        vertex_buffer_data[18*i+3 + 360] = x_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+4 + 360] = y_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+5 + 360] = -2.0 ; 
        vertex_buffer_data[18*i+6 + 360] = 0.0 ; 
        vertex_buffer_data[18*i+7 + 360] = 0.0 ; 
        vertex_buffer_data[18*i+8 + 360] = -3.0 ; 
        vertex_buffer_data[18*i+9 + 360] = 0.0 ; 
        vertex_buffer_data[18*i+10 + 360] = 0.0 ; 
        vertex_buffer_data[18*i+11 + 360 ] = -3.0 ; 
        vertex_buffer_data[18*i+12 + 360] = 0.0 ; 
        vertex_buffer_data[18*i+13 + 360] = 0.0 ; 
        vertex_buffer_data[18*i+14 + 360]= -3.0 ; 
        vertex_buffer_data[18*i+15 + 360] = x_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+16 + 360] = y_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+17 + 360] = -2.0 ; 
    }

    this->object = create3DObject(GL_TRIANGLES, c1_nos*3*2*2 , vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, c1_nos*3*2*2 , vertex_buffer_data, COLOR_BLACK, GL_LINE);
}

void Missile::draw(glm::mat4 VP) {
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

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

float Missile::return_x(){
    return this->position.x ;
}

float Missile::return_y(){
    return this->position.y ; 
}

float Missile::return_z(){
    return this->position.z ; 
}

void Missile::front(){
    this->position.x -= 4*direction_z.x ; 
    this->position.z -= 4*direction_z.z ; 
    this->position.y -= 4*direction_z.y ; 
}

float Missile::return_rotation_z(){
    return this->rotation_z ; 
}

float Missile::return_rotation_y(){
    return this->rotation_y ; 
}

glm::vec3 Missile::return_yaxis(){
    return this->direction_y ; 
}

glm::vec3 Missile::return_zaxis(){
    return this->direction_z ; 
}

glm::vec3 Missile::return_xaxis(){
    return this->direction_x ; 
}

int Missile::return_type(){
    return this->type ; 
}

bounding_box_t Missile::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.height = b.width = this->radius * 2 ; 
    b.depth = 5.0 ; 

    return b ; 
}

void Missile::tick() {
    // this-> position.z += speed * this->direction.z ;
    // this->position.x += speed * this->direction.x ; 
    // this->position.y += speed * this->direction.y ;  
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

