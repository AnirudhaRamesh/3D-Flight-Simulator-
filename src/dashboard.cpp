#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1 ; 
    // Yvelovity = 0 ; 
    // gravity = 0.005 ;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices 

    static GLfloat vertex_buffer_data_one[6*3] ={
        0.0, 0.0, 0.0,
        0.0, -0.2, 0.0,
        0.04, 0.0, 0.0,
        0.04, 0.0, 0.0, 
        0.0, -0.2, 0.0,
        0.04, -0.2, 0.0 
    } ; 

    static GLfloat vertex_buffer_data_two[6*3] = {
        0.0, -0.2, 0.0,
        0.0, -0.4, 0.0, 
        0.04, -0.2, 0.0,
        0.04, -0.2, 0.0, 
        0.0, -0.4, 0.0,
        0.04, -0.4, 0.0,
    } ;

    static GLfloat vertex_buffer_data_three[6*3] = {
        0.2, -0.2, 0.0,
        0.2, -0.4, 0.0, 
        0.24, -0.2, 0.0,
        0.24, -0.2, 0.0, 
        0.2, -0.4, 0.0,
        0.24, -0.4, 0.0,
    } ; 

    static GLfloat vertex_buffer_data_four[6*3] = {
        0.2, 0.0, 0.0,
        0.2, -0.2, 0.0,
        0.24, 0.0, 0.0,
        0.24, 0.0, 0.0, 
        0.2, -0.2, 0.0,
        0.24, -0.2, 0.0 
    } ; 

    static GLfloat vertex_buffer_data_five[6*3] = {
        0.0, 0.0 , 0.0,
        0.0, -0.04, 0.0,
        0.2, 0.0, 0.0,
        0.2, 0.0, 0.0, 
        0.0, -0.04, 0.0,
        0.2, -0.04, 0.0,
    } ; 

    static GLfloat vertex_buffer_data_six[6*3] = {
        0.0, -0.2 , 0.0,
        0.0, -0.24, 0.0,
        0.2, -0.2, 0.0,
        0.2, -0.2, 0.0, 
        0.0, -0.24, 0.0,
        0.2, -0.24, 0.0,
    } ; 

    static GLfloat vertex_buffer_data_seven[6*3] = {
        0.0, -0.4 , 0.0,
        0.0, -0.44, 0.0,
        0.2, -0.4, 0.0,
        0.2, -0.4, 0.0, 
        0.0, -0.44, 0.0,
        0.2, -0.44, 0.0,
    } ; 
    

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_one, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_two, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_three, color, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_four, color, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_five, color, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_six, color, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_seven, color, GL_FILL);


}

void Dashboard::draw(glm::mat4 VP, int score) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate ;
    rotate[0] = glm::vec4(direction_x, 0.0) ; 
    rotate[1] = glm::vec4(direction_y, 0.0) ; 
    rotate[2] = glm::vec4(direction_z, 0.0) ; 
    rotate[3] = glm::vec4(0.0,0.0,0.0,1.0) ;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
      switch(score){
            case 0 : 
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object2) ; 
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object7) ; 
                    break ; 
            case 1 :
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object2) ;
                    break ; 
            case 2 :
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object6) ; 
                    draw3DObject(this->object7) ; 
                    draw3DObject(this->object2) ;
                    break  ;

            case 3 :
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object6) ; 
                    draw3DObject(this->object7) ; 
                    break ; 

            case 4 :
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object6) ; 
                    break ; 
            case 5 :
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object6) ; 
                    draw3DObject(this->object7) ; 
                    break ; 
            case 6 :
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object2) ; 
                    draw3DObject(this->object3) ;  
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object6) ; 
                    draw3DObject(this->object7) ; 
                    break ; 
            case 7 :
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    break ; 
            case 8 :
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object2) ; 
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object6) ; 
                    draw3DObject(this->object7) ;
                    break; 
            case 9 :  
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object6) ; 
                    break ; 

            default : 
                    draw3DObject(this->object1) ;
                    draw3DObject(this->object2) ; 
                    draw3DObject(this->object3) ; 
                    draw3DObject(this->object4) ; 
                    draw3DObject(this->object5) ; 
                    draw3DObject(this->object7) ; 
                    break ;
        }

}

void Dashboard::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Dashboard::tick(glm::vec3 x_axis, glm::vec3 y_axis, glm::vec3 z_axis) {
    direction_x = x_axis ; 
    direction_y = y_axis ; 
    direction_z = z_axis ; 
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

