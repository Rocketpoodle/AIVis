#version 440

layout(location = 0) in vec2 coord;
layout(location = 0) out vec4 fragColor;

layout(std140, binding =0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    vec4 monoColor;
};
layout(binding = 1) uniform sampler2D source;

void main(void)
{
    vec4 p = texture(source, coord);
    float g = dot(p.rgb, vec3(0.33, 0.5, 0.17));
    fragColor = vec4(monoColor.rgb, p.a) * qt_Opacity;// * qt_Opacity * g;
}
