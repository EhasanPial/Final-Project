

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include "sphere.h"
#include "stb_image.h"
#include "curveObject.h"
#include "cube.h"
#include <iostream>
#include <stdlib.h>
#include<windows.h>  

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void Grasses(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void CoffeMachine(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void CafeFoodCounter(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void CafeShop(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Baloon(Shader ourShader, Shader sphereShader, glm::mat4 moveMatrix, glm::vec3 rotationAxis, glm::vec3 ambient, glm::vec4 color, float rotation, Cube cube[]);
void dotdot(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void drawCube(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, float spec, float shininess);
void SpotLightWithCurve(Shader ourShader, Shader lightingShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[], GLfloat reverseCurve[]);
void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void SecondFloorShamne(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void ChotoBlocks(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void TubeLight(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void SquareBati(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Pillars(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube cube[]);
void Table(Shader ourShader, glm::mat4 moveMatrix, float rotation, bool square, Cube cube[]);
void Chair(Shader ourShader, glm::mat4 moveMatrix, float rotation, Cube all_cubes[]);
void RotateChairY(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[]);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float dorja1_rotationY = 0.0f;
float window_translate = 0.8125f;
float rotateAngleTest_Y = 0.0;
float globalBallonRotation = 0.0f;
float globalBallonStep = 3.0f;
bool isglobalBallonOn = 1.0f;
// camera               8.0   1.0   18.1
Camera camera(glm::vec3(8.0f, 1.0f, 18.1f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 2.5;
float lookAtX = 0.0, lookAtY = 1.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


glm::vec3 lightPositions[] = {
		glm::vec3(7.0 + 5, 3.01 - 1, -20 + 0.36),
		glm::vec3(-8.0f, 8.0f, 8.0f),
		glm::vec3(-8.0f, 8.0f, -8.0f),
		glm::vec3(8.0f, 8.0f, -8.0f),
		glm::vec3(15.0, 10.0f, 15.0f),
		glm::vec3(-2.3f, .5f, 4.8f) ,

		glm::vec3(4.30f, 3.0, -5.0f) ,//spotlight1
		glm::vec3(4.30f, 3.0, -5.0f  - 2 ), //spotlight2
		glm::vec3(4.30f , 3.0, -5.0f -  4) //spotlight3
};

glm::vec3 lightDirections[] = {
	glm::vec3(0.4f, -0.2f, 1.0f)
};


PointLight pointLight0(

	lightPositions[0].x, lightPositions[0].y, lightPositions[0].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	1       // light number
);

PointLight pointLight1(

	lightPositions[0].x, lightPositions[0].y, lightPositions[0].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	1       // light number
);

PointLight pointLight2(

	lightPositions[1].x, lightPositions[1].y, lightPositions[1].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	2       // light number
);

PointLight pointLight3(

	lightPositions[2].x, lightPositions[2].y, lightPositions[2].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	3       // light number
);

PointLight pointLight4(

	lightPositions[3].x, lightPositions[3].y, lightPositions[3].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	4       // light number
);

PointLight pointLight5(

	lightPositions[4].x, lightPositions[4].y, lightPositions[4].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	5       // light number
);

DirectionalLight directionalLight(

	-lightPositions[4].x, -lightPositions[4].y, -lightPositions[4].z,  // direction
	0.4f, 0.4f, 0.4f,     // ambient
	0.9f, 0.9f, 0.9f,     // diffuse
	.2f, .2f, 0.2f,        // specular
	1           // light number
);

DirectionalLight directionalLight2(

	lightPositions[4].x, lightPositions[4].y, lightPositions[4].z,  // direction
	0.4f, 0.4f, 0.4f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1           // light number
);

SpotLight spotLight(

	lightPositions[6].x, lightPositions[6].y, lightPositions[6].z,  // position
	1.0f, 1.0f, 1.0f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	0.0, -3.0, 0.0,  // direction
	8.5f,   // cutoff
	15.5f,   // outer cutoff
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	1       // light number
);

SpotLight spotLight2(

	lightPositions[7].x, lightPositions[7].y, lightPositions[7].z,  // position
	1.0f, 1.0f, 1.0f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	0.0, -3.0, 0.0,  // direction
	8.5f,   // cutoff
	15.5f,   // outer cutoff
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	2      // light number
);

SpotLight spotLight3(

	lightPositions[8].x, lightPositions[8].y, lightPositions[8].z,  // position
	1.0f, 1.0f, 1.0f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	0.0, -3.0, 0.0,  // direction
	8.5f,   // cutoff
	15.5f,   // outer cutoff
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	3      // light number
);



// texture
float extra = 4.0f;
float TXmin = 0.0f;
float TXmax = 1.0f + extra;
float TYmin = 0.0f;
float TYmax = 1.0f + extra;



//rotate
bool isRotating = false;
float fanSpeed = 8.0f;

bool lightingOn = true;
float ambientOn = 1.0;
float diffuseOn = 1.0;
float specularOn = 1.0;
bool dark = false;

float directionalLightOn = 1.0;
float pointLightOn = 0.0;
float spotLightOn = 0.0;


// Textures
unsigned int texture0, texture1, redBrickTex, texture3, texture4, tilesTex, texture6, texture7, woodtex, glasstex, tabletex, marbeltex, coffeetex;



int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cafeteria - Pial 1807040", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
	Shader ourShader("vertexShader.vs", "fragmentShader.fs");
	Shader lightingShader("vertexShaderLight.vs", "fragmentShaderLight.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes


	float cube_vertices[] = {
		// positions      // normals         // texture coords
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,
		0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmax,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,

		0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax,
		0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, TXmin, TYmin,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, TXmin, TYmax,

		0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,
		0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
		0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

		0.0f, 0.0f, 0.5f, -1.0f, 0.0f, 0.0f, TXmax, TYmin,
		0.0f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, TXmax, TYmax,
		0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax,
		0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin,

		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
		0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

		0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
		0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
		0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
		0.0f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, TXmin, TYmax
	};
	unsigned int cube_indices[] = {
		0, 3, 2,
		2, 1, 0,

		4, 5, 7,
		7, 6, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};
	GLfloat points[] = {
-1.0250, 0.79, 5.1000,
-1.0250, .50, 5.1000,
0.0000, .50, 5.10
	};

	GLfloat blank[] = {
0.1,0.1,0.1
	};

	GLfloat reverseCurve[]{


-0.9500, 0.3000, 5.1000,
-0.9100, 0.8750, 5.1000,
-0.6950, 1.3700, 5.1000,
-0.3000, 1.7600, 5.1000,
-0.0150, 1.8800, 5.1000,

	};
	unsigned int cubeVAO, cubeVBO, cubeEBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &cubeEBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

	// position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//vertex normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
	glEnableVertexAttribArray(2);

	//light's VAO
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	//ourShader.use();



	// Texture loading

	//Texture 0
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("transparent.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture 0" << endl;
	}
	stbi_image_free(data);



	float testBallon = 0.0;

	string diffuseMapPath;
	string specularMapPath = "";
	// Draw Cubes 
	unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

	diffuseMapPath = "new_grass.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_grass = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "glass.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_glass = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "green-coffee.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_coffee = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "marble.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_marbel = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "pillar.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_pillar = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "table.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_table = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "tiles.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_tiles = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "wood.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_wood = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);


	diffuseMapPath = "transparent.png";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_transparent = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "brickwall_2.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_brick = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	Cube all_cubes[] = { cube_grass , cube_glass , cube_coffee, cube_marbel , cube_pillar, cube_table, cube_tiles, cube_wood, cube_transparent,cube_brick };


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// activate shader
		lightingShaderWithTexture.use();
		glBindVertexArray(cubeVAO);

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
		lightingShaderWithTexture.setMat4("projection", projection);


		////testing rotating around lookat point
		//const float radius = 2.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//glm::mat4 view;
		//view = glm::lookAt(glm::vec3(camX, 1.0, camZ), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		// camera/view transformation
		//glm::mat4 view = basic_camera.createViewMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		lightingShaderWithTexture.setMat4("view", view);


		//**************lighting**************
		lightingShader.use();

		// light shader
		pointLight1.setUpPointLight(lightingShader);
		pointLight2.setUpPointLight(lightingShader);
		pointLight3.setUpPointLight(lightingShader);
		pointLight4.setUpPointLight(lightingShaderWithTexture);
		pointLight5.setUpPointLight(lightingShaderWithTexture);
		directionalLight.setUpLight(lightingShaderWithTexture);
		spotLight.setUpLight(lightingShaderWithTexture);

		

		pointLight0.setUpPointLight(lightingShader);
		directionalLight2.setUpLight(lightingShader);
		spotLight2.setUpLight(lightingShaderWithTexture);

		//lightingShader.use();
		spotLight3.setUpLight(lightingShaderWithTexture);

		lightingShader.use();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		//Setting up Directional Light
		directionalLight.setUpLight(lightingShaderWithTexture);
		if (!directionalLightOn)
			directionalLight.turnOff();
		if (!ambientOn)
			directionalLight.turnAmbientOff();
		if (!diffuseOn)
			directionalLight.turnDiffuseOff();
		if (!specularOn)
			directionalLight.turnSpecularOff();

		//Setting up Point Light
		{
			pointLight1.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight1.turnOff();
			if (!ambientOn)
				pointLight1.turnAmbientOff();
			if (!diffuseOn)
				pointLight1.turnDiffuseOff();
			if (!specularOn)
				pointLight1.turnSpecularOff();

			pointLight2.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight2.turnOff();
			if (!ambientOn)
				pointLight2.turnAmbientOff();
			if (!diffuseOn)
				pointLight2.turnDiffuseOff();
			if (!specularOn)
				pointLight2.turnSpecularOff();

			pointLight3.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight3.turnOff();
			if (!ambientOn)
				pointLight3.turnAmbientOff();
			if (!diffuseOn)
				pointLight3.turnDiffuseOff();
			if (!specularOn)
				pointLight3.turnSpecularOff();

			pointLight4.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight4.turnOff();
			if (!ambientOn)
				pointLight4.turnAmbientOff();
			if (!diffuseOn)
				pointLight4.turnDiffuseOff();
			if (!specularOn)
				pointLight4.turnSpecularOff();

			pointLight5.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight5.turnOff();
			if (!ambientOn)
				pointLight5.turnAmbientOff();
			if (!diffuseOn)
				pointLight5.turnDiffuseOff();
			if (!specularOn)
				pointLight5.turnSpecularOff();
		}


		//Setting up Spot Light
		spotLight.setUpLight(lightingShaderWithTexture);
		spotLight2.setUpLight(lightingShaderWithTexture);
		spotLight3.setUpLight(lightingShaderWithTexture);
		if (!spotLightOn) {
			spotLight.turnOff();
			spotLight2.turnOff();
			spotLight3.turnOff();
		}
			
		if (!ambientOn) {
			spotLight.turnAmbientOff();
			spotLight2.turnAmbientOff();
			spotLight3.turnAmbientOff();
		}
			 
		if (!diffuseOn) {
			spotLight.turnDiffuseOff();
			spotLight2.turnDiffuseOff();
			spotLight3.turnDiffuseOff();
		}
		
		if (!specularOn) {
			spotLight.turnSpecularOff();
			spotLight2.turnSpecularOff();
			spotLight3.turnSpecularOff();
		}
			

		//Setting up Camera and Others
		lightingShaderWithTexture.setVec3("viewPos", camera.Position);
		lightingShaderWithTexture.setBool("lightingOn", lightingOn);
		lightingShaderWithTexture.setFloat("ambientOn", ambientOn);
		lightingShaderWithTexture.setFloat("diffuseOn", diffuseOn);
		lightingShaderWithTexture.setFloat("specularOn", specularOn);
		lightingShaderWithTexture.setFloat("pointLightOn", pointLightOn);
		lightingShaderWithTexture.setFloat("directionalLightOn", directionalLightOn);
		lightingShaderWithTexture.setFloat("spotLightOn", spotLightOn);

		lightingShaderWithTexture.setBool("dark", dark);

		////For axis
		//ourShader.use();
		//glm::mat4 identity = glm::mat4(1.0f); // identity matrix
		//ourShader.setMat4("model", identity);
		//glBindVertexArray(axisVAO);
		//glDrawArrays(GL_LINES, 0, 6);


		// Starting
		glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 translateMatrix;
		glm::vec4 color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	  

		lightingShader.use();
		CurveObj co1;
		co1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		co1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		co1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		co1.translation = glm::vec3(4.2, 0.81, -4.0);
		co1.scale = glm::vec3(0.2f, .5f, 0.2f);
		co1.hollowBezier(points, (sizeof(points) / sizeof(points[0])) / 3 - 1, lightingShader);
		 
		CurveObj batirNiche;
		batirNiche.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		batirNiche.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		batirNiche.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		batirNiche.translation = glm::vec3(4.2, 0.81, -4.0);
		batirNiche.scale = glm::vec3(0.2f, .2f, 0.2f);
		batirNiche.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);
		 
		lightingShader.use();
		CurveObj co2;
		co2.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		co2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		co2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		co2.translation = glm::vec3(4.2, 0.81, -8.0);
		co2.scale = glm::vec3(0.2f, .5f, 0.2f);
		co2.hollowBezier(points, (sizeof(points) / sizeof(points[0])) / 3 - 1, lightingShader);

		CurveObj batirNiche1;
		batirNiche1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		batirNiche1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		batirNiche1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		batirNiche1.translation = glm::vec3(4.2, 0.81, -8.0);
		batirNiche1.scale = glm::vec3(0.2f, .2f, 0.2f);
		batirNiche1.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);
		
		translateMatrix = glm::translate(identityMatrix, glm::vec3(4.2, 1.1, -10.0));
		SquareBati(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		lightingShader.use();
		CurveObj co3;
		co3.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		co3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		co3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		co3.translation = glm::vec3(4.0 + 0.75, 0.9, -19.6);
		co3.scale = glm::vec3(0.04f  , .2f + 0.1,  0.04);
		co3.hollowBezier(points, (sizeof(points) / sizeof(points[0])) / 3 - 1, lightingShader);


		translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 + 0.75, 1.19 , -19.6));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		dotdot(lightingShader, translateMatrix, color1, all_cubes);
		 
		 
		 //4.2, 0.81, -16.0
		////********** Object making ***********
		//lightingShaderWithTexture.use();
		//glActiveTexture(GL_TEXTURE0);
		////Grass
		//translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		//color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		//Grasses(lightingShaderWithTexture, translateMatrix, color1);

		lightingShaderWithTexture.use();

		// Grass

		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Grasses(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		//Floor

		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Floor(lightingShaderWithTexture, translateMatrix, color1, all_cubes);


		float dy = 5.0 - 1.5;
		float dz = -7.3f;
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 3.6, 0.0f + dz));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		SecondFloorShamne(lightingShaderWithTexture, translateMatrix, color1, all_cubes);


		//Pillars
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Pillars(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		//Choto red bricks blocks
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 3.5f + 1.5, -0.2 + 0.05f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);
		//Choto red bricks blocks 2 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5 + 0.5, 3.5f + 1.5, -0.2 + 0.05f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		int dx = 1.8;
		for (int i = 0; i < 4; i++) {
			//Choto red bricks blocks 2 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 + 0.5 * i + dx, 3.5f + 1.5, -0.2 + 0.05f));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);
			dx += 3.0;

		}


		//Choto red bricks blocks
		translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.0, 3.5f + 1.5, -0.2 + 0.05f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		//Choto red bricks blocks 2 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.85 - 3.0, 3.5f + 1.5, -0.2 + 0.05f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		// Corner tables
		float translate_table = 0.0;
		for (int i = 0; i < 4; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 + translate_table, 1.0, -6.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 0.0f, false, all_cubes);
			translate_table += 1.6;


		}
		float translate_chair = -0.2;
		for (int i = 0; i < 10; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 + translate_chair, 1.0, -6.0 + 0.7));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Chair(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);
			translate_chair += 0.6;
		}

		translate_chair = -0.2;
		for (int i = 0; i < 10; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 + 0.6 + translate_chair, 1.0, -6.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
			translate_chair += 0.6;
		}



		translate_table = 0.0;
		for (int i = 0; i < 3; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 - translate_table, 1.0, -10.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 90.0f, true, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4 - .5, 1.0, -10.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Chair(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 0.7 - .5, 1.0, -10.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Chair(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4, 1.0, -10.0 - 1.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 0.7, 1.0, -10.0 - 1.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4 - 1.5, 1.0, -10.0 - 1.5 + .65));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4 - 1.5 + 1.60f, 1.0, -10.0 - 1.5 + 1.1));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

			translate_table += 5.0;
		}




		translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0, 1.0, -5.0));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Table(lightingShaderWithTexture, translateMatrix, 90.0f, true, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 + 4, 1.0, -5.0 - 0.5));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 0.8 + 4, 1.0, -5.0 - 0.5 - 1.2));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4 + 4, 1.0, -5.0 - 0.5 - 1.2));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 1.0 - 0.6 + 4, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4 - 0.6, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);


		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0, 1.0, -5.0));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Table(lightingShaderWithTexture, translateMatrix, 90.0f, true, all_cubes);


		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6, 1.0, -5.0 - 0.5));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 0.8, 1.0, -5.0 - 0.5 - 1.2));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4, 1.0, -5.0 - 0.5 - 1.2));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 1.0 - 0.6, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4 - 0.6, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);

		translate_table = 0.0;
		for (int i = 0; i < 2; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0, 1.0, -16.0 + translate_table));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 90.0f, false, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + 1.0, 1.0, -16.0 + translate_table));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 - 0.5, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 - 0.3, 1.0, -16.0 + translate_table - 0.6 - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);


			translate_table += 1.5;



		}
		translate_table = 0;
		for (int i = 0; i < 2; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0, 1.0, -16.0 + translate_table));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 0.0f, false, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 + 1.0, 1.0, -16.0 + translate_table));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 - 0.5, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 - 0.3, 1.0, -16.0 + translate_table - 0.6 - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);


			translate_table += 1.5;



		}

		translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0, 0.0, 0.0));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		CafeFoodCounter(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		CafeShop(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(9.6, 1.0, -18.7f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		RotateChairY(lightingShaderWithTexture, translateMatrix, 180, all_cubes);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 + 0.60, 0.0, -2));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		CoffeMachine(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		translate_table = 0;
		for (int i = 0; i < 2; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0, 1.0, -16.0 + translate_table));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 90.0f, false, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 + 1.0, 1.0, -16.0 + translate_table));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 - 0.5, 1.0, -16.0 + translate_table - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 - 0.3, 1.0, -16.0 + translate_table - 0.6 - 0.6));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);


			translate_table += 1.5;



		}


		if (isglobalBallonOn) {

			if (globalBallonRotation <= 15 && testBallon != 0.0) {
				globalBallonRotation += 0.1f;
				if (globalBallonRotation >= 15) {
					testBallon = 0.0;
				}
			}
			else {
				globalBallonRotation -= 0.1f;
				if (globalBallonRotation < -15) {
					testBallon = 1.0;
				}
			}



		}

		float translate_ballon = 0.0;
		for (int i = 0; i < 4; i++) {
			CurveObj co;
			co.ambient = glm::vec4(0.6f, 0.9f, 0.6f, 1.0);

			co.hollowBezier(blank, (sizeof(blank) / sizeof(blank[0])) / 3 - 1, lightingShader);
			glm::vec3 ambient1 = glm::vec3(0.0f, 0.9f, 0.0f);
			glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f + translate_ballon, 2.5, -10));
			Baloon(lightingShaderWithTexture, lightingShader, translateMatrix, rotationAxis, ambient1, color1, globalBallonRotation, all_cubes);
			translate_ballon += 7.0;
		}

		lightingShader.use();
		translate_ballon = 0.0;
		for (int i = 0; i < 4; i++) {
			CurveObj co;
			co.ambient = glm::vec4(0.4f, 0.6f, 0.9f, 1.0);

			co.hollowBezier(blank, (sizeof(blank) / sizeof(blank[0])) / 3 - 1, lightingShader);
			glm::vec3 ambient1 = glm::vec3(0.0f, 0.9f, 0.0f); 			glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f + translate_ballon, 2.5, -13));
			Baloon(lightingShaderWithTexture, lightingShader, translateMatrix, rotationAxis, ambient1, color1, globalBallonRotation, all_cubes);
			translate_ballon += 7.0;
		}
		translate_ballon = 0.0;
		for (int i = 0; i < 4; i++) {
			CurveObj co;
			co.ambient = glm::vec4(0.8f, 0.4f, 0.1f, 1.0);

			co.hollowBezier(blank, (sizeof(blank) / sizeof(blank[0])) / 3 - 1, lightingShader);
			glm::vec3 ambient1 = glm::vec3(0.0f, 0.9f, 0.0f);
			glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f + translate_ballon, 2.5, -16));
			Baloon(lightingShaderWithTexture, lightingShader, translateMatrix, rotationAxis, ambient1, color1, globalBallonRotation, all_cubes);
			translate_ballon += 7.0;
		}




		translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0 + 5, 3 - 1, -20 + 0.3));
		TubeLight(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		// point lights 

		  // make sure to initialize matrix to identity matrix first
		lightPositions[0] = glm::vec3(7.0 + 5, 3.01 - 1, -20 + 0.36);
		glm::mat4 model;
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPositions[0]);
		model = glm::scale(model, glm::vec3(2, 0.01, 0.01));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
		all_cubes[1].drawCubeWithTexture(lightingShaderWithTexture, model);



		float spotLightDz = 0.0;
		for (int i = 0; i < 3; i++) {
			
			translateMatrix = glm::translate(identityMatrix, glm::vec3(4.2f, 2.5, -5.0 - spotLightDz));
			SpotLightWithCurve(lightingShaderWithTexture, lightingShader, translateMatrix, color1, all_cubes, reverseCurve);

			CurveObj lightCurve;
			lightCurve.ambient = glm::vec4(0.06, 0.05, 0.08, 1.0);
			lightCurve.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
			lightCurve.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
			lightCurve.translation = glm::vec3(4.2f, 2.5, -5.0f - spotLightDz);
			lightCurve.scale = glm::vec3(0.2f, .2f, 0.2f);
			lightCurve.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);

			spotLightDz += 2.0;
		}






		//    glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &cubeEBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void dotdot(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]){
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateXMatrix, translateToPivot, translateFromPivot;

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0 ));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02, 0.02, .02));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix* model);
}


