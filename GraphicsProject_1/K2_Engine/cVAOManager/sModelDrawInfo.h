#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

// Structure representing vertex data
struct sVertex
{
    float x, y, z, w;  // Position (x, y, z, w)
    float r, g, b, a;  // Color (red, green, blue, alpha)
    float nx, ny, nz, nw;  // Normal vector (x, y, z, w)
};

// Structure representing drawing information for a model
struct sModelDrawInfo
{
    sModelDrawInfo();

    std::string meshFileName; // File name of the mesh
    std::string friendlyName; // A friendly name for the model

    unsigned int VAO_ID;  // Vertex Array Object ID

    unsigned int VertexBufferID;  // Vertex Buffer Object ID
    unsigned int VertexBuffer_Start_Index;  // Start index in the vertex buffer
    unsigned int numberOfVertices;  // Number of vertices

    unsigned int IndexBufferID;  // Index Buffer Object ID
    unsigned int IndexBuffer_Start_Index;  // Start index in the index buffer
    unsigned int numberOfIndices;  // Number of indices
    unsigned int numberOfTriangles; // Number of triangles

    unsigned int* pIndices; // Pointer to the index buffer
    float maxExtent;  // Maximum extent of the model

    sVertex* pVertices; // Pointer to the vertex buffer

    glm::vec3 maxExtents_XYZ;  // Maximum extents in XYZ dimensions
    glm::vec3 minExtents_XYZ;  // Minimum extents in XYZ dimensions
    glm::vec3 deltaExtents_XYZ;  // Change in extents in XYZ dimensions

    // Calculates the extents (bounding box) of the model based on its vertices
    void calcExtents(void);

    // Gets the unique ID of the model draw information
    unsigned int getUniqueID(void);

private:

    unsigned int m_UniqueID; // Unique ID of the model draw information
    static const unsigned int FIRST_UNIQUE_ID = 1;
    static unsigned int m_nextUniqueID;
};
