#ifndef spotLight_h
#define spotLight_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class SpotLight {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float k_c;
    float k_l;
    float k_q;
    int lightNumber;

    SpotLight(float posX, float posY, float posZ, float ambR, float ambG, float ambB, float diffR, float diffG, float diffB, float specR, float specG, float specB, float dirX, float dirY, float dirZ, float cuOff, float outerCuOff, float constant, float linear, float quadratic, int num)
    {
        position = glm::vec3(posX, posY, posZ);
        ambient = glm::vec3(ambR, ambG, ambB);
        diffuse = glm::vec3(diffR, diffG, diffB);
        specular = glm::vec3(specR, specG, specB);

        direction = glm::vec3(dirX, dirY, dirZ);
        cutOff = cuOff;
        outerCutOff = outerCuOff;

        k_c = constant;
        k_l = linear;
        k_q = quadratic;
        lightNumber = num;
    }

    void setUpLight(Shader& lightingShader)
    {
        lightingShader.use();
        lightingShader.setVec3("spotLight.ambient", ambient * ambientOn * isOn);
        lightingShader.setVec3("spotLight.diffuse", diffuse * diffuseOn * isOn);
        lightingShader.setVec3("spotLight.specular", specular * specularOn * isOn);
        lightingShader.setVec3("spotLight.position", position);
        lightingShader.setVec3("spotLight.direction", direction);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));
        lightingShader.setFloat("spotLight.k_c", k_c);
        lightingShader.setFloat("spotLight.k_l", k_l);
        lightingShader.setFloat("spotLight.k_q", k_q);
    }

    void turnOff()
    {
        isOn = 0.0;
    }
    void turnOn()
    {
        isOn = 1.0;
    }
    void turnAmbientOn()
    {
        ambientOn = 1.0;
    }
    void turnAmbientOff()
    {
        ambientOn = 0.0;
    }
    void turnDiffuseOn()
    {
        diffuseOn = 1.0;
    }
    void turnDiffuseOff()
    {
        diffuseOn = 0.0;
    }
    void turnSpecularOn()
    {
        specularOn = 1.0;
    }
    void turnSpecularOff()
    {
        specularOn = 0.0;
    }

private:
    float ambientOn = 1.0;
    float diffuseOn = 1.0;
    float specularOn = 1.0;
    float isOn = 1.0;
};

#endif /* spotLight_h */