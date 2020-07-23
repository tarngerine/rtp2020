uniform sampler2DRect canvas;
uniform sampler2DRect wetness;

void main()
{
  vec2 pos = gl_FragCoord.xy;
//  pos.y = 800. - pos.y;
  vec3 color = texture2DRect(canvas, pos).rgb;
  
//  gl_FragColor = vec4(color, 1.);
  
  vec2 n = vec2(pos.x, pos.y - 1./800.);
  vec3 wet_n = texture2DRect(wetness, n).rgb;
  vec3 color_n = texture2DRect(canvas, n).rgb;

  if (wet_n.r > 0.) {
    gl_FragColor = vec4(color_n, 1.0);
    gl_FragColor = vec4(1.,0.,0., 1.0);
  } else {
    gl_FragColor = vec4(color, 1.);
  }
}
