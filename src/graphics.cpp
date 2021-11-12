#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics.h"
#include "context.h"
#include "entity.h"

namespace OpenGL
{
	void GraphicsComponent::Draw(Entity& entity) {}

	QuadComponent::QuadComponent()
		: quad(Quad()), vertexArray(0), vertexBuffer(0), elementBuffer(0)
	{
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad.vertices), quad.vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad.indices), quad.indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

	}

	void QuadComponent::Draw(Entity& entity)
	{
		glm::vec2 position = glm::vec2(1.0f);

		unsigned int shader = Context::Shaders["BasicShader"];
		glUseProgram(shader);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(glm::vec2(1.0f), 0.0f))
		* glm::scale(glm::mat4(1.0f), glm::vec3(glm::vec2(1.0f), 1.0f));

		unsigned int modelUniform = glGetUniformLocation(shader, "model");
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int positionUniform = glGetUniformLocation(shader, "position");
		glUniform2fv(positionUniform, 1, glm::value_ptr(position));

		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}