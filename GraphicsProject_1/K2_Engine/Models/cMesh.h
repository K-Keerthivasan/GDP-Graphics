#ifndef _cMesh_HG_
#define _cMesh_HG_

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>

#include "../Physics/iPhysicsMeshTransformAccess.h"

class cMesh : public iPhysicsMeshTransformAccess
{
private:
	glm::quat m_qOrientation;               // Quaternion for orientation
	unsigned int m_UniqueID;                // Unique identifier for the mesh
	static const unsigned int FIRST_UNIQUE_ID = 1000;  // Starting value for unique IDs
	static unsigned int m_nextUniqueID;     // Next available unique ID

public:
	cMesh();                                // Constructor
	~cMesh();                               // Destructor

	std::string meshName;                   // Name of the mesh

	std::string friendlyName;               // Friendly name for the mesh

	glm::vec3 drawPosition;                 // Position for drawing the mesh

	glm::vec3 drawOrientation;              // Orientation for drawing the mesh

	glm::vec4 wholeObjectDebugColourRGBA;   // Debug color for the entire object

	std::vector<cMesh*> vec_pChildMeshes;   // List of child meshes

	bool bIsVisible;                       // Flag indicating if the mesh is visible

	bool bIsWireframe;                     // Flag indicating if the mesh should be rendered in wireframe mode

	bool bDoNotLight;                      // Flag indicating if the mesh should not be affected by lighting

	bool bUseDebugColours;                 // Flag indicating if debug colors should be used for rendering

	


	void setRotationFromEuler(glm::vec3 newEulerAngleXYZ)
	{
		this->m_qOrientation = glm::quat(newEulerAngleXYZ);
	}

	void adjustRotationAngleFromEuler(glm::vec3 EulerAngleXYZ_Adjust)
	{
		glm::quat qChange = glm::quat(EulerAngleXYZ_Adjust);
		this->m_qOrientation *= qChange;
	}

	glm::quat get_qOrientation(void)
	{
		return this->m_qOrientation;
	}

	glm::vec3 drawScale;                    // Scale for drawing the mesh
	void setUniformDrawScale(float scale);

	virtual glm::vec3 getDrawPosition(void);           // Get the drawing position
	virtual glm::vec3 getDrawOrientation(void);        // Get the drawing orientation

	virtual void setDrawPosition(const glm::vec3& newPosition);  // Set the drawing position
	virtual void setDrawOrientation(const glm::vec3& newOrientation);  // Set the drawing orientation
	virtual void setDrawOrientation(const glm::quat& newOrientation);  // Set the drawing orientation using a quaternion

	
	
	unsigned int getUniqueID(void);        // Get the unique identifier for the mesh

};

#endif
