#version 100
precision mediump float;

varying vec2 TexCoord;

uniform sampler2D screenTexture;

void main() {
  vec2 flippedUV = vec2(1.0 - TexCoord.x, TexCoord.y); // flip X
  gl_FragColor = texture2D(screenTexture, flippedUV);
}
