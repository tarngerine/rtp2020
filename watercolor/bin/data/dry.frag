uniform sampler2DRect wetness;
uniform float w;

void main()
{
  vec2 pos = gl_FragCoord.xy;
  pos.y = w - pos.y;
  vec3 rgb = texture2DRect(wetness, pos).rgb;
  
  rgb.r = rgb.r - .005;

  gl_FragColor = vec4(rgb, 1.);
}
