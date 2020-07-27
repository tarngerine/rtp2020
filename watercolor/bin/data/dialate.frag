uniform sampler2DRect wetness;
uniform float w;
uniform float rnd;
uniform float t;

float rand(vec2 pos){
    return fract(sin(pos.x + pos.y * 700. + t * .8) * 43758.5453);
}

void main()
{
  vec2 pos = gl_FragCoord.xy;
//  pos.y = w - pos.y;
  vec3 rgbwetness = texture2DRect(wetness, pos).rgb;
  
  bool go = rand(pos) > .1;
  
  // look at neighbors
  float px = 1.;
  vec2 stp = vec2(pos.x, pos.y + px);
  vec3 wet_n = texture2DRect(wetness, stp).rgb;
  
  stp = vec2(pos.x + px, pos.y + px);
  vec3 wet_ne = texture2DRect(wetness, stp).rgb;

  stp = vec2(pos.x + px, pos.y);
  vec3 wet_e = texture2DRect(wetness, stp).rgb;
  
  stp = vec2(pos.x + px, pos.y - px);
  vec3 wet_se = texture2DRect(wetness, stp).rgb;

  stp = vec2(pos.x, pos.y - px);
  vec3 wet_s = texture2DRect(wetness, stp).rgb;
  
  stp = vec2(pos.x - px, pos.y - px);
  vec3 wet_sw = texture2DRect(wetness, stp).rgb;

  stp = vec2(pos.x - px, pos.y);
  vec3 wet_w = texture2DRect(wetness, stp).rgb;
  
  stp = vec2(pos.x - px, pos.y + px);
  vec3 wet_nw = texture2DRect(wetness, stp).rgb;

  if ((wet_n.r > 0. ||
      wet_ne.r > 0. ||
      wet_e.r > 0. ||
      wet_se.r > 0. ||
      wet_s.r > 0. ||
      wet_sw.r > 0. ||
      wet_w.r > 0. ||
      wet_nw.r > 0.) && go) {
    rgbwetness.r = max(rgbwetness.r, max(wet_n.r, max(wet_ne.r, max(wet_e.r, max(wet_se.r, max(wet_s.r, max(wet_sw.r, max(wet_w.r, wet_nw.r))))))));
  }
  gl_FragColor = vec4(rgbwetness, 1.);
}
