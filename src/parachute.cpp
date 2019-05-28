#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->direction_x = glm::vec3(1,0,0) ;
    this->direction_y = glm::vec3(0,1,0) ; 
    this->direction_z = glm::vec3(0,0,1) ; 
    this->rotation = 0 ; 
    speed = 1;
    // this->direction_z = z_axis ; 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[1000] ; 

    static const GLfloat vertex_buffer_data_top[] = {
        -6.0f,-6.0f,-6.0f, // triangle 6 : begin
        -6.0f,-6.0f, 6.0f,
        -6.0f, 6.0f, 6.0f, // triangle 6 : end
        6.0f, 6.0f,-6.0f, // triangle 2 : begin
        -6.0f,-6.0f,-6.0f,
        -6.0f, 6.0f,-6.0f, // triangle 2 : end
        6.0f,-6.0f, 6.0f,
        -6.0f,-6.0f,-6.0f,
        6.0f,-6.0f,-6.0f,
        6.0f, 6.0f,-6.0f,
        6.0f,-6.0f,-6.0f,
        -6.0f,-6.0f,-6.0f,
        -6.0f,-6.0f,-6.0f,
        -6.0f, 6.0f, 6.0f,
        -6.0f, 6.0f,-6.0f,
        6.0f,-6.0f, 6.0f,
        -6.0f,-6.0f, 6.0f,
        -6.0f,-6.0f,-6.0f,
        -6.0f, 6.0f, 6.0f,
        -6.0f,-6.0f, 6.0f,
        6.0f,-6.0f, 6.0f,
        6.0f, 6.0f, 6.0f,
        6.0f,-6.0f,-6.0f,
        6.0f, 6.0f,-6.0f,
        6.0f,-6.0f,-6.0f,
        6.0f, 6.0f, 6.0f,
        6.0f,-6.0f, 6.0f,
        6.0f, 6.0f, 6.0f,
        6.0f, 6.0f,-6.0f,
        -6.0f, 6.0f,-6.0f,
        6.0f, 6.0f, 6.0f,
        -6.0f, 6.0f,-6.0f,
        -6.0f, 6.0f, 6.0f,
        6.0f, 6.0f, 6.0f,
        -6.0f, 6.0f, 6.0f,
        6.0f,-6.0f, 6.0f
    };
    
    GLfloat x_coord[25], z_coord[25] ; 
    float c1_r = 15 ; 
    int c1_nos = 20 ;
    this->radius = c1_r ; 
    for(int i = 0 ; i < c1_nos ; i++ )
    {
        x_coord[i] = c1_r * cos(2*M_PI*i/c1_nos) ; 
        z_coord[i] = c1_r * sin(2*M_PI*i/c1_nos) ; 
    }

      for(int i = 0 ; i < c1_nos  ; ++i)
    {
        vertex_buffer_data[18*i] = x_coord[i] ; 
        vertex_buffer_data[18*i+1] = 30.0 ; 
        vertex_buffer_data[18*i+2] = z_coord[i] ; 
        vertex_buffer_data[18*i+3] = x_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+4] = 30.0 ; 
        vertex_buffer_data[18*i+5] = z_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+6] = x_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+7] = 10.0 ; 
        vertex_buffer_data[18*i+8] = z_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+9] = x_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+10] = 10.0 ; 
        vertex_buffer_data[18*i+11] = z_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+12] = x_coord[(i+1)%c1_nos]/3 ; // 0.0
        vertex_buffer_data[18*i+13]= 10.0 ; 
        vertex_buffer_data[18*i+14] = z_coord[(i+1)%c1_nos]/3 ; // 0.0
        vertex_buffer_data[18*i+15] = x_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+16] = 30.0 ; 
        vertex_buffer_data[18*i+17] = z_coord[(i+1) % c1_nos] ; 
    }

    for(int i=0 ; i< c1_nos ; ++i)
    {
        vertex_buffer_data[9*i+360] = x_coord[i] / 3 ; 
        vertex_buffer_data[9*i+1+360] = 10.0 ; 
        vertex_buffer_data[9*i+2+360] = z_coord[i] / 3 ; 
        vertex_buffer_data[9*i+3+360] =  x_coord[(i+1)%c1_nos] / 3; 
        vertex_buffer_data[9*i+4+360] =  10.0; 
        vertex_buffer_data[9*i+5+360] =  z_coord[(i+1)%c1_nos] / 3; 
        vertex_buffer_data[9*i+6+360] =  0.0; 
        vertex_buffer_data[9*i+7+360] =  10.0; 
        vertex_buffer_data[9*i+8+360] =  0.0; 
    }

    for(int i=0 ; i< c1_nos ; ++i)
    {
        vertex_buffer_data[9*i+540] = x_coord[i]; 
        vertex_buffer_data[9*i+1+540] = 30.0 ; 
        vertex_buffer_data[9*i+2+540] = z_coord[i]; 
        vertex_buffer_data[9*i+3+540] =  x_coord[(i+1)%c1_nos]; 
        vertex_buffer_data[9*i+4+540] =  30.0; 
        vertex_buffer_data[9*i+5+540] =  z_coord[(i+1)%c1_nos]; 
        vertex_buffer_data[9*i+6+540] =  0.0; 
        vertex_buffer_data[9*i+7+540] =  30.0; 
        vertex_buffer_data[9*i+8+540] =  0.0; 
    }

    this->object = create3DObject(GL_TRIANGLES, 36 , vertex_buffer_data_top, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 240, vertex_buffer_data, COLOR_LAVA, GL_FILL); 
    // this->object2 = create3DObject(GL_TRIANGLES, c1_nos*3*2*2 , vertex_buffer_data, COLOR_BLACK, GL_LINE);

    // to determine plane position in 5 seconds 

}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::vec3 temp = glm::vec3(this->position.x, this->position.y-30, this->position.z) ; 
    glm::mat4 translate = glm::translate (temp);    // glTranslatef
    glm::mat4 rotate ;
    rotate[0] = glm::vec4(direction_x, 0.0) ; 
    rotate[1] = glm::vec4(direction_y, 0.0) ; 
    rotate[2] = glm::vec4(direction_z, 0.0) ; 
    rotate[3] = glm::vec4(0.0,0.0,0.0,1.0) ;

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2) ; 
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

float Parachute::return_x(){
    return this->position.x ;
}

float Parachute::return_y(){
    return this->position.y ; 
}

float Parachute::return_z(){
    return this->position.z ; 
}


bounding_box_t Parachute::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.depth = b.width = this->radius * 2 ; 
    b.height = 36.0;  

    return b ; 
}

void Parachute::tick() {
    this->position.y -= 0.2; 
}

