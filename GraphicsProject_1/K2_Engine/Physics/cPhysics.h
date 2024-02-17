#ifndef _cPhysics_HG_
#define _cPhysics_HG_

#include "sPhysicsProperties.h"
#include "../Models/cMesh.h"
#include "../cVAOManager/cVAOManager.h"	
#include <vector>

class cPhysics
{
public:

	cPhysics();

	~cPhysics();

	void setVAOManager(cVAOManager* pTheMeshManager);

	void AddShape(sPhysicsProperties* pNewShape);

	void Update(double deltaTime);

	sPhysicsProperties* findShapeByUniqueID(unsigned int uniqueIDtoFind);

	sPhysicsProperties* findShapeByFriendlyName(std::string friendlyNameToFind);

	/*std::vector<sPhysicsProperties*> findShapesByType(sPhysicsProperties::eShape shapeType);

	bool findShapesByType(sPhysicsProperties::eShape shapeType, std::vector<sPhysicsProperties*>& vecShapes);*/

	bool rayCast(glm::vec3 startXYZ, glm::vec3 endXYZ, std::vector<sPhysicsProperties*>& vecObjectsHit);

	void CheckForCollision(cVAOManager * modelVAO, std::string filename, sModelDrawInfo* drawInfo, glm::vec3 spherePosition, float sphereRadius, cMesh* groundMesh, sPhysicsProperties* spherePhysicalProps);

private:

	cVAOManager* m_pMeshManager = NULL;

	std::vector< sPhysicsProperties* > m_vec_pPhysicalProps;

	//bool m_Sphere_Sphere_IntersectionTest(sPhysicsProperties* pSphereA, sPhysicsProperties* pShpereB);
	//bool m_Sphere_Plane_IntersectionTest(sPhysicsProperties* pSphere, sPhysicsProperties* pPlane);
	//bool m_Sphere_Triangle_IntersectionTest(sPhysicsProperties* pSphere, sPhysicsProperties* pTriangle);
	//bool m_Sphere_AABB_IntersectionTest(sPhysicsProperties* pSphere, sPhysicsProperties* pAABB);
	//bool m_Sphere_Capsule_IntersectionTest(sPhysicsProperties* pSphere, sPhysicsProperties* pCapsule);
	//bool m_Sphere_TriMeshIndirect_IntersectionTest(sPhysicsProperties* pSphere, sPhysicsProperties* pTriMesh);
	//bool m_Sphere_TriMeshLocal_IntersectionTest(sPhysicsProperties* pSphere, sPhysicsProperties* pTriMesh);
	
	glm::vec3 m_ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

	struct sCollisionEvent
	{
		sPhysicsProperties* pObjectA;		
		sPhysicsProperties* pObjectB;		
		glm::vec3 contactPoint;
		glm::vec3 velocityAtCollision;
		glm::vec3 reflectionNormal;
	};

	std::vector< sCollisionEvent > m_vecCollisionsThisFrame;
};

#endif 