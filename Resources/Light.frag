varying vec4 v_fragmentColor;
varying vec2 v_coord;
varying vec2 v_normal;
varying vec2 v_position;

uniform vec2 u_lightPosition;
uniform vec2 u_winSize;
void main()
{
    vec2 lightPosition = vec2(1.0 ,1.0 );

    lightPosition.x = u_lightPosition.x - v_position.x;
    lightPosition.y = u_lightPosition.y - v_position.y;

    float brightness = 1- 1.5 * (length(lightPosition)/length(u_winSize));

    vec4 brightnessVec = vec4(brightness, brightness, brightness, 1.0);
    gl_FragColor = brightnessVec* v_fragmentColor * texture2D(CC_Texture0,v_coord);
}