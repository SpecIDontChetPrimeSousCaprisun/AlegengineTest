#version 100
precision mediump float;

varying vec2 TexCoord;

uniform float alpha;
uniform sampler2D tex;
uniform vec3 color;
uniform bool useColor;

void main() {
  if (useColor) {
    gl_FragColor = vec4(
      color.rgb,
      alpha
    );
  }
}
