#version 100
precision mediump float;

varying vec2 TexCoord;

uniform sampler2D tex;
uniform vec3 color;
uniform vec3 colorChange;
uniform vec2 maskPos;
uniform vec2 maskSize;
uniform vec2 resolution;
uniform float transparency;
uniform bool hasMask;

void main() {
  if (hasMask) {
    float fragY = resolution.y - gl_FragCoord.y; // flip to top-left origin

    if (!(gl_FragCoord.x > maskPos.x &&
          gl_FragCoord.x < maskPos.x + maskSize.x &&
          fragY > maskPos.y &&
          fragY < maskPos.y + maskSize.y)) {
      discard;
    }
  }

  float textAlpha = texture2D(tex, TexCoord).a;
  gl_FragColor = vec4(color + colorChange, textAlpha - transparency);
}
