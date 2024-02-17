// Vertex shader
#version 420

//uniform mat4 MVP;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matModel;			// Later...
uniform mat4 matModel_IT;		// Inverse transpose of the model matrix

//uniform vec3 modelScale;
//uniform vec3 modelOffset;

uniform bool bUseHeightMap;
uniform sampler2D heightMapSampler;		
uniform float heightScale;

in vec4 vCol;		// was vec3
in vec4 vPos;		// was vec3
in vec4 vNormal;	// NEW for 2023!
in vec2 vTexCoord;

out vec4 colour;
out vec4 vertexWorldPos;	
out vec4 vertexWorldNormal;
out vec2 texCoord;

void main()
{
	
//	gl_Position = MVP * vec4(finalPos, 1.0);
//	gl_Position = MVP * vertModelPosition;
	vec4 vertexModelPosition = vPos;	
			

	if ( bUseHeightMap )
	{
		// Greyscale (black and white) heightmap image
		float height = texture( heightMapSampler, vTexCoord.st ).r;		
		vertexModelPosition.y += ( height * heightScale );
	}

	mat4 matMVP = matProjection * matView * matModel;
	gl_Position = matMVP * vec4(vertexModelPosition.xyz, 1.0);
		
	// Rotate the normal by the inverse transpose of the model matrix
	// (so that it only is impacted by the rotation, not translation or scale)
	vertexWorldNormal = matModel_IT * vec4(vNormal.xyz, 1.0f);
	vertexWorldNormal.xyz = normalize(vertexWorldNormal.xyz);
	vertexWorldNormal.w = 1.0f;
	
	vertexWorldPos = matModel * vec4(vertexModelPosition.xyz, 1.0);
	
	colour = vCol;
	texCoord = vTexCoord;
}
