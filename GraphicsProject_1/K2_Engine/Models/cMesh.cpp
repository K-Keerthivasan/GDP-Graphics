#include "cMesh.h"
#include <iostream>

unsigned int cMesh::m_nextUniqueID = cMesh::FIRST_UNIQUE_ID;

// Constructor for cMesh
cMesh::cMesh()
{
	// Initialize default values for various properties
	this->drawPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->drawOrientation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->setRotationFromEuler(glm::vec3(0.0f, 0.0f, 0.0f));
	this->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->drawScale = glm::vec3(1.0f);

	this->bIsWireframe = false;
	this->bDoNotLight = false;
	this->bIsVisible = true;
	this->bUseDebugColours = false;

	// Assign a unique identifier to the mesh and increment the next available ID
	this->m_UniqueID = cMesh::m_nextUniqueID;

	cMesh::m_nextUniqueID++;
}

// Destructor for cMesh
cMesh::~cMesh()
{
	// Cleanup or deallocate resources, if necessary
}

// Get the unique identifier of the mesh
unsigned int cMesh::getUniqueID(void)
{
	return this->m_UniqueID;
}

// Set a uniform scale for drawing the mesh
void cMesh::setUniformDrawScale(float scale)
{
	this->drawScale.x = this->drawScale.y = this->drawScale.z = scale;
	return;
}

// Get the position used for drawing the mesh
glm::vec3 cMesh::getDrawPosition(void)
{
	return this->drawPosition;
}

// Set the position used for drawing the mesh
void cMesh::setDrawPosition(const glm::vec3& newPosition)
{
	this->drawPosition = newPosition;
	return;
}

// Get the orientation used for drawing the mesh
glm::vec3 cMesh::getDrawOrientation(void)
{
	return glm::eulerAngles(this->get_qOrientation());
}

// Set the orientation used for drawing the mesh using Euler angles
void cMesh::setDrawOrientation(const glm::vec3& newOrientation)
{
	this->setRotationFromEuler(newOrientation);
	return;
}

// Set the orientation used for drawing the mesh using a quaternion
void cMesh::setDrawOrientation(const glm::quat& newOrientation)
{
	this->m_qOrientation = newOrientation;
	return;
}
