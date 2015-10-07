varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
varying highp vec2 blurCoordinates[5];
void main()
{
    vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
    lowp vec4 sum = v_orColor*0.5;
    sum += texture2D(CC_Texture0, v_texCoord) * 0.2;
    sum += texture2D(CC_Texture0, v_texCoord) * 0.3;
    sum += texture2D(CC_Texture0, v_texCoord) * 0.4;
    
    gl_FragColor = sum;
}