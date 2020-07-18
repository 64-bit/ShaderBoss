#version 330 core
//layout (location = 0) in vec3 aPos;

varying vec2 uv;

uniform vec4 vectorType;
uniform float floatType;

void main()
{
    gl_FragColor = vectorType * floatType + vec4(uv.xy,0.0,1.0);
}