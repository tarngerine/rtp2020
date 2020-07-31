uniform sampler2DRect wetness;
uniform sampler2DRect stamp;
uniform float w;

void main()
{
  vec2 pos = gl_FragCoord.xy;
//  pos.y = w - pos.y;
  vec3 rgbwetness = texture2DRect(wetness, pos).rgb;
  float astamp = texture2DRect(stamp, pos).a;
  
  if (astamp > 0.) {
    rgbwetness.r = rgbwetness.r + .01;
  }

  gl_FragColor = vec4(rgbwetness, 1.);
}
