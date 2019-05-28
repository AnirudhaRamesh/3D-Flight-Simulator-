#include "specialenemy.h"
#include "main.h"

SpecialEnemy::SpecialEnemy(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    turn = 1 ;
    float c1_r = 5 ; 
    this->radius = c1_r ; 
    this->lives = 3 ; 

    static GLfloat vertex_buffer_data[] = {
        -5.0f,-5.0f,-5.0f, // triangle 5 : begin
        -5.0f,-5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f, // triangle 5 : end
        5.0f, 5.0f,-5.0f, // triangle 2 : begin
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f, // triangle 2 : end
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f,-5.0f,
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
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
        5.0f,-5.0f, 5.0f,
        -15.0f,-5.0f,-5.0f, // 2
        -15.0f,-5.0f, 5.0f,
        -15.0f, 5.0f, 5.0f, // triangle 5 : end
        -5.0f, 5.0f,-5.0f, // triangle 2 : begin
        -15.0f,-5.0f,-5.0f,
        -15.0f, 5.0f,-5.0f, // triangle 2 : end
        -5.0f,-5.0f, 5.0f,
        -15.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -15.0f,-5.0f,-5.0f,
        -15.0f,-5.0f,-5.0f,
        -15.0f, 5.0f, 5.0f,
        -15.0f, 5.0f,-5.0f,
        -5.0f,-5.0f, 5.0f,
        -15.0f,-5.0f, 5.0f,
        -15.0f,-5.0f,-5.0f,
        -15.0f, 5.0f, 5.0f,
        -15.0f,-5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f,
        -15.0f, 5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        5.0f,-5.0f,-5.0f, //3
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f, // triangle 5 : end
        15.0f, 5.0f,-5.0f, // triangle 2 : begin
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f, // triangle 2 : end
        15.0f,-5.0f, 5.0f,
        5.0f,-5.0f,-5.0f,
        15.0f,-5.0f,-5.0f,
        15.0f, 5.0f,-5.0f,
        15.0f,-5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f, 5.0f,-5.0f,
        15.0f,-5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        15.0f,-5.0f, 5.0f,
        15.0f, 5.0f, 5.0f,
        15.0f,-5.0f,-5.0f,
        15.0f, 5.0f,-5.0f,
        15.0f,-5.0f,-5.0f,
        15.0f, 5.0f, 5.0f,
        15.0f,-5.0f, 5.0f,
        15.0f, 5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        15.0f,-5.0f, 5.0f,
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


    int c1_nos = 20 ; 
    this->radius = c1_r ; 
    static GLfloat vertex_buffer_data_cone1[360] ; 
    GLfloat z_coord[20], y_coord[20] ; 

    for(int i = 0 ; i < c1_nos ; i++ )
    {
        z_coord[i] = c1_r * cos(2*M_PI*i/c1_nos) ; 
        y_coord[i] = c1_r * sin(2*M_PI*i/c1_nos) ; 
    }

    for(int i = 0 ; i < c1_nos ; i++ )
    {
        vertex_buffer_data_cone1[18*i]   = 15.0 ; 
        vertex_buffer_data_cone1[18*i+1] = y_coord[i] ; 
        vertex_buffer_data_cone1[18*i+2] = z_coord[i] ; 
        vertex_buffer_data_cone1[18*i+3] = 15.0 ; 
        vertex_buffer_data_cone1[18*i+4] = y_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data_cone1[18*i+5] = z_coord[(i+1)%c1_nos] ; 
        vertex_buffer_data_cone1[18*i+6] = 25.0 ; 
        vertex_buffer_data_cone1[18*i+7] = y_coord[i]*1/5 ; 
        vertex_buffer_data_cone1[18*i+8] = z_coord[i]*1/5; 
        vertex_buffer_data_cone1[18*i+9] = 25.0; 
        vertex_buffer_data_cone1[18*i+10] = y_coord[i]*1/5 ; 
        vertex_buffer_data_cone1[18*i+11] = z_coord[i]*1/5  ; 
        vertex_buffer_data_cone1[18*i+12] = 25.0 ; 
        vertex_buffer_data_cone1[18*i+13] = y_coord[(i+1)%c1_nos]*1/5 ; 
        vertex_buffer_data_cone1[18*i+14] = z_coord[(i+1)%c1_nos]*1/5 ; 
        vertex_buffer_data_cone1[18*i+15] =  15.0; 
        vertex_buffer_data_cone1[18*i+16] = y_coord[(i+1) % c1_nos] ; 
        vertex_buffer_data_cone1[18*i+17] = z_coord[(i+1) % c1_nos]; 
    }

    this->Mountain = create3DObject(GL_TRIANGLES, 120, vertex_buffer_data_cone1, COLOR_BROWN  , GL_FILL);
    this->Sides = create3DObject(GL_TRIANGLES, 108, vertex_buffer_data, COLOR_LAVA, GL_FILL);
    this->Base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_base, COLOR_LAVA, GL_FILL);
    this->Flag = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data_flag, COLOR_RED, GL_FILL) ; 
}

void SpecialEnemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Mountain) ; 
    draw3DObject(this->Sides);
    draw3DObject(this->Base) ;
    draw3DObject(this->Flag) ; 

}

void SpecialEnemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 SpecialEnemy::return_position(){
    return this->position ; 
}

float SpecialEnemy::return_radius(){
    return this->radius ; 
}

int SpecialEnemy::get_lives(){
    return this->lives; 
}

void SpecialEnemy::dec_life(){
    this->lives -= 1 ; 
}

bounding_box_t SpecialEnemy::get_bounding_box(){
    bounding_box_t b ; 
    b.x = this->position.x ; 
    b.y = this->position.y ; 
    b.z = this->position.z ; 

    b.height = 10; 
    b.width = 30 ; 
    b.depth = 10 ; 

    return b ; 
}

void SpecialEnemy::tick() {
    // this->rotation += speed;
    if(turn == 1)
    {
        this->position.x -= speed;
    // this->position.y -= speed;
        this->position.z -= speed ;
        if (this->position.x < -100.0)
        {
            turn = 2 ; 
        }
    }
    else if(turn == 2){
        this->position.x += speed;
    // this->position.y -= speed;
        this->position.z += speed ;
        if(this->position.x > 100.0)
            turn = 1 ; 
    }
}

