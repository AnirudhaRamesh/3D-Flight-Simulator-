#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "dashboard.h"
#include "volcano.h"
#include "checkpoint.h"
#include "ship.h"
#include "missile.h"
#include "cannon_ball.h"
#include "bomb.h"
#include "ring.h"
#include "fuel.h"
#include "parachute.h"
#include "compass.h"
#include "specialenemy.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Sea sea ;
Compass compass ;
vector <Dashboard> altitude ;
vector <Dashboard> lives ;
vector <Dashboard> speed ;
vector <Dashboard> fuel_remaining ;
vector <Dashboard> scoreboard ; 
vector <Volcano> volcano ;  
vector <Checkpoint> checkpoint ; 
vector <Ship> ship ; 
vector <Missile> missile ; 
vector <CannonBall> cannonball ; 
vector <Bomb> bomb ;
vector <Ring> ring ;  
vector <Fuel> fuel ; 
vector <Parachute> parachute ; 
vector<SpecialEnemy> se ; 

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, near = 0.1f, far = 500.0f;
float camera_rotation_angle = 0;

int view = 0;
float up_dir[3] = {0,1,0} ; 

float view_x = 0, view_y = 5, view_z = 10 ;
float target_x = 0, target_y = 0, target_z = 0 ; 
float prev_x=0, prev_y=0, prev_z=0 ; 

bool fp_view = false, tp_view = true ;

int timer_br=0, timer_ldl=0, plane_cooldown_timer = 0, ship_cooldown_timer = 0, bomb_cooldown_timer = 0, se_cooldown_timer = 0 ; 

glm::vec3 eye_pos ; 

int checkpoint_no = 0 ; 

int score = 0 ;

bool in_helicopter = false ;
double prev_h_x = 0, prev_h_y = 0 ; 

bool mouse_pressed = false; 

Timer t60(1.0 / 30);

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // if(view == 1)
    //     glm::vec3 eye (0, 0, 20) ;
    // else if (view == 2)

    // change view by hitting left or right

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(ball1.return_x() + view_x,ball1.return_y()+ view_y , ball1.return_z() + view_z) ; 
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (ball1.return_x() + target_x, ball1.return_y() + target_y, ball1.return_z() + target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_dir[0], up_dir[1], up_dir[2]);

    eye_pos = eye ;
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    sea.draw(VP) ;

    for(int i = 0 ; i < se.size() ; ++i)
        se[i].draw(VP) ; 
    // cout<<angle<<endl ; 
    for(int i = 0 ; i < volcano.size() ; ++i) 
        volcano[i].draw(VP) ; 

    if(checkpoint.size() > 0)
        checkpoint[0].draw(VP) ; 
    else
    {
            cout<<"WIN!\n" ;
            exit(0) ;  
    }
    

    for(int i = 0 ; i < ship.size() ; ++i)
        ship[i].draw(VP) ; 

    for(int i = 0 ; i <missile.size() ; ++i)
        missile[i].draw(VP) ; 
    
    for(int i = 0 ; i < cannonball.size() ; ++i)
        cannonball[i].draw(VP) ; 

    for(int i = 0 ; i < bomb.size() ; ++i)
        bomb[i].draw(VP) ; 

    for(int i = 0 ; i < ring.size() ; ++i)
        ring[i].draw(VP) ; 

    for(int i = 0 ; i < fuel.size() ; ++i)
        fuel[i].draw(VP) ; 
    
    for(int i = 0 ; i < parachute.size() ; ++i)
        parachute[i].draw(VP) ; 


    int height =  ball1.return_y() - sea.position.y ; 
    
    if(timer_br==0 && timer_ldl==0)
    {
        compass.draw(VP) ; 
        for(int i = 0 ; i < altitude.size() ; ++i)
            { 
                if(height==0) break ; 
                altitude[i].draw(VP,height%10) ;
                height = height/10 ;
            }

        int ls = ball1.return_lives() ; 
        for(int i = 0 ; i < lives.size() ; ++i)
            { 
                if(ls==0) break ; 
                lives[i].draw(VP,ls%10) ;
                ls = ls/10 ;
            }

        int flr = ball1.return_fuel() ; 
        for(int i = 0 ; i < fuel_remaining.size() ; ++i)
            { 
                if(flr==0) break ; 
                fuel_remaining[i].draw(VP,flr%10) ;
                flr = flr/10 ;
            }

        int change_x, change_y, change_z ; 
        change_x = (int)(prev_x - ball1.return_x()) ;
        change_y = (int)(prev_y - ball1.return_y()) ; 
        change_z = (int)(prev_z - ball1.return_z()) ; 

        prev_x = ball1.return_x() ; 
        prev_y = ball1.return_y() ; 
        prev_z = ball1.return_z() ; 
        int sp = sqrt(pow(change_x,2) + pow(change_y,2) + pow(change_z,2)) ;

        for(int i = 0 ; i < speed.size() ; ++i){
            speed[i].draw(VP,sp%10) ; 
            sp /= 10 ; 
            if(sp == 0) break ;
        } 

        int sc = score ; 
        for(int i = 0 ; i < scoreboard.size() ; ++i)
        {
        scoreboard[i].draw(VP,sc%10) ; 
            sc /= 10 ; 
            if(sc == 0) break ; 
        }
    }
}

