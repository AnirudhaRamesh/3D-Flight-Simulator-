#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->direction_x = glm::vec3(1,0,0) ; 
    this->direction_y = glm::vec3(0,1,0) ; 
    this->direction_z = glm::vec3(0,0,1) ; 
    this->rotation_x = 0;
    this->rotation_y = 0;
    this->rotation_z = 0;
    this->rotation = 0 ; 
    speed = 1;
    this->lives =  5; 
    this->fuel = 840 ; 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
   
    static GLfloat vertex_buffer_data[2000] ; 
    GLfloat x_coord[25], y_coord[25] ; 
    float c1_r = 0.5 ; 
    int c1_nos = 20 ;
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

    vertex_buffer_data[720] = 0.0 ;
    vertex_buffer_data[720+1] = 0.0 ; 
    vertex_buffer_data[720+2] = -2.0 ; 
    vertex_buffer_data[720+3] = 2.0 ; 
    vertex_buffer_data[720+4] = 0.0 ; 
    vertex_buffer_data[720+5] = 2.0 ; 
    vertex_buffer_data[720+6] = -2.0 ; 
    vertex_buffer_data[720+7] = 0.0 ; 
    vertex_buffer_data[720+8] = 2.0 ; 

    vertex_buffer_data[729] = 0.0 ;
    vertex_buffer_data[729+1] = 0.1 ; 
    vertex_buffer_data[729+2] = -2.0 ; 
    vertex_buffer_data[729+3] = 2.0 ; 
    vertex_buffer_data[729+4] = 0.1 ; 
    vertex_buffer_data[729+5] = 1.0 ; 
    vertex_buffer_data[729+6] = -2.0 ; 
    vertex_buffer_data[729+7] = 0.1 ; 
    vertex_buffer_data[729+8] = 1.0 ; 

    vertex_buffer_data[738] = -0.15 ;
    vertex_buffer_data[738+1] = 0.0 ; 
    vertex_buffer_data[738+2] = 0.0 ; 
    vertex_buffer_data[738+3] = -0.15 ; 
    vertex_buffer_data[738+4] = 0.0 ; 
    vertex_buffer_data[738+5] = 2.0 ; 
    vertex_buffer_data[738+6] = 0.0 ; 
    vertex_buffer_data[738+7] = 1.5 ; 
    vertex_buffer_data[738+8] = 2.0 ; 

    vertex_buffer_data[747] = 0.15 ;
    vertex_buffer_data[747+1] = 0.0 ; 
    vertex_buffer_data[747+2] = 0.0 ; 
    vertex_buffer_data[747+3] = 0.15 ; 
    vertex_buffer_data[747+4] = 0.0 ; 
    vertex_buffer_data[747+5] = 2.0 ; 
    vertex_buffer_data[747+6] = 0.0 ; 
    vertex_buffer_data[747+7] = 1.5 ; 
    vertex_buffer_data[747+8] = 2.0 ; 

    vertex_buffer_data[756] = 0.15 ;
    vertex_buffer_data[756+1] = 0.0 ; 
    vertex_buffer_data[756+2] = 2.0 ; 
    vertex_buffer_data[756+3] = -0.15 ; 
    vertex_buffer_data[756+4] = 0.0 ; 
    vertex_buffer_data[756+5] = 2.0 ; 
    vertex_buffer_data[756+6] = 0.0 ; 
    vertex_buffer_data[756+7] = 1.5 ; 
    vertex_buffer_data[756+8] = 2.0 ; 

    this->object = create3DObject(GL_TRIANGLES, c1_nos*3*2*2+3*5 , vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, c1_nos*3*2*2+3*5 , vertex_buffer_data, COLOR_BLACK, GL_LINE);
}