void Baloon(Shader ourShader, Shader sphereShader, glm::mat4 moveMatrix, glm::vec3 rotationAxis, glm::vec3 ambient, glm::vec4 color, float rotation, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateXMatrix, translateToPivot, translateFromPivot;

	glm::vec3 pivot1 = glm::vec3(0.0f, 1.00, 0.0f);

	// ring
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.0f - 0.05 / 2, -0.01));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 0.05, .05));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	// String
	translateToPivot = glm::translate(identityMatrix, -pivot1);
	translateFromPivot = glm::translate(identityMatrix, pivot1);

	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotation), glm::vec3(rotationAxis));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, -0.01f, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02, 2.0f, .02));
	model = translateFromPivot * rotateXMatrix * translateToPivot * translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	Sphere s1 = Sphere();
	sphereShader.use();
	s1.ambient = ambient;
	s1.diffuse = ambient;
	s1.specular = glm::vec3(.1f, .1f, .1f);
	s1.scale = glm::vec3(.1f, 0.1f, 0.1f);
	s1.drawSphere(sphereShader, moveMatrix, pivot1, translateMatrix,
		translateToPivot, translateFromPivot, rotateXMatrix);


	//ourShader.use();

}


void RotateChairY(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[])
{
	// Create a rotation matrix around the y-axis
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

	// Combine the rotation matrix with the existing transformation matrix
	moveMatrix = moveMatrix * rotationMatrix;

	// Call the Chair function with the updated moveMatrix to draw the chair
	Chair(ourShader, moveMatrix, 0.0, all_cubes);
}

