#include "MiniRenderer.h"

using namespace MiniRenderer;

int main()
{
	// TEST
	Vec<4, Complex<float>> t = {
		{1, 2}, {3, 4}, {5, 6}, {7, 8}
	};

	t *= 2.3f;

	std::cout << t << std::endl;
	std::cout << -t << std::endl;

	Quat q;
	std::cout << q << std::endl;

	auto a = Math::Rotate(q, 0.6f, { 0.3f, 0.4f, 0.5f });
	std::cout << a << std::endl;

	Mat4 mat(1.0f);
	auto model = Math::Translate(mat, { 1.0f, 2.0f, 4.0f });
	auto rotation = Math::Rotate(mat, 0.6f, { 1.0f, 2.0f, 3.0f });
	auto projection = Math::Perspective(0.6f, 16.0f / 9.0f, 0.1f, 100.0f);
	std::cout << model << rotation << projection << projection * rotation * model << std::endl;
	model = Math::Translate(mat, { 1.0f, 2.0f, 3.0f });

	Vec<Type::Dynamic, float> gg{1, 2, 3, 4, 5, 6, 7, 8};
	std::cout << gg << std::endl;
	gg = std::move(Vec<Type::Dynamic, float>(3));

	std::cout << gg << std::endl;

	MatX mama(1.0f, 9, 9);
	mama = mama + mama;
	mama = mama * mama;

	std::cout << mama << std::endl;

	try
	{
		VecX min{ 1, 2, 3, 4, 5 };
		VecX max{ 5, 4, 3, 2, 1 };
		std::cout << Math::Max(min, max) << std::endl;
		std::cout << Math::Normailzed(min) << std::endl;
		std::cout << Math::Dot(min, max) << std::endl;

		Mat3 A{ 1, 2, -1, 2, 1, -2, -3, 1, 1 };
		Mat3 L, U;
		Math::LUDecompose(A, L, U);
		std::cout << L << U << std::endl;

		MatX B({ 1, 2, -1, 2, 1, -2, -3, 1, 1 }, 3, 3);
		MatX LL, UU, PP;
		Math::LUPDecompose(B, LL, UU, PP);
		std::cout << "LUP\n" << LL << UU << PP  << PP * B << LL * UU << std::endl;
		Math::LUDecompose(LL * UU, LL, UU);
		std::cout << LL << UU;
		Math::LUDecompose(PP * B, LL, UU);
		std::cout << LL << UU << std::endl;

		Mat3 LU{ 1, 2, -1, 2, 1, -2, -3, 1, 1 };
		Mat3 LLL, UUU;
		Math::LUDecompose(LU, LLL, UUU);
		std::cout << Math::SolveLU(LLL, UUU, Vec3(3, 3, -6)) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	
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
		Vec4 color;
	} unif;

	VertexShader<a2v, v2f> vert = [&](const a2v& v) -> v2f {
		v2f o;
		o.pos = Vec4(v.vertex);
		o.pos.w = 1.0f;
		o.color = v.color;
		return o;
	};

	FragmentShader<v2f> frag = [&](const v2f& i) -> Vec4 {
		auto color = i.pos * 0.5f + 0.5f;
		color = Vec4(i.color) * 0.5f + 0.5f;
		color.w = 1.0f;
		return color;
	};

	Shader<a2v, v2f, uniform, VertexShader<a2v, v2f>, FragmentShader<v2f>> shader;

	a2v vertices[6] = {
		{{-0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}},
		{{ 0.0f,  0.5f, 0.0f}, { 0.0f,  0.5f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, { 0.5f, -0.5f, 0.0f}},

		{{-0.5f,  0.5f, 0.1f}, {-0.5f,  0.5f, 0.1f}},
		{{ 0.0f, -0.5f, 0.1f}, { 0.0f, -0.5f, 0.1f}},
		{{ 0.5f,  0.5f, 0.1f}, { 0.5f,  0.5f, 0.1f}}
	};

	shader.AddPass(vert, frag, &unif);

	// Renderer

	Renderer renderer(800, 600);

	renderer.Update = [&]() {
		unif.color = Vec4(0.5f, 0.5f, 0.5f, 1.0f);
		renderer.DrawCall(vertices, 6, shader);
	};

	renderer.Run();

	return 0;
}