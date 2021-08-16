#ifndef VERTEXOBJECT_H
#define VERTEXOBJECT_H
#endif


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <vector>

class vObject
{
public:
	vObject()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void arrtibArray()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	
	void vBindArray()
	{
		glBindVertexArray(VAO);
	}

	void deallocate()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	glm::mat4 createModel(glm::mat4 model, glm::vec3 cubePosition, float rotation, float revolution)
	{
		model = glm::rotate(model, static_cast<float>(glfwGetTime()) * rotation, glm::vec3(1.0f, 0.3f, 0.5f));
		model = glm::translate(model, cubePosition);
		//model = glm::rotate(model, static_cast<float>(glfwGetTime()) / revolution, glm::vec3(1.0f, 0.3f, 0.5f));
		return model;	
	}

private:
	unsigned int VAO;
	unsigned int VBO;
};	