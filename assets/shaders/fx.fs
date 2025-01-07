#version 330

#ifdef GL_ES
    precision highp float;
#endif

// Sampler settings
uniform sampler2D texture0;
in vec2 fragTexCoord;       
out vec4 finalColor;       

// Parameters - make a pipeline into settings
uniform float curvature;          // curvature strength
uniform float bloomIntensity;     // bloom strength
uniform float glowIntensity;      // glow intensity
uniform float scanlineIntensity;  // scanline intensity
uniform float brightness;         // brightness
uniform vec2 resolution; // texture resolution

// CRT scanlines effect
float scanlines(vec2 uv) {
    float scan = sin(uv.y * resolution.y * 3.0) * scanlineIntensity;
    return scan;
}

// CRT curvature effect
vec2 crtCurvature(vec2 uv) {
    vec2 centered = uv * 2.0 - 1.0;
    centered *= 1.0 + curvature * (dot(centered, centered));
    return (centered + 1.0) * 0.5;
}

// Chromatic aberration effect
vec3 chromaticAberration(vec2 uv) {
    float aberrate = 0.001;
    float r = texture(texture0, uv + vec2(aberrate, 0.0)).r;
    float g = texture(texture0, uv).g;
    float b = texture(texture0, uv - vec2(aberrate, 0.0)).b;
    return vec3(r, g, b);
}

// Phosphor glow effect
vec3 phosphorGlow(vec3 color) {
    return color + glowIntensity * color;
}

void main(void) {
    vec2 curvedUV = crtCurvature(fragTexCoord);
    if (curvedUV.x < 0.0 || curvedUV.x > 1.0 || curvedUV.y < 0.0 || curvedUV.y > 1.0) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        vec3 color = chromaticAberration(curvedUV);
        color = phosphorGlow(color);
        float lines = scanlines(curvedUV);
        color *= (1.0 + lines);
        finalColor = vec4(color * brightness, 1.0);
    }
}
