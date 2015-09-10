#define GLEW_STATIC
#define GLM_FORCE_RADIANS

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <common/shader.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>


GLFWwindow* window;
GLuint programID;
GLuint vertexbuffer;
GLuint VertexArrayID;
GLuint colorbuffer;


void Render(void) {
  glClear( GL_COLOR_BUFFER_BIT );
  glUseProgram(programID);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
			0,       // must match the layout in the shader.
			3,       // size
			GL_FLOAT,// type
			GL_FALSE,// normalized
			0,       // stride
			(void*)0 // array buffer offset
			);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glVertexAttribPointer(
			1,         // must match the layout in the shader.
			3,         // size
			GL_FLOAT,  // type
			GL_FALSE,  // normalized?
			0,         // stride
			(void*)0   // array buffer offset
			);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glfwSwapBuffers(window);
}
void Init(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  programID = LoadShaders(
			  "VertexShader.vertexshader",
			  "FragmentShader.fragmentshader" );
 
  static const GLfloat g_vertex_buffer_data[] = { 
    -0.5f, -0.5f, 0.0f, 0.5f,  0.0f, 0.0f,
    0.0f,  0.5f, 0.0f, };

  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER,
	       sizeof(g_vertex_buffer_data),
	       g_vertex_buffer_data, GL_STATIC_DRAW);
  static const GLfloat g_color_buffer_data[] = { 
    1.0f,  0.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
    0.0f,  0.0f, 1.0f,
  };
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER,
	       sizeof(g_color_buffer_data),
	       g_color_buffer_data, GL_STATIC_DRAW);
}

void Uninit(void) {
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteBuffers(1, &colorbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);
}

void PrintVec(const glm::vec4 &v)
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << v[i] << "\n";
	}
	std::cout << "\n";
}

void PrintMatrix(const glm::mat4 &m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << m[j][i] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main( void ) {

	//-----------------------------------------------------
	
	std::cout << "Ex 25-------------------------------------------------------\n" << std::endl;
	glm::vec4 P1(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 P2(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 P3(0.0f, 1.0f, 0.0f, 1.0f);

	glm::vec3 x_axis(1.0f, 0.0f, 0.0f);
	glm::vec3 y_axis(0.0f, 1.0f, 0.0f);
	glm::vec3 z_axis(0.0f, 0.0f, 1.0f);

	glm::vec3 s(0.3f); //skaalaus
	glm::vec3 t(-2.0f, -1.0f, 0.0f); //siirto
	glm::vec3 r = z_axis; //kierto

	glm::mat4 R = rotate(3.14159265f / 6.0f, r);
	glm::mat4 S = scale(s);
	glm::mat4 T = translate(t);

	glm::mat4 T_total = T*S*R;
	PrintVec(T_total*P1);
	PrintVec(T_total*P2);
	PrintVec(T_total*P3);
	PrintMatrix(T_total);


	std::cout << "\nEx 26--------------------------------------------------------" << std::endl;
	glm::vec3 cam_pos(1.2f, 0.1f, 0.0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = z_axis; //oikeakätinen koordinaatisto

	glm::mat4 C = lookAt(cam_pos, cam_pos + cam_front, cam_up);
	T_total = C*T_total;

	PrintVec(T_total*P1);
	PrintVec(T_total*P2);
	PrintVec(T_total*P3);
	PrintMatrix(T_total);

	std::cout << "\nEx 27---------------------------------------------------------" << std::endl;

	float v_width = 6.0; //viewport in camera coord
	float v_height = 6.0;

	glm::mat4  T_projection = glm::ortho(-0.5f*v_width, 0.5f*v_width,
		-0.5f*v_height, 0.5f*v_height);
	T_total = T_projection*T_total;
	PrintVec(T_total*P1);
	PrintVec(T_total*P2);
	PrintVec(T_total*P3);
	PrintMatrix(T_total);

	//------------------------------------------------------

	//------------------------------------------------------
	
	//Ex 23 GLM:llä matriisi laskemista
	//glm::mat4 matrix1(1.0f, 0.0f, 2.0f, 2.0f,
	//				  0.0f, 1.0f, 0.0f, 0.0f,
	//				  1.0f, 1.0f, 1.0f, 2.0f,
	//				  0.0f, 0.0f, 1.0f, 0.0f);

	//glm::mat4 matrix2(0.0f, 0.0f, 0.0f, 2.0f,
	//				  1.0f, 1.0f, 0.0f, 0.0f,
	//				  1.0f, 1.0f, 0.0f, 2.0f,
	//				  0.0f, 0.0f, 1.0f, 0.0f);

	//glm::vec4 multiplyVector(3.0f, 4.0f, -2.0f, 1.0f);

	//glm::vec4 xTulos;

	//xTulos = (matrix1 * matrix2) * multiplyVector;

	///*for (int j = 0; j < sizeof(xTulos); j++)
	//{
	//	std::cout << xTulos[j] << std::endl;
	//}*/

	//std::cout << xTulos[0] << ", " << xTulos[1] << ", " << xTulos[2] << ", " << xTulos[3] << std::endl;

	//system("pause");

	//return 0;
	//--------------------------------------------------------
	
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 768,
		"Tutorial 02 - Red triangle", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	Init();

	do{
		Render();
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
  

	system("pause");

	return 0;
}
