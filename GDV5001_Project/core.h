#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<cerrno>
#include<glad/glad.h>


#include<glew.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<SOIL2.h>
#include<glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm:: vec2 texcoord;
};