void print_text(int x, int y, float r, float g, float b, int font, char string[])
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
  }
}

void helicopter_cam(){
    double xpos, ypos;
    glm::vec3 hc ; 
    if(mouse_pressed == true)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        if(xpos - prev_x > 0)
        {
            hc = glm::vec3(view_x, view_y, view_z) ; 
            hc = glm::vec3(glm::rotate((float)(1.0f*M_PI/180.0f), glm::vec3(0,1,0)) * glm::vec4(hc,1.0f));             
            view_x = hc.x; view_y = hc.y ; view_z = hc.z ; 
        }
        else if(xpos - prev_x < 0)
        {
            hc = glm::vec3(view_x, view_y, view_z) ; 
            hc = glm::vec3(glm::rotate((float)(-1.0f*M_PI/180.0f), glm::vec3(0,1,0)) * glm::vec4(hc,1.0f));             
            view_x = hc.x; view_y = hc.y ; view_z = hc.z ; 
        }
        if(ypos - prev_y > 0)
        {
            hc = glm::vec3(view_x, view_y, view_z) ; 
            hc = glm::vec3(glm::rotate((float)(1.0f*M_PI/180.0f), glm::vec3(1,0,0)) * glm::vec4(hc,1.0f));             
            view_x = hc.x; view_y = hc.y ; view_z = hc.z ; 
        }
        else if(ypos - prev_y < 0)
        {
            hc = glm::vec3(view_x, view_y, view_z) ; 
            hc = glm::vec3(glm::rotate((float)(-1.0f*M_PI/180.0f), glm::vec3(1,0,0)) * glm::vec4(hc,1.0f));             
            view_x = hc.x; view_y = hc.y ; view_z = hc.z ; 
        }
        prev_h_x = xpos ; 
        prev_h_y = ypos ; 
    }

    if(mouse_pressed == false)
    {
        cout<<"\nscreen_zoom "<<screen_zoom<<endl ; 
        cout<<view_x ; 
        view_x = screen_zoom*view_x; 
        view_y = screen_zoom*view_y ; 
        view_z = screen_zoom*view_z ;  
        screen_zoom = 1 ; 
        cout<<" " << view_x; 

    }
}

