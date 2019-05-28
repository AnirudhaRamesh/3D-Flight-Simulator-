#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 5;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     
    float c1_r = 5 ; 
    int c1_nos = 20 ; 
    this->radius = c1_r ; 
    static GLfloat vertex_buffer_data[360] ; 
    GLfloat x_coord[20], y_coord[20] ; 

    for(int i = 0 ; i < c1_nos ; i++ )
    {
        x_coord[i] = c1_r * cos(2*M_PI*i/c1_nos) ; 
        y_coord[i] = c1_r * sin(2*M_PI*i/c1_nos) ; 
    }

    for(int i = 0 ; i < c1_nos ; i++ )
    {
        vertex_buffer_data[18*i]   = x_coord[i] ; 
        vertex_buffer_data[18*i+1] = y_coord[i] ; 
        vertex_buffer_data[18*i+2] = 0.0 ; 
        vertex_buffer_data[18*i+3] = x_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+4] = y_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data[18*i+5] = 0.0 ; 
        vertex_buffer_data[18*i+6] = x_coord[i]*4/5 ; 
        vertex_buffer_data[18*i+7] = y_coord[i]*4/5 ; 
        vertex_buffer_data[18*i+8] = -0.0 ; 
        vertex_buffer_data[18*i+9] = x_coord[i]*4/5 ; 
        vertex_buffer_data[18*i+10] = y_coord[i]*4/5 ; 
        vertex_buffer_data[18*i+11] = -0.0 ; 
        vertex_buffer_data[18*i+12] = x_coord[(i+1)%c1_nos]*4/5 ; 
        vertex_buffer_data[18*i+13] = y_coord[(i+1)%c1_nos]*4/5 ; 
        vertex_buffer_data[18*i+14] = -0.0 ; 
        vertex_buffer_data[18*i+15] = x_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+16] = y_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data[18*i+17] = 0.0 ; 
    }

    this->Mountain = create3DObject(GL_TRIANGLES, 120, vertex_buffer_data, color  , GL_FILL);
    // this->Lava = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data_lava, COLOR_LAVA, GL_FILL ) ; 
}

void Ring::draw(glm::mat4 VP) {
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
    // draw3DObject(this->Lava) ;   
    // draw3DObject(this->object2) ; 
    // draw3DObject(this->object3) ; 
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Ring::return_position(){
    return this->position ; 
}

float Ring::return_radius(){
    return this->radius ; 
}

bounding_box_t Ring::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ;
    b.z = this->position.z ; 
    b.depth = b.height = b.width = this->radius * 2 ;  
    return b ; 
}

void Ring::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

