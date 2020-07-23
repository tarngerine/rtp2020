uniform float time;
uniform vec2 mouse;
uniform sampler2DRect img;
uniform sampler2DRect line;

void main()
{
  vec2 pos = gl_FragCoord.xy;
  pos.y = 768. - pos.y;
  float dist = distance(pos, mouse);
  
  vec2 pixelPos = pos;
  
//  pixelPos.x += 400. * sin(pos.x/200. + time);
//  pixelPos.y += 400. * sin(pos.y/200. + time);
//  pixelPos.x = mod(pixelPos.x, 400.);
//  pixelPos.x += 80. * sin(time + sin(pixelPos.x*.01));

  
  // offset color
//  vec3 color = texture2DRect(img, pixelPos).rgb;
//
//  float r = color.r;
//  pixelPos.x += 30. * sin(r*10. + time);
//  pixelPos.y += 30. * cos(r*10. + time);
//
//  vec3 color2 = texture2DRect(img, pixelPos).rgb;
//
//
//  color2.b += 10. * sin(time + sin(pixelPos.x));
  
  vec3 colorImg = texture2DRect(img, pixelPos).rgb;
  float r = colorImg.r;
  float g = colorImg.g;
  
  pixelPos.x += (r*sin(time)) *  500.;
  pixelPos.y += (g*sin(time)) *  500.;
  
  vec3 colorLine = texture2DRect(line, pixelPos).rgb;
    
  gl_FragColor = vec4(colorLine, 1.0);
  
  // offset pixels via distance from mouse
//  gl_FragColor = vec4(vec3(sin(dist*.01 - time)*.5*.5),1.);
}
