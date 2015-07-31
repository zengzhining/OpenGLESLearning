varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
  
uniform sampler2D u_texture1;

void main()
{
	vec4 color = texture2D(CC_Texture0, v_texCoord);
	color.a = texture2D(u_texture1, v_texCoord).r;

    gl_FragColor = color;
}