void tick_input(GLFWwindow *window) {
    int view1  = glfwGetKey(window, GLFW_KEY_1);
    int view2 = glfwGetKey(window, GLFW_KEY_2);
    int view3 = glfwGetKey(window, GLFW_KEY_3);
    int view4 = glfwGetKey(window, GLFW_KEY_4);
    int view5 = glfwGetKey(window, GLFW_KEY_5);
    int front = glfwGetKey(window, GLFW_KEY_W );
    int tilt_left = glfwGetKey(window, GLFW_KEY_D) ; 
    int tilt_right = glfwGetKey(window, GLFW_KEY_A) ; 
    int roll_left = glfwGetKey(window, GLFW_KEY_Q) ;
    int roll_right = glfwGetKey(window, GLFW_KEY_E) ; 
    int up = glfwGetKey(window, GLFW_KEY_UP) ; 
    int down = glfwGetKey(window, GLFW_KEY_DOWN) ; 
    int loopdaloop = glfwGetKey(window, GLFW_KEY_L) ; 
    int barrelroll = glfwGetKey(window, GLFW_KEY_K) ; 
    int space = glfwGetKey(window, GLFW_KEY_SPACE) ; 
    int bomb_key = glfwGetKey(window, GLFW_KEY_B) ; 

    glm::vec3 a ;  

    if(timer_br != 0)
    {
        ball1.barrel_roll() ; 
        timer_br-- ; 
    }
    else if(timer_ldl != 0)
    {
        ball1.ldl() ; 
        timer_ldl-- ; 
    }
    else{
        if(view1){
            view_x = 10 * ball1.return_zaxis().x;
            view_y = 5 + 10 * ball1.return_zaxis().y; 
            view_z = 10 * ball1.return_zaxis().z; 
            target_x = 0 ; 
            target_y = 0 ; 
            target_z = 0 ;
            fp_view = false ;
            tp_view = true ; 
            in_helicopter = false ;
        }
        if(view2){
            view_x = 0;
            view_y = 0; 
            view_z = 0; 
            target_x = 0 ; 
            target_y = 0 ; 
            target_z = 0 ;  
            fp_view = true ; 
            tp_view = false ; 
             in_helicopter = false ;
        }

        if(view3){
            view_x = 0.01 ; 
            view_y = 30 ; 
            view_z = 0 ; 
            target_x = 0 ; 
            target_y = 0 ; 
            target_z = 0 ; 
            fp_view = false ; 
            tp_view = false ; 
             in_helicopter = false ;
        }    
        if(view4)
        {
            view_x = 30 ; 
            view_y = 25 ; 
            view_z = 0 ; 
            target_x = 0 ; 
            target_y = 0 ; 
            target_z = 0 ;
            fp_view = false ; 
            tp_view = false ; 
             in_helicopter = false ;
        }
        if(view5)
        {
            view_x = 30 ; 
            view_y = 25 ; 
            view_z = 0 ; 
            target_x = 0 ; 
            target_y = 0 ; 
            target_z = 0 ;
            fp_view = false ; 
            tp_view = false ;  
            in_helicopter = true ;  
        }
        if(front){
            ball1.front() ; 
        }
        if(tilt_left){
            ball1.turn_left() ;  
        }
        if(tilt_right){
            ball1.turn_right() ; 
        }
        if(roll_left){
            ball1.roll_left() ;
        }
        if(roll_right){
            ball1.roll_right() ; 
        }
        if(up){
            ball1.go_up() ; 
        }
        if(down){
            ball1.go_down() ; 
        }
        if(loopdaloop){
            timer_ldl = 120 ; 
        }
        if(barrelroll){
            timer_br = 120 ; 
        }
        if(space && plane_cooldown_timer == 0){
            missile.push_back(Missile(ball1.return_x(),ball1.return_y(), ball1.return_z(), ball1.return_zaxis(),0, ball1)) ;
            plane_cooldown_timer = 15 ;  
        }
        if(bomb_key && bomb_cooldown_timer == 0){
            bomb.push_back(Bomb(ball1.return_x(), ball1.return_y(), ball1.return_z(), ball1.return_zaxis())) ; 
            bomb_cooldown_timer = 15 ; 
        }

        if(fp_view == true)
        {
            a = ball1.return_yaxis() ; 
            up_dir[0] = a.x ; up_dir[1]=a.y ; up_dir[2] = a.z ; 
            a = ball1.return_zaxis() ; 
            target_x = -10 * a.x ;  target_y = -10 * a.y ; target_z = -10 * a.z ;  
            view_x = -3 * ball1.return_zaxis().x;
            view_y = -3 * ball1.return_zaxis().y; 
            view_z = -3 * ball1.return_zaxis().z; 
        }
        else{
            up_dir[0] = 0 ; up_dir[1]=1 ; up_dir[2] = 0 ; 
        }
        if(tp_view == true)
        {
            a = ball1.return_yaxis() ; 
            up_dir[0] = a.x ; up_dir[1]=a.y ; up_dir[2] = a.z ; 
            view_x = 10 * ball1.return_zaxis().x + 5 * ball1.return_yaxis().x;
            view_y = 10 * ball1.return_zaxis().y + 5 * ball1.return_yaxis().y; 
            view_z = 10 * ball1.return_zaxis().z + 5 * ball1.return_yaxis().z; 
        }

        if(in_helicopter == true)
            helicopter_cam() ; 

    }
}


