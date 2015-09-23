#define GLM_FORCE_RADIANS
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <iostream>

#include "renderer.h"
#include "vertexshader.h"

namespace {
	GLuint programID;
	GLuint vertexbuffer;
	GLuint VertexArrayID;
	GLuint indexbuffer;
	GLFWwindow* window;
	float alpha = 0.0f;
	glm::mat4 MVP(1.0);
	GLuint MVP_MatrixID;
	GLuint TextureID;
	GLuint uvbuffer;
	GLuint Texture;
};


void renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void renderer::Render(void) {
	const int N_repeat = 13;

	glm::vec3 x_axis(1.0, 0.0, 0.0);
	glm::vec3 y_axis(0.0, 1.0, 0.0);
	glm::vec3 z_axis(0.0, 0.0, 1.0);

	glm::vec3 cam_pos(0, 0, 0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = -z_axis; //oikeakatinen koordinaatisto
	glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);
	glBindVertexArray(VertexArrayID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	glm::mat4 VP = V*P;
	for (int j = 0; j < N_repeat; j++) {
		glm::mat4 M =
			glm::rotate(alpha + j*2.0f*3.14159265f / N_repeat, z_axis)*
			glm::translate(glm::vec3(0.0, 0.3, 0));
			//glm::scale(glm::vec3(0.75));
		MVP = VP*M;
		glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glVertexAttrib3f(VERTEX_POSITION, 0.0f, 0.0f, 0.0f);
		glPointSize(width / 15);
		glDrawArrays(GL_POINTS, 0, 12);
	}
	glfwSwapBuffers(window);
	alpha += 0.005f;
}


void renderer::Init(GLFWwindow* w) {
	window = w;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);

	/*glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);*/

	programID = LoadShaders("VertexShader.vertexshader", "FragmentShader.fragmentshader");
	MVP_MatrixID = glGetUniformLocation(programID, "MVP");

	glGenVertexArrays(1, &VertexArrayID);

	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	Texture = loadBMP_custom("./include/pointsprite.bmp");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glDisable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void renderer::Uninit(void) {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
}
