#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

//uniform float time;
uniform sampler2D mySampler;

void main(){

	vec4 textureColor = texture(mySampler, fragmentUV);
	color = fragmentColor * textureColor;
	//color = vec4(fragmentColor.r,
		//		 fragmentColor.g, 
			//	 fragmentColor.b,
				// fragmentColor.a * (sin(time * (fragmentPosition.x - 25) * (fragmentPosition.x - 25)) + 1.0) * 0.5) * textureColor;
}