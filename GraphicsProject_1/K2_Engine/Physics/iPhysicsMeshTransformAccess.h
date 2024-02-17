#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

// This is an interface class for accessing and modifying the position and orientation of a physics mesh.
class iPhysicsMeshTransformAccess
{
public:
    virtual ~iPhysicsMeshTransformAccess() {};

    // Get the current 3D position of the physics mesh in the world.
    virtual glm::vec3 getDrawPosition(void) = 0;

    // Get the current 3D orientation (rotation) of the physics mesh in the world.
    virtual glm::vec3 getDrawOrientation(void) = 0;

    // Set the 3D position of the physics mesh to a new position specified by 'newPosition'.
    virtual void setDrawPosition(const glm::vec3& newPosition) = 0;

    // Set the 3D orientation (rotation) of the physics mesh to a new orientation specified by 'newOrientation'.
    virtual void setDrawOrientation(const glm::vec3& newOrientation) = 0;

    // Set the orientation (rotation) of the physics mesh to a new orientation specified by 'newOrientation', represented as a quaternion.
    virtual void setDrawOrientation(const glm::quat& newOrientation) = 0;
};
