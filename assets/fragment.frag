#version 300 es
precision highp float;
out vec4 fragColor;
in vec4 color;
in vec3 normal;
in vec2 texCoord;
in vec2 texCoordShadow;
in vec4 fragPos;
uniform sampler2D theTexture;
uniform sampler2D shadowTex;
uniform vec3 sunRayDirn;
uniform bool isWater;
uniform vec3 viewPos;
void main()
{
    vec4 fragColorTemp = 0.6*texture(theTexture,texCoord)*texture(shadowTex,texCoordShadow);
    float specularWeight = 0.6;
    vec3 viewdir = normalize(viewPos-fragPos.xyz);
    float spec = 0.0;
    if(isWater)
    {
        fragColorTemp = color;
        vec3 refl = normalize(sunRayDirn-2.0*(dot(sunRayDirn,normal))*normal);
        spec = pow(max(dot(viewdir,refl),0.0),20.0);
        //sun reflection "jugaad"
        refl = normalize(sunRayDirn-2.0*(dot(sunRayDirn,vec3(0.0,1.0,0.0)))*vec3(0.0,1.0,0.0));
        spec+=2.0*pow(max(dot(viewdir,refl),0.0),80.0);
    }
    vec4 specular = specularWeight*spec*vec4(1.0,1.0,1.0,1.0);
    float ambient = 0.1;
    vec3 norm = normalize(normal);
    float diffuse = 0.8*max(dot(norm,-sunRayDirn),0.0);
    vec3 result = (ambient+diffuse)*fragColorTemp.xyz+specular.xyz;
    fragColor = vec4(result,fragColorTemp.a+specular.a);
}