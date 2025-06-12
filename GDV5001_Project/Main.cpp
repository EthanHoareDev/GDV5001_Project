#include"core.h"
#include"Shader.h"
#include "camera.h"


const int width = 512;
const int height = 512;
void framebuffer_resize(GLFWwindow* window, int fbw, int fbh);

GLfloat vertices[] =
{
	(-0.5f,0.0f,0.5f),	   (0.83f, 0.70f, 0.44f),		(0.f, 1.f),
	(-0.5f,-0.5f,-0.5f),   (0.83f, 0.70f, 0.44f),		(5.0f, 0.0f),
	(0.5f, 0.0f, -0.5f),   (0.83f, 0.70f, 0.44f),		(0.0f, 0.0f)
	(0.5f, 0.0f, 0.5f),    (0.83f, 0.70f, 0.44f),		(5.0f, 0.0f),
	(0.0f, 0.8f, 0.0f),    (0.92f, 0.86f, 0.76f),		(2.5f, 5.0f),
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0,1,2,
	0,2,3,
	0,1,4,
	1,2,4,
	2,3,4,
	3,0,4
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


void updateInput(GLFWwindow*window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
void framebuffer_resize(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);

}

GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1 &vertexShaderSource,NULL)





int main()

{

	glfwInit();

	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(width, height,"DUGEON KEEPERS 2", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize);

	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);


	//Init GLEW
	glfwMakeContextCurrent(window);


	Shader shaderProgram("Default.vert", "Default.frag");


	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
	std:: cout << "ERROR" << "\n";
	glfwTerminate();

	}


	//OPpenGL Options

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Shaders
	

	//GENRATING VAO
	GLuint VAO; 
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//UPDATE INPUT
		glfwPollEvents();


		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, -0.f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));



		//UPDATE
		updateInput(window);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		//clear
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		//END DRAW
		glfwSwapBuffers(window);
		glFlush();

	
	}
	


	glfwTerminate();
	return 0;

}

