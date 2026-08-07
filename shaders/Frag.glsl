#version 100
precision mediump float;

varying vec2 TexCoord;

#define MAX_LIGHTS 16

uniform vec2 lightPositions[MAX_LIGHTS];
uniform vec3 lightColors[MAX_LIGHTS];
uniform float lightRadii[MAX_LIGHTS];
uniform float lightIntensities[MAX_LIGHTS];
uniform int lightCount;

uniform vec2 objectWorldPos;
uniform vec2 objectWorldSize;
uniform vec2 objectSize;
uniform float alpha;
uniform float baseLight;
uniform float cornerRadius;
uniform sampler2D tex;
uniform vec3 color;
uniform vec3 colorChange;
uniform vec2 maskPos;
uniform vec2 maskSize;
uniform vec2 resolution;
uniform bool useColor;
uniform bool hasMask;
uniform bool affectedByLight;
uniform bool flipH;
uniform bool flipV;

void main() {
  vec2 pixelPos = TexCoord * objectSize;
  float r = cornerRadius;

  if (r > 0.0) {
    bool inCorner = false;
    vec2 corner;

    // top-left
    if (pixelPos.x < r && pixelPos.y < r) {
      corner = vec2(r, r);
      inCorner = true;
    }
    // top-right
    else if (pixelPos.x > objectSize.x - r &&
            pixelPos.y < r) {
      corner = vec2(objectSize.x - r, r);
      inCorner = true;
    }
    // bottom-left
    else if (pixelPos.x < r &&
            pixelPos.y > objectSize.y - r) {
      corner = vec2(r, objectSize.y - r);
      inCorner = true;
    }
    // bottom-right
    else if (pixelPos.x > objectSize.x - r &&
            pixelPos.y > objectSize.y - r) {
      corner = vec2(objectSize.x - r,
                    objectSize.y - r);
      inCorner = true;
    }

    if (inCorner && distance(pixelPos, corner) > r)
      discard;
  }

  vec4 finalColor;

  if (hasMask) {
    float fragY = resolution.y - gl_FragCoord.y; // flip to top-left origin

    if (!(gl_FragCoord.x > maskPos.x &&
          gl_FragCoord.x < maskPos.x + maskSize.x &&
          fragY > maskPos.y &&
          fragY < maskPos.y + maskSize.y)) {
      discard;
    }
  }

  vec3 totalLight = vec3(baseLight);

  if (useColor) {
    finalColor = vec4(color, alpha);
  } else {
    vec2 flipedCoords = TexCoord;
    flipedCoords = flipH ? vec2(1.0 - flipedCoords.x, flipedCoords.y) : flipedCoords;
    flipedCoords = flipV ? vec2(flipedCoords.x, 1.0 - flipedCoords.y) : flipedCoords;
    finalColor = texture2D(tex, flipedCoords);
  }
  
  if (affectedByLight) {
    vec2 fragWorldPos = objectWorldPos + TexCoord * objectWorldSize;

    for (int i = 0; i < lightCount; i++) {
      float dist = distance(fragWorldPos, lightPositions[i]);

      // attenuation: light fades to 0 at the radius
      float attenuation = clamp(1.0 - (dist / lightRadii[i]), 0.0, 1.0);
      attenuation = attenuation * attenuation; // square it for a nicer falloff

      totalLight += lightColors[i] * lightIntensities[i] * attenuation;
    }

    finalColor = finalColor * vec4(totalLight, 1.0);
  }

  gl_FragColor = vec4(finalColor.rgb + colorChange.rgb, finalColor.a);
}
