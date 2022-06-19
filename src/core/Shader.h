#pragma once

#include "math/Math.h"
#include "Vertex.h"

#include <vector>
#include <functional>

namespace MiniRenderer
{
#define SHADER_DATA_TEMPLATE <      \
		typename VertexInput,       \
		typename VertexOutput,      \
		typename VertexUniform,     \
		typename VertexShader,      \
		typename FragmentShader>

#define PASS_DATA_TEMPLATE <        \
		typename VertexShader,      \
		typename FragmentShader,    \
		typename VertexUniform>     

#define SHADER_DATA_TYPE < \
		VertexInput,       \
		VertexOutput,      \
		VertexUniform,     \
		VertexShader,      \
		FragmentShader>

#define PASS_DATA_TYPE <   \
		VertexShader,      \
		FragmentShader,    \
		VertexUniform>
	
	template <typename VertexInput, typename VertexOutput>
	using VertexShader = std::function<VertexOutput(const VertexInput&)>;
	template <typename VertexOutput>
	using FragmentShader = std::function<Vec4(const VertexOutput&)>;

	template <typename VertexShader, typename FragmentShader, typename VertexUniform>
	struct Pass
	{
		VertexShader vert;
		FragmentShader frag;
		VertexUniform* unif;
	};

	template SHADER_DATA_TEMPLATE
	class Shader
	{
		friend class Rasterizer;
	public:
		//using VertexShader = VertexShader<VertexInput, VertexOutput>;
		//using FragmentShader = FragmentShader<VertexOutput>;

		using Pass = Pass PASS_DATA_TYPE;
	public:
		Shader() = default;
		void AddPass(VertexShader vert, FragmentShader frag, VertexUniform* unif)
		{
			Pass pass{ vert, frag, unif };
			m_pass.push_back(pass);
		}

		void AddPass(Pass pass)
		{
			m_pass.push_back(pass);
		}

	private:
		std::vector<Pass> m_pass;
	};

	//template SHADER_DATA_TEMPLATE
	//using Pass = Shader SHADER_DATA_TYPE::Pass;
}