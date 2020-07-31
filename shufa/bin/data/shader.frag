uniform sampler2DRect canvas;
uniform sampler2DRect wetness;

void main()
{
  vec2 pos = gl_FragCoord.xy;
  vec3 colorcanvas = texture2DRect(canvas, pos).rgb;
  vec3 colorwetness = texture2DRect(wetness, pos).rgb;
  
  
  vec4 final;
  
  // use wetness matrix and fill in colors
  if (colorwetness.r > 0.) {
  
    // look at neighbors
    float px = 1.;
    vec2 n = vec2(pos.x, pos.y + px);
    vec3 c_n = texture2DRect(canvas, n).rgb;

    vec2 e = vec2(pos.x + px, pos.y);
    vec3 c_e = texture2DRect(canvas, e).rgb;

    vec2 s = vec2(pos.x, pos.y - px);
    vec3 c_s = texture2DRect(canvas, s).rgb;

    vec2 w = vec2(pos.x - px, pos.y);
    vec3 c_w = texture2DRect(canvas, w).rgb;
    
    float c_max = min(colorcanvas.r, min(c_n.r, min(c_w.r, min(c_e.r, c_s.r))));
    
    final = vec4(c_max, c_max, c_max, 1.);
  } else {
    final = vec4(colorcanvas, 1.);
  }
  
  if (final.r > .5) {
    final.a = 0.;
  }
  
  gl_FragColor = final;
}
