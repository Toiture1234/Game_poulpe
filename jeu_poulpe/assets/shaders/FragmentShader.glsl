uniform sampler2D texture;
uniform vec2 offset;
uniform vec2 w_resolution;

void main()
{
    // lookup the pixel in the texture
    vec2 uv = gl_TexCoord[0].xy;
    uv += offset * vec2(1., -1.);
    uv -= 0.5;
    uv.x *= w_resolution.x / w_resolution.y;

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    float darkening = length(uv - vec2(0., -0.15));
    darkening = smoothstep(0.9, 0., darkening);
    pixel.rgb *= darkening;

    // light
    float light = 0.01 / length(uv - vec2(0.05, -0.1));
    pixel.rgb += light * vec3(1., 0.4, 0.1);
    
    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}