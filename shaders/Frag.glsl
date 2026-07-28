#version 100
precision mediump float;

varying vec2 TexCoord;

uniform float alpha;
uniform sampler2D tex;
uniform vec3 color;
uniform vec3 colorChange;
uniform vec2 maskPos;
uniform vec2 maskSize;
uniform vec2 resolution;
uniform bool useColor;
uniform bool hasMask;

void main() {
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

  if (useColor) {
    finalColor = vec4(color, alpha);
  } else {
    finalColor = texture2D(tex, TexCoord);
  }

  gl_FragColor = vec4(finalColor.rgb + colorChange.rgb, finalColor.a);
}
