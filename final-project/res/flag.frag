const float M_PI = 3.14159265358979323846;

uniform sampler2D texture;

uniform float deltaTime;
uniform float wind;

const float heightMultiplier = 0.5;
const float offsetMultiplier = 0.5;
const float contrast = 0.3;

void main() {
	float angle = heightMultiplier * gl_TexCoord[0].s * wind;
	float offset = offsetMultiplier * deltaTime * wind;
	float value = contrast * cos(mod(angle + offset, 2.0 * M_PI));

	gl_FragColor = texture2D(texture, gl_TexCoord[0].st, 0.2);
	gl_FragColor.r += value;
	gl_FragColor.g += value;
	gl_FragColor.b += value;
}
