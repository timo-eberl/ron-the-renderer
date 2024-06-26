#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;

out vec3 world_position;
out vec3 color;

uniform mat4 view_projection_matrix;
uniform vec3 camera_world_position;

void main() {
	// move axes with the camera, only in the direction the axes are pointing
	vec3 offset_mask = clamp( ceil( abs(a_position) ) ,0,1);
	vec3 offset = camera_world_position * offset_mask;

	world_position = a_position + offset;
	color = a_color;

	gl_Position = view_projection_matrix * vec4(world_position, 1.0);
}
