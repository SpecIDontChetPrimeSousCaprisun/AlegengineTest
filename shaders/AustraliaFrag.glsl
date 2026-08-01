#version 100
precision mediump float;

varying vec2 TexCoord;

uniform sampler2D screenTexture;

void main() {
  vec2 flippedUV = vec2(TexCoord.x, 1.0 - TexCoord.y); // flip Y
  gl_FragColor = texture2D(screenTexture, flippedUV);
}
