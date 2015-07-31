
varying vec4 v_fragmentColor;
varying vec2 v_coord;

uniform vec4 u_color;

uniform vec3 u_lightPosition;
uniform vec3 u_lightColor;

varying vec2 v_normal;
varying vec2 v_position;

void main()
{
    vec3 light = u_lightPosition - vec3(v_position,1.0);
    light = normalize(light);
    
    float brightness = clamp(dot(light, vec3(v_normal,0.0)) / length(light) * length(v_normal), 0.0,1.0);
    
    gl_FragColor = brightness * vec4(u_lightColor,1.0) * v_fragmentColor * texture2D(CC_Texture0,v_coord);
}