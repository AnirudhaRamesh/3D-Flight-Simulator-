#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    static GLfloat vertex_buffer_data[1000] = {0}, vertex_buffer_data_lava[200] ; 
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
        vertex_buffer_data[18*i+1] = -30.0 ; 
        vertex_buffer_data[18*i+2] = z_coord[i] ; 
        vertex_buffer_data[18*i+3] = x_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+4] = -30.0 ; 
        vertex_buffer_data[18*i+5] = z_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+6] = x_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+7] = -10.0 ; 
        vertex_buffer_data[18*i+8] = z_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+9] = x_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+10] = -10.0 ; 
        vertex_buffer_data[18*i+11] = z_coord[i] / 3 ; // 0.0
        vertex_buffer_data[18*i+12] = x_coord[(i+1)%c1_nos]/3 ; // 0.0
        vertex_buffer_data[18*i+13]= -10.0 ; 
        vertex_buffer_data[18*i+14] = z_coord[(i+1)%c1_nos]/3 ; // 0.0
        vertex_buffer_data[18*i+15] = x_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+16] = -30.0 ; 
        vertex_buffer_data[18*i+17] = z_coord[(i+1) % c1_nos] ; 
    }

    for(int i=0 ; i< c1_nos ; ++i)
    {
        vertex_buffer_data_lava[9*i] = x_coord[i] / 3 ; 
        vertex_buffer_data_lava[9*i+1] = -10.0 ; 
        vertex_buffer_data_lava[9*i+2] = z_coord[i] / 3 ; 
        vertex_buffer_data_lava[9*i+3] =  x_coord[(i+1)%c1_nos] / 3; 
        vertex_buffer_data_lava[9*i+4] =  -10.0; 
        vertex_buffer_data_lava[9*i+5] =  z_coord[(i+1)%c1_nos] / 3; 
        vertex_buffer_data_lava[9*i+6] =  0.0; 
        vertex_buffer_data_lava[9*i+7] =  -10.0; 
        vertex_buffer_data_lava[9*i+8] =  0.0; 
    }


    this->Mountain = create3DObject(GL_TRIANGLES, 6*c1_nos, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->Lava = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data_lava, COLOR_LAVA, GL_FILL ) ; 
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Mountain);
    draw3DObject(this->Lava) ; 
    // draw3DObject(this->object2) ; 
    // draw3DObject(this->object3) ; 
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Volcano::return_position(){
    return this->position ; 
}

float Volcano::return_radius(){
    return this->radius ; 
}

void Volcano::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

