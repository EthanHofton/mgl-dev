#version 410

out vec4 fragColor;

in VSOUT {
    vec4 i_col;
} vsin;

void main() 
{
    fragColor = vsin.i_col;
}