void Ball::draw(glm::mat4 VP) {
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

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

float Ball::return_x(){
    return this->position.x ;
}

float Ball::return_y(){
    return this->position.y ; 
}

float Ball::return_z(){
    return this->position.z ; 
}

void Ball::front(){
    if(speed <= 2.6)
        speed += 0.4 ;
    else{
        speed = 3.0 ; 
    } 
    // this->position.x -= speed*direction_z.x ; 
    // this->position.z -= speed*direction_z.z ; 
    // this->position.y -= speed*direction_z.y ; 
}

void Ball::turn_left(){

    if(this->rotation_y >= 360 && this->rotation_y <= -360)
    {
        this->rotation_y = 0 ; 
    }

    this->rotation_y -= 1 ; 
    glm::mat4 rotate_x  = glm::rotate((float)(-1 * M_PI / 180.0), this->direction_y) ; 
    this->direction_x = glm::vec3(rotate_x * glm::vec4(this->direction_x, 1.0)) ; 

    glm::mat4 rotate_z = glm::rotate((float)(-1*M_PI/180.0f), this->direction_y) ; 
    this->direction_z = glm::vec3(rotate_z * glm::vec4(this->direction_z,1.0)) ; 
}

void Ball::turn_right(){

    if(this->rotation_y >= 360 && this->rotation_y <= -360)
    {
        this->rotation_y = 0 ; 
    }
    this->rotation_y += 1 ; 
    glm::mat4 rotate_x  = glm::rotate((float)(1 * M_PI / 180.0), this->direction_y) ; 
    this->direction_x = glm::vec3(rotate_x * glm::vec4(this->direction_x, 1.0)) ; 

    glm::mat4 rotate_z = glm::rotate((float)(1*M_PI/180.0f), this->direction_y) ; 
    this->direction_z = glm::vec3(rotate_z * glm::vec4(this->direction_z,1.0)) ; 

}

void Ball::roll_right(){

    if(this->rotation_z >= 360 && this->rotation_z <= -360)
    {
        this->rotation_z = 0 ; 
    }

    this->rotation_z -= 1 ; 

    glm::mat4 rotate_y = glm::rotate((float)(-1*M_PI/180.0), this->direction_z)  ;
    this->direction_y = glm::vec3(rotate_y * glm::vec4(this->direction_y, 1.0)) ;

    glm::mat4 rotate_x = glm::rotate((float)(-1*M_PI/180.0), this->direction_z) ; 
    this->direction_x = glm::vec3(rotate_x * glm::vec4(this->direction_x, 1.0)) ; 

}

void Ball::roll_left(){
    if(this->rotation_z >= 360 && this->rotation_z <= -360)
    {
        this->rotation_z = 0 ; 
    }

    this->rotation_z += 1 ; 

    glm::mat4 rotate_y = glm::rotate((float)(1*M_PI/180.0), direction_z)  ;
    this->direction_y = glm::vec3(rotate_y * glm::vec4(this->direction_y, 1.0)) ;

    glm::mat4 rotate_x = glm::rotate((float)(1*M_PI/180.0), direction_z) ; 
    this->direction_x = glm::vec3(rotate_x * glm::vec4(this->direction_x, 1.0)) ; 

}

void Ball::go_up(){
    // this->position.y += 0.5 ; 
    if(this->rotation_x >= 360 && this->rotation_x <= -360)
    {
        this->rotation_x = 0 ; 
    }

    this->rotation_x += 1 ; 

    glm::mat4 rotate_z = glm::rotate((float)(1*M_PI/180.0), direction_x)  ;
    this->direction_z = glm::vec3(rotate_z * glm::vec4(this->direction_z, 1.0)) ;

    glm::mat4 rotate_y = glm::rotate((float)(1*M_PI/180.0), direction_x) ; 
    this->direction_y = glm::vec3(rotate_y * glm::vec4(this->direction_y, 1.0)) ; 
}

void Ball::go_down(){
    // this->position.y -= 0.5 ; 
    if(this->rotation_x >= 360 && this->rotation_x <= -360)
    {
        this->rotation_x = 0 ; 
    }

    this->rotation_x -= 1 ; 

    glm::mat4 rotate_z = glm::rotate((float)(-1*M_PI/180.0), direction_x)  ;
    this->direction_z = glm::vec3(rotate_z * glm::vec4(this->direction_z, 1.0)) ;

    glm::mat4 rotate_y = glm::rotate((float)(-1*M_PI/180.0), direction_x) ; 
    this->direction_y = glm::vec3(rotate_y * glm::vec4(this->direction_y, 1.0)) ; 
}

void Ball::barrel_roll(){
    roll_left() ; 
    front() ; 
    roll_left() ; 
    front() ; 
    roll_left() ; 
    front() ; 
}

void Ball::ldl(){
    go_up() ;
    front() ; 
    go_up() ;
    front() ; 
    go_up() ; 
    front() ; 

}


float Ball::return_rotation_z(){
    return this->rotation_z ; 
}

float Ball::return_rotation_y(){
    return this->rotation_y ; 
}

glm::vec3 Ball::return_yaxis(){
    return this->direction_y ; 
}

glm::vec3 Ball::return_zaxis(){
    return this->direction_z ; 
}

glm::vec3 Ball::return_xaxis(){
    return this->direction_x ; 
}

int Ball::return_lives(){
    return this->lives; 
}

void Ball::dec_lives(){
    this->lives -= 1 ; 
}

int Ball::return_fuel(){
    return this->fuel ; 
}

void Ball::dec_fuel(){
    this->fuel -= 1 ; 
}

void Ball::inc_fuel(int f){
    this->fuel += f ; 
}

bounding_box_t Ball::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.height = b.width = 5.0 ; 
    b.depth = 5.0 ; 
    return b ; 
}

void Ball::tick() {
    this->dec_fuel() ; 
    if(speed >= 0.2)
        speed -= 0.2 ;
    else
    {
            speed = 0.0 ; 
    }
    this->position.x -= speed*direction_z.x ; 
    this->position.z -= speed*direction_z.z ; 
    this->position.y -= speed*direction_z.y ; 
    // this->position.x -= direction_z.x ; 
    // this->position.z -= direction_z.z ; 
    // this->position.y -= direction_z.y ; 
    // this-> position.z += speed * this->direction.z ;
    // this->position.x += speed * this->direction.x ; 
    // this->position.y += speed * this->direction.y ;  
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

