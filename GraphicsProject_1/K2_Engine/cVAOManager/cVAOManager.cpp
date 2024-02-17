#include "cVAOManager.h"

#include "../OpenGLCommon.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <vector>
#include <sstream>
#include <fstream>


// Set the base path for loading model files.

void cVAOManager::setBasePath(std::string basePathWithoutSlash)
{
    this->m_basePathWithoutSlash = basePathWithoutSlash;
    return;
}
// Load a model file into a Vertex Array Object (VAO) and associate it with a shader program.

bool cVAOManager::LoadModelIntoVAO(std::string friendlyName, std::string fileName, sModelDrawInfo& drawInfo, unsigned int shaderProgramID, bool bIsDynamicBuffer)
{
    drawInfo.meshFileName = fileName;

    drawInfo.friendlyName = friendlyName;

    std::string fileAndPath = this->m_basePathWithoutSlash + "/" + fileName;

    if (!this->m_LoadTheFile_Ply_XYZ_N_RGBA(fileAndPath, drawInfo))
    {
        return false;
    };

    glGenVertexArrays(1, &(drawInfo.VAO_ID));

    glBindVertexArray(drawInfo.VAO_ID);

    glGenBuffers(1, &(drawInfo.VertexBufferID));

    glBindBuffer(GL_ARRAY_BUFFER, drawInfo.VertexBufferID);

    glBufferData(GL_ARRAY_BUFFER,
        sizeof(sVertex) * drawInfo.numberOfVertices,
        (GLvoid*)drawInfo.pVertices,
        (bIsDynamicBuffer ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));

    glGenBuffers(1, &(drawInfo.IndexBufferID));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawInfo.IndexBufferID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * drawInfo.numberOfIndices,
        (GLvoid*)drawInfo.pIndices,
        GL_STATIC_DRAW);

    GLint vpos_location = glGetAttribLocation(shaderProgramID, "vPos");
    GLint vcol_location = glGetAttribLocation(shaderProgramID, "vCol");
    GLint vNormal_location = glGetAttribLocation(shaderProgramID, "vNormal");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 4, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, x));

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 4, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, r));

    glEnableVertexAttribArray(vNormal_location);
    glVertexAttribPointer(vNormal_location, 4, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, nx));

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(vpos_location);
    glDisableVertexAttribArray(vcol_location);
    glDisableVertexAttribArray(vNormal_location);

    this->m_map_ModelName_to_VAOID[drawInfo.meshFileName] = drawInfo;

    return true;
}

// Find and retrieve the draw information for a model based on its filename.
bool cVAOManager::FindDrawInfoByModelName(std::string filename, sModelDrawInfo& drawInfo)
{
    std::map< std::string, sModelDrawInfo>::iterator itDrawInfo = this->m_map_ModelName_to_VAOID.find(filename);

    if (itDrawInfo == this->m_map_ModelName_to_VAOID.end())
        return false;

    drawInfo = itDrawInfo->second;
    return true;
}

