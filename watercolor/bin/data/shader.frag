uniform sampler2DRect canvas;
uniform sampler2DRect wetness;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
  vec2 pos = gl_FragCoord.xy;
//  pos.y = 800. - pos.y;
  vec3 color = texture2DRect(canvas, pos).rgb;
  
  gl_FragColor = vec4(color, 1.);
  
  // if i have a 1 channel texture
  // how do i access the value for that?
//  vec3 n = texture2DRect(wetness,vec2(pos.x, pos.y + 1./800.)).rgb;
//  n = rgb2hsv(n);
//
//  if (n.z > 0.) {
//    n = hsv2rgb(n);
//    gl_FragColor = vec4(n, 1.0);
//  } else {
//    gl_FragColor = vec4(0.,0.,0., 0.);
//  }
}
