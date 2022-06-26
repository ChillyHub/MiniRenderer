#include "MiniRenderer.h"

using namespace MiniRenderer;

int main()
{
	// Shader
	struct a2v
	{
		Vec3 vertex;
		Vec3 color;
	};

	struct v2f : VertexOut
	{
		Vec3 color;
	};

	struct uniform
	{

	} unif;

	VertexShader<a2v, v2f> vert = [&](const a2v& v) -> v2f {
		v2f o;
		o.pos = Vec4(v.vertex, 1.0f);
		o.color = v.color;
		return o;
	};

	FragmentShader<v2f> frag = [&](const v2f& i) -> Vec4 {
		auto color = Vec4(i.color * 0.5f + 0.5f, 1.0f);
		return color;
	};

	Shader<a2v, v2f, uniform, VertexShader<a2v, v2f>, FragmentShader<v2f>> shader;

	a2v vertices[3] = {
		{{-0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}},
		{{ 0.0f,  0.5f, 0.0f}, { 0.0f,  0.5f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, { 0.5f, -0.5f, 0.0f}}
	};

	shader.AddPass(vert, frag, &unif);

	// Renderer
	Renderer renderer(800, 600);

	renderer.Update = [&]() {
		renderer.DrawCall(shader, vertices, 3);
	};

	renderer.Run();

	return 0;
}