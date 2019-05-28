#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_sea[] = {
        -500.0f,0.0f,-500.0f, // triangle 1 : begin
         500.0f,0.0f,-500.0f,
        -500.0f, 0.0f, 500.0f, // triangle 1 : end
        500.0f, 0.0f,-500.0f, // triangle 2 : begin
        -500.0f,0.0f,500.0f,
        500.0f, 0.0f,500.0f, // triangle 2 : end
    };

    static const GLfloat vertex_buffer_data_sky[] = {
        -0.0f,0.0f,-0.0f, // triangle 1 : begin
         0.0f,0.0f,-0.0f,
        -0.0f, 0.0f,-0.0f, // triangle 1 : end
        0.0f, 0.0f,-0.0f, // triangle 2 : begin
        -0.0f,0.0f,-0.0f,
        0.0f, 0.0f,-0.0f, // triangle 2 : end
        
        
        -0.0f,0.0f,0.0f, // triangle 1 : begin
        0.0f,0.0f,0.0f,
        -0.0f, 0.0f,0.0f, // triangle 1 : end
        0.0f, 0.0f,0.0f, // triangle 2 : begin
        -0.0f,0.0f,0.0f,
        0.0f, 0.0f,0.0f, // triangle 2 : end

        -0.0f,0.0f,-0.0f, // triangle 1 : begin
        -0.0f,0.0f,0.0f,
        -0.0f,0.0f,-0.0f, // triangle 1 : end
        -0.0f,0.0f,0.0f, // triangle 2 : begin
        -0.0f,0.0f,-0.0f,
        -0.0f, 0.0f,0.0f, // triangle 2 : end

        0.0f,0.0f,-0.0f, // triangle 1 : begin
        0.0f,0.0f,0.0f,
        0.0f,0.0f,-0.0f, // triangle 1 : end
        0.0f,0.0f,0.0f, // triangle 2 : begin
        0.0f,0.0f,-0.0f,
        0.0f, 0.0f,0.0f, // triangle 2 : end

        -0.0,0.0,-0.0,
        0.0,0.0,-0.0,
        -0.0,0.0,0.0,
        -0.0,0.0,0.0,
        0.0,0.0,-0.0,
        0.0,0.0,0.0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_sea, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_sea, COLOR_BLACK, GL_LINE);
    this->object2 = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data_sky, COLOR_SKY, GL_FILL) ; 
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object2) ; 
    // draw3DObject(this->object3) ; 
}

void Sea::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sea::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

