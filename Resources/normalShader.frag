
varying vec4 v_fragmentColor;
varying vec2 v_coord;

uniform vec4 u_color;

varying vec2 v_position;

void main()
{
    
    
    gl_FragColor =  v_fragmentColor * u_color * texture2D(CC_Texture0,v_coord);
}