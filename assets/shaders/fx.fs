#version 330

#ifdef GL_ES
    precision highp float;
#endif

// Sampler settings
uniform sampler2D texture0;
in vec2 fragTexCoord;       
out vec4 finalColor;       

// Parameters - make a pipeline into settings
const float curvature = 0.07;          // curvature strength
const float bloomIntensity = 2.5;     // bloom strength
const float scanlineIntensity = 1;  // scanline intensity
const float brightness = 1.4;         // brightness
const vec2 resolution = vec2(1920.0, 1080.0); //texture resolution

// mapping curvature
vec2 applyCurvature(vec2 uv) {
    uv = uv * 2.0 - 1.0; 
    uv.x *= 1.0 + curvature * (uv.y * uv.y);
    uv.y *= 1.0 + curvature * (uv.x * uv.x);
    return (uv + 1.0) * 0.5; 
}

// bloom apply
vec4 applyBloom(vec2 uv) {
    vec4 color = vec4(0.0);
    vec2 texelSize = 1.0 / resolution;


    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            color += texture(texture0, uv + vec2(x, y) * texelSize);
        }
    }
    color /= 9.0;  
    color *= bloomIntensity;
    
    return color;
}

// scanlines function
vec4 applyScanlines(vec2 uv) {
    float scanline = sin(uv.y * resolution.y * 3.0) * scanlineIntensity;
    return vec4(vec3(scanline), 1.0);
}

// fake subpixels rgb
vec4 applyRGBGrid(vec2 uv, vec4 color) {
    float rgbFactor = mod(gl_FragCoord.x, 3.0); 
    if (rgbFactor < 1.0) color.rgb *= vec3(1.0, 0.7, 0.7); 
    else if (rgbFactor < 2.0) color.rgb *= vec3(0.7, 1.0, 0.7); 
    else color.rgb *= vec3(0.7, 0.7, 1.0); 
    return color;
}

void main(void) {
    vec2 curvedUV = applyCurvature(fragTexCoord);
    if (curvedUV.x < 0.0 || curvedUV.x > 1.0 || curvedUV.y < 0.0 || curvedUV.y > 1.0) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        vec4 baseColor = texture(texture0, curvedUV);
        vec4 bloomColor = applyBloom(curvedUV);
        baseColor *= applyScanlines(curvedUV);
        baseColor = applyRGBGrid(fragTexCoord, baseColor);
        finalColor = baseColor * vec4(vec3(brightness), 1.0) + bloomColor * 0.5;
    }
}
