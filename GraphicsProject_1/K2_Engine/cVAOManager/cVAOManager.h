#ifndef _cVAOManager_HG_
#define _cVAOManager_HG_

#include <string>
#include <map>
#include "sModelDrawInfo.h"

class cVAOManager
{
public:
    // Loads a model file into a Vertex Array Object (VAO) and associates it with a shader program.
    bool LoadModelIntoVAO(std::string friendlyName, std::string fileName, sModelDrawInfo& drawInfo,
        unsigned int shaderProgramID, bool bIsDynamicBuffer = false);

    // Finds and retrieves the draw information for a model based on its filename.
    bool FindDrawInfoByModelName(std::string filename, sModelDrawInfo& drawInfo);

    // Gets the last error message, and optionally clears it.
    std::string getLastError(bool bAndClear = true);

    // Sets the base path for loading model files.
    void setBasePath(std::string basePathWithoutSlash);

    // Updates the VAO buffers for an existing model.
    bool UpdateVAOBuffers(std::string fileName, sModelDrawInfo& updatedDrawInfo, unsigned int shaderProgramID);

private:
    // Loads model data from a PLY file and populates the 'sModelDrawInfo' structure.
    bool m_LoadTheFile_Ply_XYZ_N_RGBA(std::string theFileName, sModelDrawInfo& drawInfo);

    std::map<std::string, sModelDrawInfo> m_map_ModelName_to_VAOID; // Map for model VAOs.

    std::string m_basePathWithoutSlash; // Base path for model file loading.
};

#endif
