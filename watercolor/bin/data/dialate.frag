uniform sampler2DRect wetness;
uniform float w;

void main()
{
  vec2 pos = gl_FragCoord.xy;
//  pos.y = w - pos.y;
  vec3 rgbwetness = texture2DRect(wetness, pos).rgb;
  
  // look at neighbors
  float px = 1.;
  vec2 n = vec2(pos.x, pos.y + px);
  vec3 wet_n = texture2DRect(wetness, n).rgb;

  vec2 e = vec2(pos.x + px, pos.y);
  vec3 wet_e = texture2DRect(wetness, e).rgb;

  vec2 s = vec2(pos.x, pos.y - px);
  vec3 wet_s = texture2DRect(wetness, s).rgb;

  vec2 w = vec2(pos.x - px, pos.y);
  vec3 wet_w = texture2DRect(wetness, w).rgb;

  if (wet_n.r > 0. ||
      wet_e.r > 0. ||
      wet_s.r > 0. ||
      wet_w.r > 0.) {
    rgbwetness.r = max(rgbwetness.r, max(wet_n.r, max(wet_e.r, max(wet_s.r, wet_w.r))));
  }
  gl_FragColor = vec4(rgbwetness, 1.);
}
