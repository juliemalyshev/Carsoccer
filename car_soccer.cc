/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"
#include <chrono>
#include <ctime>


float thrust = 0;
float turnRate = 0;
float speed = 0;
float drag = 0;
float updateSpeed = 0;
float distance = 0;
clock_t time_req;
float car_time;
bool flag = false;

CarSoccer::CarSoccer() : GraphicsApp(1024, 768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;
    
    if (IsKeyDown(GLFW_KEY_LEFT))
        dir[0] -= 0.5;
        
        
    if (IsKeyDown(GLFW_KEY_RIGHT))
        dir[0] += 0.5;
     

    if (IsKeyDown(GLFW_KEY_UP))
        dir[1]-=0.5;
        distance += dir[1];
     
    if (IsKeyDown(GLFW_KEY_DOWN))
        dir[1]+=0.5;

        

        
    return dir;
}

void CarSoccer::launch_ball() {

    Vector3 randVel = Vector3((rand() % 30 + (-15)) * 2, (rand() % 10 + 1) * 2, (rand() % 30 + (-15)) * 2);
    ball_.set_velocity(randVel);

}
void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {

    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        ball_.Reset();
        launch_ball();

    }

}



void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.

    float epsilon = 0.01;
    Vector2 dir = joystick_direction();


    if (IsKeyDown(GLFW_KEY_UP)) {
        if (flag == false) {
            
            time_req = clock();
        }
        thrust++;
        speed = 100 * ((-1 * distance) / (time_req));
        drag = speed;
        updateSpeed = 0.00001 * (thrust - drag) * time_req;

        flag = true;

    }
    if (!IsKeyDown(GLFW_KEY_UP)) {
        if (flag == true) {
            time_req = clock() - time_req;

            distance = 0;
            car_time = 0;

        }
        speed = 0;
        flag = false;
    }

    //updating speed
    
    dir[1] -= speed;
    Point3 carPos1 = Point3(car_.position().x() + dir[0], car_.collision_radius(), car_.position().z());
    car_.set_position(carPos1);

    Point3 carPos2 = Point3(car_.position().x(), car_.collision_radius(), car_.position().z() + dir[1]);
    car_.set_position(carPos2);





    //bouncing the ball

    Vector3 newVel = Vector3(ball_.velocity() + gravity * timeStep * 5);
    ball_.set_velocity(newVel);
    Point3 newPos = Point3(ball_.position() + (ball_.velocity() * timeStep));
    ball_.set_position(newPos);

    //ball on the ground

    if ((ball_.position().y() - ball_.radius()) <= 0) {
        if (ball_.position().y() <= 0) {
            ball_.set_position(Point3(ball_.position().x(), ball_.radius() + epsilon, ball_.position().z()));
        }
        float amount = (ball_.radius()) - ball_.position().y();
        Point3 corrected = ball_.position() + amount * -((ball_.velocity()).ToUnit());
        ball_.set_position(corrected);
        newVel = newVel - (2.5 * (newVel.Dot(Vector3::UnitY())) * Vector3::UnitY());
        if (newVel.Length() > 20) {
            newVel = 0.6 * newVel;

        }


        ball_.set_velocity(newVel);
        Point3 newPos = Point3(ball_.position() + (ball_.velocity() * (timeStep*1000)));
    }
    ball_.set_position(newPos);

    //If ball hits ceiling

    if ((ball_.position().y() + ball_.radius()) >= 35) {
        Point3 corrected = ball_.position() - ((-((ball_.velocity()).ToUnit())) * ((ball_.radius()) - ball_.position().y() - epsilon));
        ball_.set_position(corrected);
        newVel = newVel - (2 * (newVel.Dot(Vector3::UnitY())) * Vector3::UnitY());
        if (newVel.Length() > 20) {
            newVel = 0.6 * newVel;
        }
        ball_.set_velocity(newVel);
        Point3 newPos = Point3(ball_.position() + (ball_.velocity() * timeStep*1000));
    }
    ball_.set_position(newPos);

    // Right Side
    if ((ball_.position().x() + ball_.radius()) >= 40) {
        Point3 corrected = ball_.position() - ((-((ball_.velocity()).ToUnit())) * ((ball_.radius()) - ball_.position().x() - epsilon));
        ball_.set_position(corrected);
        newVel = newVel - (2.5 * (newVel.Dot(Vector3::UnitX())) * Vector3::UnitX());
        if (newVel.Length() > 20) {
            newVel = 0.6 * newVel;
        }
        ball_.set_velocity(newVel);
        Point3 newPos = Point3(ball_.position() + (ball_.velocity() * timeStep*1000));
    }
    ball_.set_position(newPos);

    //Left Side
    if ((ball_.position().x() - ball_.radius()) <= -40) {
        Point3 corrected = ball_.position() + ((-((ball_.velocity()).ToUnit())) * ((ball_.radius()) + ball_.position().x() + epsilon));
        ball_.set_position(corrected);
        newVel = newVel - (2.5 * (newVel.Dot(Vector3::UnitX())) * Vector3::UnitX());
        if (newVel.Length() > 20) {
            newVel = newVel * 0.6;
        }
        ball_.set_velocity(newVel);
        Point3 newPos = Point3(ball_.position() + (ball_.velocity() * (timeStep * 1000)));
        
    }
    ball_.set_position(newPos);

    //our goal wall
    if ((ball_.position().z() + ball_.radius()) >= 50) {
        Point3 corrected = ball_.position() - ((-((ball_.velocity()).ToUnit())) * ((ball_.radius()) - ball_.position().z() - epsilon));
        ball_.set_position(corrected);
        //Vector3 normalVector = newVel.x;
        newVel = newVel - (2.5 * (newVel.Dot(Vector3::UnitZ())) * Vector3::UnitZ());
        if (newVel.Length() > 20) {
            newVel = 0.6 * newVel;
        }
        ball_.set_velocity(newVel);
        Point3 newPos = Point3(ball_.position() + (ball_.velocity() * (timeStep*1000)));
    }
    ball_.set_position(newPos);


    //their goal wall
    if ((ball_.position().z() - ball_.radius()) <= -50) {
        Point3 corrected = ball_.position() + ((-((ball_.velocity()).ToUnit())) * ((ball_.radius()) + ball_.position().z() + epsilon));
        ball_.set_position(corrected);
        newVel = newVel - (2.5 * (newVel.Dot(Vector3::UnitZ())) * Vector3::UnitZ());
        if (newVel.Length() > 20) {
            newVel = 0.6 * newVel;
        }
        ball_.set_velocity(newVel);
        Point3 newPos = Point3(ball_.position() + (ball_.velocity() * (timeStep *100)));
    }
    ball_.set_position(newPos);

    

    // Make sure car doesnt go out of bounds
    if ((car_.position().x() - car_.collision_radius()) <= -40) {
        float amount = (-40 + car_.collision_radius()) - car_.position().x();
        Point3 corrected = car_.position() + amount * car_.size().ToUnit();
        car_.set_position(corrected);
    }
    if ((car_.position().x() + car_.collision_radius()) >= 40) {
        float amount = (40 - car_.collision_radius()) - car_.position().x();
        Point3 corrected = car_.position() + amount * car_.size().ToUnit();
        car_.set_position(corrected);
    }
    if ((car_.position().z() + car_.collision_radius()) >= 50) {
        float amount = (50 - car_.collision_radius()) - car_.position().z();
        Point3 corrected = car_.position() + amount * car_.size().ToUnit();
        car_.set_position(corrected);
    }
    if ((car_.position().z() - car_.collision_radius()) <= -50) {
        float amount = (-50 + car_.collision_radius()) - car_.position().z();
        Point3 corrected = car_.position() + amount * car_.size().ToUnit();
        car_.set_position(corrected);
    }

    //check for collision with goals 
    if ((ball_.position().z() - ball_.radius()) <= -48 && ball_.position().x() >= -10 && ball_.position().x() <= 10 && ball_.position().y() <= 10) {
        ball_.Reset();
        launch_ball();
    }
    if (ball_.position().z() + ball_.radius() >= 48 && ball_.position().x() >= -10 && ball_.position().x() <= 10 && ball_.position().y() <= 10) {
        ball_.Reset();
        launch_ball();
    }

    if (car_.position().z() >= -50 && car_.position().x() > 40) {
        car_.set_position(Point3(40 - car_.collision_radius(), car_.collision_radius(), -50 + car_.collision_radius()));
    }
    if (car_.position().z() <= 50 && car_.position().x() < -40) {
        car_.set_position(Point3(-40 + car_.collision_radius(), car_.collision_radius(), 50 - car_.collision_radius()));
    }
    if (ball_.position().y() - ball_.radius() <= 0) {
        ball_.set_position(Point3(ball_.position().x(), ball_.radius(), ball_.position().z()));
    }
    //std::cout << car_.position() << std::endl;

   

    //check for collision with car
    Vector3 distance = ball_.position() - car_.position();
    if (distance.Length() <= ball_.radius() + car_.collision_radius()) {
        float distanceDesired = ball_.radius() + car_.collision_radius();
        float distanceWhenHit = distance.Length();
        float amountToAdjust = distanceDesired - distanceWhenHit - epsilon;
        std::cout << -(ball_.velocity().ToUnit()) << std::endl;
        Point3 corrected = ball_.position() + (((-(ball_.velocity())).ToUnit()) * (amountToAdjust + epsilon));
        ball_.set_position(corrected);

        //velocity
        Vector3 normal = Vector3::Normalize(distance);
        newVel = ball_.velocity() - (3 * (ball_.velocity().Dot(normal)) * normal);
        ball_.set_velocity(newVel);
    }
}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    viewMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));
 
    // Set a background color for the screen
    glClearColor(0.8,0.8,0.8, 1);
    
    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);
    
    // Draw the field with the field texture on it.
    Color col(16.0/255.0, 46.0/255.0, 9.0/255.0);
    Matrix4 M = Matrix4::Translation(Vector3(0,-0.201,0)) * Matrix4::Scale(Vector3(50, 1, 60));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0,-0.2,0)) * Matrix4::Scale(Vector3(40, 1, 50));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);
    
    // Draw the car
    Color carcol(0.8, 0.2, 0.2);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0,0,0)) *
        Matrix4::RotationY(car_.angle()) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);
    
    
    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);
    
    
    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2,0.4,0.15);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);
    
    //Drawing bottom and top loop of the field
    Matrix4 m_loop;
    std::vector<Point3> loop;
    loop.push_back(Point3(40.0, 35.0, -50.0));
    loop.push_back(Point3(-40.0, 35.0, -50.0));
    loop.push_back(Point3(-40.0, 35.0, 50.0));
    loop.push_back(Point3(40.0, 35.0, 50.0));

    
    quickShapes_.DrawLines(m_loop, viewMatrix_, projMatrix_, Color(1, 1, 1), loop, QuickShapes::LinesType::LINE_LOOP, 0.1);

    Matrix4 bottom_loop;
    std::vector<Point3> bottom_loop_vec;
    bottom_loop_vec.push_back(Point3(40.0, 0.0, -50.0));
    bottom_loop_vec.push_back(Point3(-40.0, 0.0, -50.0));
    bottom_loop_vec.push_back(Point3(-40.0, 0.0, 50.0));
    bottom_loop_vec.push_back(Point3(40.0, 0.0, 50.0));
    
    quickShapes_.DrawLines(bottom_loop, viewMatrix_, projMatrix_, Color(1, 1, 1), bottom_loop_vec, QuickShapes::LinesType::LINE_LOOP, 0.1);

    //Drawing all of the other lines on the field
    std::vector<Point3> points;
    points.push_back(Point3(40.0, 0.0, 0.0));
    points.push_back(Point3(40.0, 35.0, 0.0));
    points.push_back(Point3(-40.0, 0.0, 0.0));
    points.push_back(Point3(-40.0, 35.0, 0.0));

    points.push_back(Point3(-40.0, 0.0, 50.0));
    points.push_back(Point3(-40.0, 35.0, 50.0));

    points.push_back(Point3(-40.0, 0.0, -50.0));
    points.push_back(Point3(-40.0, 35.0, -50.0));

    points.push_back(Point3(40.0, 0.0, -50.0));
    points.push_back(Point3(40.0, 35.0, -50.0));

    points.push_back(Point3(40.0, 0.0, 50.0));
    points.push_back(Point3(40.0, 35.0, 50.0));

    points.push_back(Point3(-40.0, 0.0, 0.0));
    points.push_back(Point3(40.0, 0.0, 0.0));

    quickShapes_.DrawLines(modelMatrix_,viewMatrix_, projMatrix_, Color(1, 1, 1), points , QuickShapes::LinesType::LINES, 0.1);

    //Drawing boundary of goal 
    Matrix4 our_goal_loop;
    std::vector<Point3> our_goal_loop_vec;
    our_goal_loop_vec.push_back(Point3(-20.0, 0.0, 50.0));
    our_goal_loop_vec.push_back(Point3(-20.0, 0.0, 35.0));
    our_goal_loop_vec.push_back(Point3(20.0, 0.0, 35.0));
    our_goal_loop_vec.push_back(Point3(20.0, 0.0, 50.0));

    quickShapes_.DrawLines(our_goal_loop, viewMatrix_, projMatrix_, Color(1, 1, 1), our_goal_loop_vec, QuickShapes::LinesType::LINE_LOOP, 0.1);

    Matrix4 their_goal_loop;
    std::vector<Point3> their_goal_loop_vec;
    their_goal_loop_vec.push_back(Point3(-20.0, 0.0, -50.0));
    their_goal_loop_vec.push_back(Point3(-20.0, 0.0, -35.0));
    their_goal_loop_vec.push_back(Point3(20.0, 0.0, -35.0));
    their_goal_loop_vec.push_back(Point3(20.0, 0.0, -50.0));

    quickShapes_.DrawLines(their_goal_loop, viewMatrix_, projMatrix_, Color(1, 1, 1), their_goal_loop_vec, QuickShapes::LinesType::LINE_LOOP, 0.1);

    //Our Goal
    
    std::vector<Point3> our_goal_vec;
    for (int i = 0; i <= 20; i++) {
        our_goal_vec.push_back(Point3(-10.0 + i, 10.0, 50.0));
        our_goal_vec.push_back(Point3(-10.0 + i, 0.0, 50.0));
    }
    for (int i = 0; i < 10; i++) {
        our_goal_vec.push_back(Point3(-10.0, 10.0-i , 50.0));
        our_goal_vec.push_back(Point3(10.0, 10.0 - i, 50.0));
    }
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(1.0, 0.65, 0.0), our_goal_vec, QuickShapes::LinesType::LINES, 0.1);
    
    // Their Goal

    std::vector<Point3> their_goal_vec;
    for (int i = 0; i <= 20; i++) {
        their_goal_vec.push_back(Point3(-10.0 + i, 10.0, -50.0));
        their_goal_vec.push_back(Point3(-10.0 + i, 0.0, -50.0));
    }
    for (int i = 0; i < 10; i++) {
        their_goal_vec.push_back(Point3(-10.0, 10.0 - i, -50.0));
        their_goal_vec.push_back(Point3(10.0, 10.0 - i, -50.0));
    }
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(0.0, 0.0, 1.0), their_goal_vec, QuickShapes::LinesType::LINES, 0.1);

    
}

