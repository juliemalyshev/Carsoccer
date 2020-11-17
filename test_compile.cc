#include <iostream>


#include <dev\MinGfx\src\mingfx.h>
using namespace mingfx;


using namespace std;

int main()
{
    Matrix4 doorToSiding = Matrix4::Translation(Vector3(0.5, -0.2, 0.0));
    
    Matrix4 sidingToHouse = Matrix4::Translation(Vector3(0.0, 0.5, 0.0));

    Matrix4 houseToWorld = Matrix4::Translation(Vector3(-1.0, 0.0, 0.0));

    Point3 pInDoorSpace = Point3(0.2, 0.4, 0.0);

    // Combined transformation from Door-Space -> World-Space
    Matrix4 doorSpaceToWorldSpace = houseToWorld * sidingToHouse * doorToSiding;

    // The point `p` in world space
    Point3 pInWorldSpace = doorSpaceToWorldSpace * pInDoorSpace;

    std::cout << "p in World-Space: " << pInWorldSpace << std::endl;
    
    return 0;
}