void check_collision_volcano(){
    float plane_x = ball1.return_x() ; 
    float plane_z = ball1.return_z() ; 
    glm::vec3 v_pos ; 
    float radius ; 
    for(int i = 0 ; i < volcano.size() ; ++i)
    {
       v_pos = volcano[i].return_position() ; 
       radius = volcano[i].return_radius() ; 
        if(plane_x >= v_pos.x - radius && plane_x <= v_pos.x + radius)
        {
            if(plane_z >= v_pos.z - radius && plane_z <= v_pos.z + radius)
            {
                cout<<"FLYING OVER VOLCANO\nGAME OVER\n" ; 
                exit(0) ; 
                // cout<<"COLLIDE "<<"plane x "<< plane_x <<" vx "<< v_pos.x << " plane z "<< plane_z << " vz "<< v_pos.z << " rad "<< radius<< '\n' ; 
            }
        } 
    }
}

void check_collision_checkpoint(){
    float plane_x = ball1.return_x() ; 
    float plane_z = ball1.return_z() ; 
    glm::vec3 v_pos ; 
    float radius ; 
    // for(int i = 0 ; i < checkpoint.size() ; ++i)
    // {
       v_pos = checkpoint[checkpoint_no].return_position() ; 
       radius = checkpoint[checkpoint_no].return_radius() ; 
        if(plane_x >= v_pos.x - radius && plane_x <= v_pos.x + radius)
        {
            if(plane_z >= v_pos.z - radius && plane_z <= v_pos.z + radius)
            {
                checkpoint_no++ ; 
                // cout<<"COLLIDE "<<"plane x "<< plane_x <<" vx "<< v_pos.x << " plane z "<< plane_z << " vz "<< v_pos.z << " rad "<< radius<< '\n' ; 
            }
        } 

        if(checkpoint_no == 5)
        {   
            cout<<"GAME COMPLETED!\n" ; 
            exit(0) ; 
        }    
    // }
}

void check_collision_coin(){
    
     for(int i = 0 ; i < ring.size() ; ++i)
    {
        if(detect_collision(ring[i].get_bounding_box(), ball1.get_bounding_box())) 
        {
            ring.erase(ring.begin() + i) ; 
            score+=50 ; 
        }
    }

}

void check_collision_fuel(){
    
     for(int i = 0 ; i < fuel.size() ; ++i)
    {
        if(detect_collision(fuel[i].get_bounding_box(), ball1.get_bounding_box())) 
        {
            fuel.erase(fuel.begin() + i) ; 
            ball1.inc_fuel(420) ; 
        }
    }

}

void check_collision_ground(){
    if(ball1.return_y() <= -100)
    {
        cout<<"Crashed onto ground\n"<<"GAME OVER!" ; 
        exit(0) ; 
    }
    for(int i = 0; i < ship.size() ; ++i)
    {
        if(detect_collision(ship[i].get_bounding_box(), ball1.get_bounding_box())){
            cout<<"Crashed into ship! \n"<<"GAME OVER\n" ;
            exit(0) ;  
        }
    }
    for(int i = 0 ; i <se.size() ; ++i)
    {
        if(detect_collision(ball1.get_bounding_box(), se[0].get_bounding_box())){
            cout<<"Crashed into Zepplin\n"<<"Game over\n" ; 
            exit(0) ; 
        }
    }
}

