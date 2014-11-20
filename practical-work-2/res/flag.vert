const float M_PI = 3.14159265358979323846;

uniform float deltaTime;
uniform float wind;

const float heightMultiplier = 0.5;
const float offsetMultiplier = 0.5;

void main() {
	float angle = heightMultiplier * gl_MultiTexCoord0.s * wind;
	float offset = offsetMultiplier * deltaTime * wind;

	vec4 newVertex = vec4(gl_Vertex.x, gl_Vertex.y + sin(mod(angle + offset, 2.0 * M_PI)), gl_Vertex.z, 1.0);
	
	gl_Position = gl_ModelViewProjectionMatrix * newVertex;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
