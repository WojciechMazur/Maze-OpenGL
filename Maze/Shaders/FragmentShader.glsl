#version 430 core

layout(location = 0) out vec4 out_color;
 
uniform sampler2D nebulaTex1;			
uniform sampler2D nebulaTex2;		
uniform sampler2D nebulaTex3;		
uniform sampler2D alphaChanTex;
uniform sampler2D rampTex;		
uniform float     timer;

in vec2 texcoord;
 
void main()
{
	float offset = timer*0.0001;

	vec4 firstColor	  = texture (nebulaTex3,   vec2(texcoord.x + offset * 0.5, texcoord.y)*1.8);
	vec4 secondColor = texture (nebulaTex1,   vec2(texcoord.x, texcoord.y - offset) * 1.5);
    vec4 thirdColor  = texture (nebulaTex2,   vec2(texcoord.x, texcoord.y - offset));
     
    vec4 aChanColor  = texture (alphaChanTex, vec2(texcoord.x, texcoord.y - offset));
    vec4 rampColor   = texture (rampTex,      vec2(texcoord.x, texcoord.y - offset) * 1.75); 

	vec4 particleColor = vec4(thirdColor.r, thirdColor.g, thirdColor.b, aChanColor.r);
 
    out_color = (firstColor * secondColor * 2) * particleColor * 2 * rampColor; 
}
