varying vec2 v_texCoord;

uniform float u_number;

void main()
{
	vec4 vol = vec4(0,0,0,0);

	vec2 textureCoord = v_texCoord;

	vec4 vol_tex = texture2D(CC_Texture0, v_texCoord);

	float I = dot(vol_tex, vec4(0.3, 0.6, 0.2, 0));
	float a = vol_tex.w;
	vec4 vol_grey = vec4(I, I, I, a);

	if ( textureCoord.y < u_number  && textureCoord.x < u_number)
	{
		vol_tex = vol_grey;
	}

	gl_FragColor = vol_tex;

}