void tick_elements() {
    ball1.tick(); 

    if(ball1.return_fuel() <= 0){
        cout<<"FUEL TANK EMPTY!\nGAME OVER!\n" ; 
        exit(0) ; 
    } 
    glm::vec3 x = glm::vec3(1,0,0) ; 
    glm::vec3 y = glm::vec3(0,1,0) ; 
    glm::vec3 z = glm::vec3(0,0,1) ; 
    for(int i = 0 ; i < altitude.size() ; ++i)
    {
        altitude[i].tick(ball1.return_xaxis(),ball1.return_yaxis(), ball1.return_zaxis()) ;
        altitude[i].set_position(ball1.return_x() + 5 * ball1.return_zaxis().x - 2.25*ball1.return_xaxis().x - (i*ball1.return_xaxis().x)/2 , ball1.return_y() + 5 * ball1.return_zaxis().y - 2.25*ball1.return_xaxis().y -  (i*ball1.return_xaxis().y)/2 , ball1.return_z() + 5 * ball1.return_zaxis().z - 2.25*ball1.return_xaxis().z - (i*ball1.return_xaxis().z)/2 ) ; 
        fuel_remaining[i].tick(ball1.return_xaxis(),ball1.return_yaxis(), ball1.return_zaxis()) ;
        fuel_remaining[i].set_position(ball1.return_x() + 5 * ball1.return_zaxis().x + 2.75*ball1.return_xaxis().x - (i*ball1.return_xaxis().x)/2 , ball1.return_y() + 5 * ball1.return_zaxis().y + 2.75*ball1.return_xaxis().y -  (i*ball1.return_xaxis().y)/2 , ball1.return_z() + 5 * ball1.return_zaxis().z + 2.75*ball1.return_xaxis().z - (i*ball1.return_xaxis().z)/2 ) ; 
        lives[i].tick(ball1.return_xaxis(),ball1.return_yaxis(), ball1.return_zaxis()) ;
        lives[i].set_position(ball1.return_x() + 5 * ball1.return_zaxis().x + 2*ball1.return_xaxis().x  + 5*ball1.return_yaxis().x - (i*ball1.return_xaxis().x)/2 , ball1.return_y() + 5 * ball1.return_zaxis().y + 2*ball1.return_xaxis().y  + 5*ball1.return_yaxis().y -  (i*ball1.return_xaxis().y)/2 , ball1.return_z() + 5 * ball1.return_zaxis().z + 2*ball1.return_xaxis().z  + 5*ball1.return_yaxis().z - (i*ball1.return_xaxis().z)/2 ) ; 
        speed[i].tick(ball1.return_xaxis(),ball1.return_yaxis(), ball1.return_zaxis()) ;
        speed[i].set_position(ball1.return_x() + 5 * ball1.return_zaxis().x - 2*ball1.return_xaxis().x  + 5*ball1.return_yaxis().x - (i*ball1.return_xaxis().x)/2 , ball1.return_y() + 5 * ball1.return_zaxis().y - 2*ball1.return_xaxis().y  + 5*ball1.return_yaxis().y -  (i*ball1.return_xaxis().y)/2 , ball1.return_z() + 5 * ball1.return_zaxis().z - 2*ball1.return_xaxis().z  + 5*ball1.return_yaxis().z - (i*ball1.return_xaxis().z)/2 ) ; 
        scoreboard[i].tick(ball1.return_xaxis(),ball1.return_yaxis(), ball1.return_zaxis()) ;
        scoreboard[i].set_position(ball1.return_x() + 5 * ball1.return_zaxis().x + 0.2*ball1.return_xaxis().x - (i*ball1.return_xaxis().x)/2 , ball1.return_y() + 5 * ball1.return_zaxis().y + 0.2*ball1.return_xaxis().y -  (i*ball1.return_xaxis().y)/2 , ball1.return_z() + 5 * ball1.return_zaxis().z + 0.2*ball1.return_xaxis().z - (i*ball1.return_xaxis().z)/2 ) ; 
  
    }

    compass.tick(ball1.return_xaxis(), ball1.return_yaxis(), ball1.return_zaxis()) ; 
    compass.set_position(ball1.return_x() + 4.75 * ball1.return_zaxis().x + 4.75*ball1.return_yaxis().x, ball1.return_y() + 4.75 * ball1.return_zaxis().y + 4.75*ball1.return_yaxis().y , ball1.return_z() + 4.75 * ball1.return_zaxis().z + 4.75*ball1.return_yaxis().z) ; 

    for(int i = 0 ; i <missile.size() ; ++i)
    {   
        if(missile[i].return_type() == 0)
        {
            missile[i].front() ;
            for(int j = 0 ; j < ship.size() ; ++j) 
            {
                if(detect_collision(missile[i].get_bounding_box(), ship[j].get_bounding_box()))
                {
                    cout<<"COLLIDE!!!\n\n" ; 
                    ship.erase(ship.begin()+j) ; 
                    checkpoint.erase(checkpoint.begin()+j) ; 
                    score += 500 ; 
                }
            }
            for(int j = 0 ; j < parachute.size() ; ++j)
            {
                if(detect_collision(missile[i].get_bounding_box(), parachute[j].get_bounding_box()))
                {
                    cout<<"PARACHUTE COLLECTED!\n\n" ; 
                    parachute.erase(parachute.begin()+j) ; 
                    score += 200 ; 
                }
            }
        }

        if(detect_collision(missile[i].get_bounding_box(), se[0].get_bounding_box()))
        {
                missile.erase(missile.begin() + i) ; 
                se[0].dec_life() ;
                if(se[0].get_lives() == 0)
                {   
                    se.erase(se.begin()) ;  
                    score+=1000 ; 
                } 
        }

        if(abs((int)missile[i].return_x()) >= 750 || abs((int)missile[i].return_y())>=750 || abs((int)missile[i].return_z()) >= 750)
        {
            missile.erase(missile.begin()+i) ; 
        }
    }
    
    for(int i = 0 ; i < cannonball.size() ; ++i)
    {
        if(cannonball[i].return_type() == 1)
        {   
            cannonball[i].tick() ; 
            if(detect_collision(cannonball[i].get_bounding_box(), ball1.get_bounding_box())) 
            {
                ball1.dec_lives() ; 
                cannonball.erase(cannonball.begin() + i) ; 
                cout<<"LIFE LOST! LIVES REMAINING : "<<ball1.return_lives()<<endl ; 
                if(ball1.return_lives() == 0)
                {
                    cout<<"LIVES OVER! GAME OVER!\n" ; 
                    exit(0) ; 
                }
            }   
        }
    }

    if(plane_cooldown_timer > 0)
        plane_cooldown_timer-- ; 

    check_collision_volcano() ;
    check_collision_coin() ; 
    check_collision_fuel() ; 
    check_collision_ground() ; 


    for(int i = 0 ; i < ship.size() ; i++)
    {
        bounding_box_t b = ship[i].get_bounding_box() ; 
        if(abs(ball1.return_x() - b.x) < 100 && abs(ball1.return_y() - b.y) < 100 && abs(ball1.return_z() - b.z) < 100 && ship_cooldown_timer == 0)
        {
            cannonball.push_back(CannonBall(b.x, b.y, b.z, ball1.return_zaxis(), 1, ball1)) ; 
            ship_cooldown_timer = 30 ; 
        } 
    } 

    if(se_cooldown_timer == 0 && se.size() != 0)
    {
        bounding_box_t b = se[0].get_bounding_box() ; 
        cannonball.push_back(CannonBall(b.x, b.y, b.z, ball1.return_zaxis(), 1, ball1)) ; 
        se_cooldown_timer = 100 ; 
    }

    if(ship_cooldown_timer > 0)
        ship_cooldown_timer-- ; 

    if(se_cooldown_timer > 0)
        se_cooldown_timer-- ; 

    for(int i = 0 ; i < bomb.size() ; ++i)
    {
        bomb[i].tick() ; 
        for(int j = 0 ; j < ship.size() ; ++j)
        {
            if(detect_collision(bomb[i].get_bounding_box(), ship[j].get_bounding_box()))
            {
                bomb.erase(bomb.begin() + i) ; 
                ship.erase(ship.begin() + j) ;  
                score+=500 ;     
            }
        }

        if(detect_collision(bomb[i].get_bounding_box(), se[0].get_bounding_box()))
        {
                bomb.erase(bomb.begin() + i) ; 
                se[0].dec_life() ; 
                if(se[0].get_lives() == 0){
                    se.erase(se.begin()) ;  
                    score+=1000 ; 
                }
        }

        if(abs((int)bomb[i].return_x()) >= 750 || (int)bomb[i].return_y()<=-120 || abs((int)bomb[i].return_z()) >= 750)
        {
            bomb.erase(bomb.begin()+i) ; 
        }
    }

    for(int i = 0 ; i <parachute.size() ; ++i)
    {
         parachute[i].tick(); 
         if(parachute[i].return_y() <= -175)
            parachute.erase(parachute.begin()+i) ;
    }   

    for(int i = 0 ; i <se.size() ; ++i)
    {
        se[i].tick() ; 
    }

    if(bomb_cooldown_timer > 0)
        bomb_cooldown_timer-- ; 
}

