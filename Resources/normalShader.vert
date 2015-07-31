
attribute vec2 a_position;
attribute vec4 a_color;
attribute vec2 a_coord;

varying vec4 v_fragmentColor;
varying vec2 v_coord;
varying vec2 v_position;

void main()
{
    gl_Position = CC_MVPMatrix * vec4(a_position.xy,0,1);
    
    v_fragmentColor = a_color;
    v_coord = a_coord;
    v_position = a_position;
}