// Load model data from a PLY file and populate the 'sModelDrawInfo' structure.
bool cVAOManager::m_LoadTheFile_Ply_XYZ_N_RGBA(std::string theFileName, sModelDrawInfo& drawInfo)
{
    std::ifstream modelFile(theFileName.c_str());

    if (!modelFile.is_open())
        return false;

    std::string temp;

    while (modelFile >> temp)
    {
        if (temp == "vertex")
            break;
    };

    modelFile >> drawInfo.numberOfVertices;

    while (modelFile >> temp)
    {
        if (temp == "face")
            break;
    };

    modelFile >> drawInfo.numberOfTriangles;

    drawInfo.numberOfIndices = drawInfo.numberOfTriangles * 3;

    while (modelFile >> temp)
    {
        if (temp == "end_header")
            break;
    };

    struct sVertexPlyFile
    {
        float x;
        float y;
        float z;
        float nx, ny, nz;
        float r, g, b, a;
    };

    struct sTrianglePlyFile
    {
        unsigned int v0, v1, v2;
    };

    sVertexPlyFile* pTheVerticesFile = new sVertexPlyFile[drawInfo.numberOfVertices];

    for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
    {
        sVertexPlyFile tempVertex;
        modelFile >> tempVertex.x;
        modelFile >> tempVertex.y;
        modelFile >> tempVertex.z;

        modelFile >> tempVertex.nx;
        modelFile >> tempVertex.ny;
        modelFile >> tempVertex.nz;

        modelFile >> tempVertex.r;       tempVertex.r /= 255.0f;
        modelFile >> tempVertex.g;       tempVertex.g /= 255.0f;
        modelFile >> tempVertex.b;       tempVertex.b /= 255.0f;
        modelFile >> tempVertex.a;       tempVertex.a /= 255.0f;


        pTheVerticesFile[index] = tempVertex;
    }

    sTrianglePlyFile* pTheTriangles = new sTrianglePlyFile[drawInfo.numberOfTriangles];

    for (unsigned int index = 0; index != drawInfo.numberOfTriangles; index++)
    {
        sTrianglePlyFile tempTriangle;

        unsigned int discard;
        modelFile >> discard;
        modelFile >> tempTriangle.v0;
        modelFile >> tempTriangle.v1;
        modelFile >> tempTriangle.v2;

        pTheTriangles[index] = tempTriangle;
    }

    drawInfo.pVertices = new sVertex[drawInfo.numberOfVertices];
    for (unsigned int vertIndex = 0; vertIndex != drawInfo.numberOfVertices; vertIndex++)
    {
        drawInfo.pVertices[vertIndex].x = pTheVerticesFile[vertIndex].x;
        drawInfo.pVertices[vertIndex].y = pTheVerticesFile[vertIndex].y;
        drawInfo.pVertices[vertIndex].z = pTheVerticesFile[vertIndex].z;
        drawInfo.pVertices[vertIndex].w = 1.0f;


        drawInfo.pVertices[vertIndex].nx = pTheVerticesFile[vertIndex].nx;
        drawInfo.pVertices[vertIndex].ny = pTheVerticesFile[vertIndex].ny;
        drawInfo.pVertices[vertIndex].nz = pTheVerticesFile[vertIndex].nz;
        drawInfo.pVertices[vertIndex].nw = 1.0f;

        drawInfo.pVertices[vertIndex].r = pTheVerticesFile[vertIndex].r;
        drawInfo.pVertices[vertIndex].g = pTheVerticesFile[vertIndex].g;
        drawInfo.pVertices[vertIndex].b = pTheVerticesFile[vertIndex].b;
        drawInfo.pVertices[vertIndex].a = pTheVerticesFile[vertIndex].a;
    }

    drawInfo.pIndices = new unsigned int[drawInfo.numberOfIndices];

    unsigned int elementIndex = 0;

    for (unsigned int triIndex = 0; triIndex != drawInfo.numberOfTriangles; triIndex++)
    {
        drawInfo.pIndices[elementIndex + 0] = pTheTriangles[triIndex].v0;
        drawInfo.pIndices[elementIndex + 1] = pTheTriangles[triIndex].v1;
        drawInfo.pIndices[elementIndex + 2] = pTheTriangles[triIndex].v2;

        elementIndex += 3;
    }

    return true;
}

// Update the VAO buffers for an existing model.
bool cVAOManager::UpdateVAOBuffers(std::string fileName, sModelDrawInfo& updatedDrawInfo, unsigned int shaderProgramID)
{
    sModelDrawInfo updatedDrawInfo_TEMP;

    if (!this->FindDrawInfoByModelName(fileName, updatedDrawInfo_TEMP))
        return false;

    glBindBuffer(GL_ARRAY_BUFFER, updatedDrawInfo.VertexBufferID);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sVertex) * updatedDrawInfo.numberOfVertices, (GLvoid*)updatedDrawInfo.pVertices);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, updatedDrawInfo.IndexBufferID);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * updatedDrawInfo.numberOfIndices, (GLvoid*)updatedDrawInfo.pIndices);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}
