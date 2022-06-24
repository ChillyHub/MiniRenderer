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
		Mat4 model;
		Mat4 view;
		Mat4 proj;
	} unif;

	VertexShader<a2v, v2f> vert = [&](const a2v& v) -> v2f {
		v2f o;
		o.pos = unif.proj * unif.view * unif.model * Vec4(v.vertex, 1.0f);
		o.color = v.color;
		return o;
	};

	FragmentShader<v2f> frag = [&](const v2f& i) -> Vec4 {
		auto color = Vec4(i.color, 1.0f);
		return color;
	};

	Shader<a2v, v2f, uniform, VertexShader<a2v, v2f>, FragmentShader<v2f>> shader;

	shader.AddPass(vert, frag, &unif);

	// Vertex Data
	a2v vertices[6] = {
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},

		{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 1.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
	};

	// Renderer

	Renderer renderer(800, 600);
	auto& camera = renderer.AddCamera();
	camera.Position = { 1.0f, 1.0f, 1.0f };
	camera.CameraLookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	camera.Fov = 60.0f;

	renderer.Update = [&]() {
		Mat4 mat(1.0f);
		Mat4 trans = Math::Translate(mat, { 0.0f, 0.0f, 0.0f });
		Mat4 rota = Math::Rotate(mat, (float)Time::GetTime(), { 0.0f, 0.0f, 1.0f });
		unif.model = trans * rota;
		unif.view = camera.GetViewMat();
		unif.proj = camera.GetProjectMat();

		renderer.DrawCall(vertices, 6, shader);
	};

	renderer.Run();
	
	return 0;
}