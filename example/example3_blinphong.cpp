#include "MiniRenderer.h"

#include "model/Sphere.h"

using namespace MiniRenderer;

int main()
{
	// Shader
	struct a2v
	{
		Vec3 vertex;
		Vec2 texcoord;
		Vec3 normal;
	};

	struct v2f : VertexOut
	{
		Vec3 worldPos;
		Vec3 normal;
		Vec3 lightDir;
		Vec3 viewDir;
	};

	struct uniform
	{
		Mat4 model;
		Mat4 view;
		Mat4 proj;
		Vec4 color;
		Light* light = nullptr;
		Camera* camera = nullptr;
	} unif;

	VertexShader<a2v, v2f> vert = [&](const a2v& v) -> v2f {
		v2f o;
		o.worldPos = unif.model * Vec4(v.vertex, 1.0f);
		o.pos = unif.proj * unif.view * Vec4(o.worldPos, 1.0f);
		o.normal = unif.model * Vec4(v.normal, 1.0f);
		o.lightDir = unif.light->GetObjToLightDir(o.worldPos);
		o.viewDir = unif.camera->GetObjToViewDir(o.worldPos);
		return o;
	};

	FragmentShader<v2f> frag = [&](const v2f& i) -> Vec4 {
		Vec3 ambient = unif.color * Vec4(0.1f);

		Vec3 diffuse = unif.color * unif.light->LightColor * Math::Max(Math::Dot(i.normal, i.lightDir), 0.0f);

		Vec3 halfDir = Math::Normailzed(i.lightDir + i.viewDir);
		Vec3 specular = unif.color * unif.light->LightColor * Math::Pow(Math::Max(Math::Dot(i.normal, halfDir), 0.0f), 16.0f);

		Vec3 color = ambient + diffuse + specular;

		return Vec4(color, 1.0f);
	};

	Shader<a2v, v2f, uniform, VertexShader<a2v, v2f>, FragmentShader<v2f>> shader;

	shader.AddPass(vert, frag, &unif);

	// Vertex Data
	a2v* vertices;
	VertexIndex* indices;

	Sphere sphere;
	int indexCount = sphere.GetIndexCount();
	int vertexCount = sphere.GetVertexCount();
	vertices = new a2v[vertexCount];
	indices = new VertexIndex[indexCount];

	for (int i = 0; i < indexCount; ++i)
	{
		indices[i] = sphere.GetIndex(i);
	}
	for (int i = 0; i < vertexCount; ++i)
	{
		vertices[i].vertex = sphere.GetVertex(i);
		vertices[i].texcoord = sphere.GetUV(i);
		vertices[i].normal = sphere.GetNormal(i);
	}

	// Renderer
	Renderer renderer(800, 600);
	renderer.GetRasterizer().RenderDataType = sphere.GetDataType();
	renderer.GetRasterizer().RenderFaceCull = FaceCull::CullBack;
	auto& camera = renderer.AddCamera();
	camera.Position = { 3.0f, 3.0f, 0.0f };
	camera.CameraLookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	camera.Fov = 60.0f;

	Light light(Vec3(0.0f, 0.0f, 0.0f));
	light.Rotation = Math::MatToQuat(Math::Rotate(Mat4(1.0f), Math::Radians(30.0f), Vec3(-1.0f, 1.0f, 0.0f)));

	unif.color = Vec4(0.5f, 0.6f, 0.7f, 1.0f);
	unif.light = &light;
	unif.camera = &camera;

	renderer.Update = [&]() {
		Mat4 mat(1.0f);
		unif.model = mat;
		unif.view = camera.GetViewMat();
		unif.proj = camera.GetProjectMat();

		renderer.DrawCall(shader, vertices, vertexCount, indices, indexCount);
	};

	renderer.Run();

	return 0;
}