void Grasses(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	//Grass
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 0.1f, 20.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[0].drawCubeWithTexture(ourShader, moveMatrix * model);


}
void CoffeMachine(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {


	// left 
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1 + 0.05, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 1.0f, 1));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//main part 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1 + 0.05 + 0.75 / 2 / 2, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6, 0.75, 1));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	// nozzle 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + 0.15, 1.0f + 0.2, -17.59f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.2, 0.01));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//right thin
	translateMatrix = glm::translate(identityMatrix, glm::vec3(.3f - 0.01 / 2 / 2, 1 + 0.05, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 1.0f, 1));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);
}
void CafeShop(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0, 0.5, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 1.0f, 4.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 2.0, 0.5, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 1.0f, 4.0 - 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	glm::mat4 rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 - 2.5 / 2 + 1.9, 0.5, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 1.0f, 3.0f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);



	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 - 2.5 / 2 + 1.9, 0.5 + 0.5, -18.0 + 0.02f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7, 0.05f, 3.0f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);
}
void CafeFoodCounter(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	// pillars 
	float translate_pillar = 0.0;
	for (int i = 0; i < 3; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1 + 0.05, -20.0f + translate_pillar)); // grass 20 e sesh hoiche
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 5.8f, 0.8f));
		model = translateMatrix * scaleMatrix;
		all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);
		translate_pillar += 8.3;
	}


	//food 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 1.0f, 34.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1, -20.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2, 0.1f, 34.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

}
void SecondFloorShamne(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube cube_tiles[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	float dy = 5.0 - 1.5;
	float dz = -10.3f;

	//dorja er left pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f - 4.5, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.5f, 5.8 + 7, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er left pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.75f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8 + 7, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja
	glm::mat4 rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.86f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.2f, 5.1 + 8, .2f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	cube_tiles[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.5, 1.8 + 8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er right pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f - 0.1, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8 + 8, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er right pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8 + 8, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f + 0.75f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(43.5, 1.8 + 8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);


	float dx = 8.25f;
	float dx_window = 7.5 + 0.75f;
	//dorja er right pillar 2 
	for (int i = 0; i < 4; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx - 0.5, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8 + 8, 1.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);



		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 1.875, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5, 7.5 + 8, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.75, 2 + 8, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 2.5, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5 + 8, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25, 1, -3.0f + 0.05 + 0.5));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25 + window_translate, 1, -3.0f + 0.1 + 0.5));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);

		if (i != 3) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 0.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 1 + 8, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 2.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5 + 8, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);


			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 1, -3.0f + 0.05));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);

			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11 + window_translate, 1, -3.0f + 0.1));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);


		}


		dx += 6.0;
		dx_window += 4.0;

	}
}
void SpotLightWithCurve(Shader ourShader, Shader lightingShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[], GLfloat reverseCurve[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;



	// ring
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.5f + 0.05 / 2, -0.01));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 0.05, .05));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.25f, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02, 2.0f, .03));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);





}
void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube cube_tiles[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//shamner block
	//glBindTexture(GL_TEXTURE_2D, tilesTex);
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 1.0f, 40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[6].drawCubeWithTexture(ourShader, model);



	// shamner block er shirir 1 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 - 7.5, 0.0, 0.0f)); // (0,0,0) ekahnei
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.33f, 1.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[6].drawCubeWithTexture(ourShader, model);

	// shamner block er shirir 2

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 - 7.5, 0.165f, 0.0f)); // (0,0,0) ekahnei , 7.5 hocche 30*0.5 = 15 jeta shirir er X, er half 
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.33f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);



	//Back
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 0.0, -20.0 - 0.2f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 23.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//shamner 1st floor er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5, -0.2f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 3.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//shamner 2nd floor er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 9.0 - 1.5, -0.2f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 3.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//shamner 2nd floor er block er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 9.0 - 1.5, -0.2f - 10.1f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 3.0f, 20.2f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//shamner 2nd floor er block er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(30.0f - 0.5f, 9.0 - 1.5, -0.2f - 10.1f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 3.0f, 20.2f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);


	//ceiling 1st floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 1.0f, -40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//left close
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5 - 3, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 20.0, -40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//up 1st floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5 + 7.5, -0.2f - 1.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 1.0f, -40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);



	//shamner wall 1st floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 7.5, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//dorja er left pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//dorja er left pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.75f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//dorja
	glm::mat4 rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.86f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.2f, 5.1, .2f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	cube_tiles[7].drawCubeWithTexture(ourShader, model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.5, 1.8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//dorja er right pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f - 0.1, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//dorja er right pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f + 0.75f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(43.5, 1.8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	float dx = 8.25f;
	float dx_window = 7.5 + 0.75f;
	//dorja er right pillar 2 
	for (int i = 0; i < 4; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx - 0.5, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8, 1.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, model);



		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 1.875, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5, 7.5, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[4].drawCubeWithTexture(ourShader, model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.75, 2, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 2.5, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25, 1, -3.0f + 0.05));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25 + window_translate, 1, -3.0f + 0.1));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, model);

		if (i != 3) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 0.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 1, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, model);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 2.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, model);


			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 1, -3.0f + 0.05));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, model);

			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11 + window_translate, 1, -3.0f + 0.1));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, model);


		}


		dx += 6.0;
		dx_window += 4.0;

	}







	////shamner wall  2nd floor 
	//translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5, -10.3f));
	//scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 18.0f, 0.4f));
	//model = translateMatrix * scaleMatrix;
	//cube_tiles[4].drawCubeWithTexture(ourShader, model);





}
void ChotoBlocks(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	//shamner 1st floor er choto choto block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.6f, 1.5f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//shamner 1st floor er choto choto block - left 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-.1, 0.0, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);


	//shamner 1st floor er choto choto block - right 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.8, 0.0, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);


	//shamner 1st floor er choto choto block - up 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-.1, 0.74, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, .2f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);

}
void SquareBati(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//back 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.06, 1.0));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0+0.125/2, 0.0, 0.5));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 0.1, 0.06));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0+0.125/2, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 0.1, 0.06));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);
	 


}
void TubeLight(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//back 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 0.06, 0.01));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.06, 0.1));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.06, 0.1));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);


}

