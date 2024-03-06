#include "renderer.h"

#include <glad/glad.h>
// include glfw after glad
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glpg;

void Renderer::render(Scene &scene, const ICamera &camera) {
	if (scene.depth_test) glEnable(GL_DEPTH_TEST);
	if (auto_clear) clear();

	const auto camera_world_position = glm::vec3(camera.get_model_matrix()[3]);
	const auto view_matrix = glm::inverse(camera.get_model_matrix());
	const auto projection_matrix = camera.get_projection_matrix();
	const auto view_projection_matrix = projection_matrix * view_matrix;
	const auto directional_light_world_direction = glm::normalize(glm::vec3(4.1f, 5.9f, -1.0f));

	scene.global_uniforms.set_mat4("view_matrix", view_matrix);
	scene.global_uniforms.set_mat4("projection_matrix", projection_matrix);
	scene.global_uniforms.set_mat4("view_projection_matrix", view_projection_matrix);
	scene.global_uniforms.set_float3("camera_world_position", camera_world_position);
	scene.global_uniforms.set_float3("directional_light_world_direction", directional_light_world_direction);

	for (const auto & mesh_node : scene.mesh_nodes) {
		mesh_node->draw(scene.global_uniforms);
	}

	m_axes_drawer.draw(scene);
}

void Renderer::set_clear_color(glm::vec4 clear_color) { m_clear_color = clear_color; }

void Renderer::clear() {
	glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::clear_color() { clear_color(m_clear_color); }

void Renderer::clear_color(glm::vec4 clear_color) {
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clear_depth() { glClear(GL_DEPTH_BUFFER_BIT); }
