#version 400

layout(vertices = 4) out;
in float edgeDiv[];
uniform float tessDiv;

void main(void)
{
    gl_TessLevelOuter[0] = tessDiv * edgeDiv[3];
    gl_TessLevelOuter[1] = tessDiv * edgeDiv[0];
    gl_TessLevelOuter[2] = tessDiv * edgeDiv[1];
    gl_TessLevelOuter[3] = tessDiv * edgeDiv[2];
	
	gl_TessLevelInner[0] = tessDiv; //(gl_TessLevelOuter[1] + gl_TessLevelOuter[3])/2.0;
    gl_TessLevelInner[1] = tessDiv; //(gl_TessLevelOuter[0] + gl_TessLevelOuter[2])/2.0;
	
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}