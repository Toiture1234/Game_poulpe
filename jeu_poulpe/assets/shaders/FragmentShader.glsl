uniform sampler2D texture;
uniform vec2 playerPosition;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}