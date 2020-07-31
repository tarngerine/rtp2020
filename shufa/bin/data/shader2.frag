uniform sampler2DRect wetness;

void main()
{
  vec2 pos = gl_FragCoord.xy;
//  pos.y = 800. - pos.y;
  vec3 color = texture2DRect(wetness, pos).rgb;
  
  gl_FragColor = vec4(color, 1.);
}