void Pillars(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//Left Side shamner Pillar Shirir

	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 - 0.3, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 - 0.3, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, model);




	//right Side shamner Pillar Shirir

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 + 7.5, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 + 7.5, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	//right Side shamner Pillar 1 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.75, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.75, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	//Left Side shamner Pillar 1 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.75, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.75, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

}

void Table(Shader ourShader, glm::mat4 moveMatrix, float rotation, bool square, Cube all_cubes[])
{

	float tableY = 0.05f;
	float squareZ = 1.5f;
	if (square == true) {
		squareZ = 3.0f;
	}
	// Top
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.06f, squareZ));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);


	// Leg 1
	glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.0, -0.5, 0.05));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
	model1 = rotateYMatrix * translateMatrix1 * scaleMatrix1;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model1);


	// Leg 2
	glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(.01f, -0.5, squareZ / 2 - 0.1));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
	model2 = rotateYMatrix * translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);


	// Leg 3
	//glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(1.5 - 0.05, -0.5, 0.05));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
	model1 = rotateYMatrix * translateMatrix1 * scaleMatrix1;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model1);;


	// Leg 4
	//glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.5 - .05f, -0.5, squareZ / 2 - 0.1));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
	model2 = rotateYMatrix * translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);
}

void Chair(Shader ourShader, glm::mat4 moveMatrix, float rotation, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	float fixLeg = 0.7f;
	float fixY = 0.1f;
	float fixYWhole = -0.17f;

	// Top
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.11f, 0.0f - fixY + fixYWhole, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.07f, 0.7f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Leg 1
	glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.13f, -0.32f + fixYWhole, 0.01f));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model1 = translateMatrix1 * scaleMatrix1;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model1);


	// Leg 2
	glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.13f, -0.32f + fixYWhole, 0.28f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model2);


	//// Leg 3
	//glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.43f, -0.32f + fixYWhole, 0.01f));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model1 = translateMatrix1 * scaleMatrix1;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model1);


	// Leg 4
	//glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.43f, -0.32f + fixYWhole, 0.28f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model2);


	//Left up 
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.17f, 0.01f - fixY + fixYWhole, 0.29f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);


	//Right up
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.39f, 0.01f - fixY + fixYWhole, 0.29f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);

	//Back support
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f, 0.09f - fixY + fixYWhole, 0.28f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.5f, 0.1f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {                 //Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {                 //Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {                 //Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {                 //Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //Down
	{
		/*if (rotateAxis_X) rotateAngle_X -= 0.1;
		else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
		else rotateAngle_Z -= 0.1;*/

		camera.ProcessKeyboard(DOWN, deltaTime);


	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)                   //Pitch positive
	{
		/*rotateAngle_X += 1;
		rotateAxis_X = 1.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(0.0f, 3.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)                   //Pitch negative
	{
		/*rotateAngle_X += 1;
		rotateAxis_X = 1.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(0.0f, -3.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)                   //Yaw positive
	{
		/*rotateAngle_Y += 1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 1.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(3.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)                   //Yaw negative
	{
		/*rotateAngle_Y += 1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 1.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(-3.0f, 0.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)                   //Roll positive
	{
		/*rotateAngle_Z += 0.1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 1.0;*/
		camera.ProcessYPR(0.0f, 0.0f, 0.5f);

	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Roll negative
	{
		/*rotateAngle_Z += 0.1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 1.0;*/
		camera.ProcessYPR(0.0f, 0.0f, -0.5f);

	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		eyeX += 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)                   //Rotate camera around a look at point
	{                                                                   //Right
		/*eyeX -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
		camera.RotateAroundLookAt(2.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)                   //Rotate camera around a look at point
	{                                                                   //Left
		/*eyeX -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
		camera.RotateAroundLookAt(-2.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		eyeZ += 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)                   //Rotate Fan
	{
		/*eyeZ -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
		isRotating ^= true;
		cout << isRotating << endl;

		Sleep(100);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		eyeY += 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
	{
		eyeY -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);

		camera.ProcessKeyboard(UP, deltaTime);

	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)                   //Up
	{
		while (dorja1_rotationY <= 100)
		{
			dorja1_rotationY += 24.0f;
			Sleep(100);
		}

		Sleep(100);

	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)                   //Up
	{
		while (dorja1_rotationY >= 24)
		{
			dorja1_rotationY -= 24.0f;
			Sleep(100);
		}



	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)                   //Up
	{
		if (window_translate < 0)
			window_translate = 0.8125f;
		else
			window_translate = -0.8125f;

		Sleep(100);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)                   //Up
	{
		isglobalBallonOn ^= true;



		Sleep(100);
	}



	//***************Lighting***************

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)                   //Lighting On-Off
	{
		lightingOn ^= true;
		cout << lightingOn << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)                   //Ambient On
	{
		ambientOn = 1.0;
		pointLight1.turnAmbientOn();
		pointLight2.turnAmbientOn();
		pointLight3.turnAmbientOn();
		pointLight4.turnAmbientOn();
		pointLight5.turnAmbientOn();
		spotLight.turnAmbientOn();
		spotLight2.turnAmbientOn();
		spotLight3.turnAmbientOn();
		directionalLight.turnAmbientOn();
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)                   //Ambient Off
	{
		ambientOn = 0.0;
		pointLight1.turnAmbientOff();
		pointLight2.turnAmbientOff();
		pointLight3.turnAmbientOff();
		pointLight4.turnAmbientOff();
		pointLight5.turnAmbientOff();
		spotLight.turnAmbientOff();
		spotLight2.turnAmbientOff();
		spotLight3.turnAmbientOff();
		directionalLight.turnAmbientOff();
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)                   //Diffuse On
	{
		diffuseOn = 1.0;
		pointLight1.turnDiffuseOn();
		pointLight2.turnDiffuseOn();
		pointLight3.turnDiffuseOn();
		pointLight4.turnDiffuseOn();
		pointLight5.turnDiffuseOn();
		spotLight.turnDiffuseOn();
		spotLight2.turnDiffuseOn();
		spotLight3.turnDiffuseOn();
		directionalLight.turnDiffuseOn();

	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)                   //Diffuse Off
	{
		diffuseOn = 0.0;
		pointLight1.turnDiffuseOff();
		pointLight2.turnDiffuseOff();
		pointLight3.turnDiffuseOff();
		pointLight4.turnDiffuseOff();
		pointLight5.turnDiffuseOff();
		spotLight.turnDiffuseOff();
		spotLight2.turnDiffuseOff();
		spotLight3.turnDiffuseOff();
		directionalLight.turnDiffuseOff();
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)                   //Specular On
	{
		specularOn = 1.0;
		pointLight1.turnSpecularOn();
		pointLight2.turnSpecularOn();
		pointLight3.turnSpecularOn();
		pointLight4.turnSpecularOn();
		pointLight5.turnSpecularOn();
		spotLight.turnSpecularOn();
		spotLight2.turnSpecularOn();
		spotLight3.turnSpecularOn();
		directionalLight.turnSpecularOn();
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)                   //Specular Off
	{
		specularOn = 0.0;
		pointLight1.turnSpecularOff();
		pointLight2.turnSpecularOff();
		pointLight3.turnSpecularOff();
		pointLight4.turnSpecularOff();
		pointLight5.turnSpecularOff();
		spotLight.turnSpecularOff();
		spotLight2.turnSpecularOff();
		spotLight3.turnSpecularOff();
		directionalLight.turnSpecularOff();
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)                   //Point Light On
	{
		pointLightOn = 1.0;
		pointLight1.turnOn();
		pointLight2.turnOn();
		pointLight3.turnOn();
		pointLight4.turnOn();
		pointLight5.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)                   //Point Light Off
	{
		pointLightOn = 0.0;
		pointLight1.turnOff();
		pointLight2.turnOff();
		pointLight3.turnOff();
		pointLight4.turnOff();
		pointLight5.turnOff();
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)                   //Directional Light On
	{
		directionalLightOn = 1.0;
		directionalLight.turnOn();
		directionalLight2.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)                   //Directional Light Off
	{
		directionalLightOn = 0.0;
		directionalLight.turnOff();
		directionalLight2.turnOff();
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)                   //Spot Light On
	{
		spotLightOn = 1.0;
		spotLight.turnOn(); 
		spotLight2.turnOn();
		spotLight3.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)                   //Spot Light Off
	{
		spotLightOn = 0.0;

		spotLight.turnOff();
		spotLight2.turnOn();
		spotLight3.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)                   //Dark On-Off
	{
		dark ^= true;
		cout << dark << endl;
	}




	//if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)               //Basic Camera rotate around lookat
	//{
	//    //lookAtX += 2.5 * deltaTime;
	//    //basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	//    float change = -0.3f;
	//    float x, y, z;
	//    x = eyeX * cos(glm::radians(change)) + eyeZ * sin(glm::radians(change));
	//    y = eyeY;
	//    z = - eyeX * sin(glm::radians(change)) + eyeZ * cos(glm::radians(change));

	//    eyeX = x, eyeY = y, eyeZ = z;
	//    basic_camera.changeEye(eyeX, eyeY, eyeZ);
	//}
	//if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	//{
	//    //lookAtX -= 2.5 * deltaTime;
	//    //basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);

	//    float change = 0.3f;
	//    float x, y, z;
	//    x = eyeX * cos(glm::radians(change)) + eyeZ * sin(glm::radians(change));
	//    y = eyeY;
	//    z = -eyeX * sin(glm::radians(change)) + eyeZ * cos(glm::radians(change));

	//    eyeX = x, eyeY = y, eyeZ = z;
	//    basic_camera.changeEye(eyeX, eyeY, eyeZ);
	//}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		lookAtY += 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		lookAtY -= 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		lookAtZ += 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		lookAtZ -= 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


//Texture Loading



unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

//OBJECTS

void drawCube(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), float spec = 1.0f, float shininess = 32.0f)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngleTest_Y), glm::vec3(0.0f, 1.0f, 0.0f));

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	ourShader.setMat4("model", moveMatrix * model);

	ourShader.setVec4("material.ambient", color);
	ourShader.setVec4("material.diffuse", color);
	ourShader.setVec4("material.specular", color * spec);
	ourShader.setFloat("material.shininess", shininess);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