void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, 0, COLOR_RED);
    sea         = Sea(50,-100, 50,COLOR_SEA) ;
    compass     = Compass(0,0,0) ; 
    for(int i = 0 ; i < 10 ; i++)
        volcano.push_back(Volcano(i * 35, -70,-100 - i* 30, COLOR_GREEN)) ; 

    for(int i = 0 ; i < 20 ; ++i)
    {
        ring.push_back(Ring(-250 + rand()%500, -20 + rand()%40, -250 + rand()%500, COLOR_GOLD)) ; 
        fuel.push_back(Fuel(-250 + rand()%500, -20 + rand() % 40, -250 + rand()%500, COLOR_RED ))  ; 
    }    

    // checkpoint.push_back(Checkpoint(-5 , 15, -20, COLOR_RED )) ; 
    checkpoint.push_back(Checkpoint(-5 , 15, -400, COLOR_RED )) ; 
    checkpoint.push_back(Checkpoint(-100 , 15, -200, COLOR_RED )) ; 
    checkpoint.push_back(Checkpoint(250 , 15, 400, COLOR_RED )) ; 
    checkpoint.push_back(Checkpoint(-250 , 15, 400, COLOR_RED )) ; 

    ship.push_back(Ship(-5, -95, -400, COLOR_GREEN)) ;
    ship.push_back(Ship(-100, -95, -200, COLOR_GREEN)) ;
    ship.push_back(Ship(250, -95, 400, COLOR_GREEN)) ; 
    ship.push_back(Ship(-250, -95, 400, COLOR_GREEN)) ;

    se.push_back(SpecialEnemy(0, 10, 0, COLOR_GREEN )) ; 

    for(int i = 0 ; i < 6 ; ++i)
    {
        altitude.push_back(Dashboard(2+i/4,2,-1,COLOR_GREEN)) ;
        lives.push_back(Dashboard(2+i/4,2,-1, COLOR_GREEN)) ; 
        speed.push_back(Dashboard(2+i/4,2,-1, COLOR_GREEN)) ; 
        fuel_remaining.push_back(Dashboard(2+i/4,2,-1, COLOR_GREEN)) ; 
        scoreboard.push_back(Dashboard(2+i/4,2,-1, COLOR_GREEN)) ; 
    }; 

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_SKY.r / 256.0, COLOR_SKY.g / 256.0, COLOR_SKY.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void init_parachutes(){
    if(rand()%150==0){
        parachute.push_back(Parachute(-500+rand()%500,30+rand()%60,-500+rand()%500)) ; 
    }
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    glfwSetCursorPosCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouseButton);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            tick_elements();        

            // draw random parachutes
            init_parachutes() ; 
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            

            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(far/screen_zoom), 16.0f/9.0f, near, far);
}

