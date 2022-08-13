#pragma once

#include <memory>

#include "core/Shader.h"
#include "core/Texture.h"

namespace MiniRenderer
{
	class Material
	{
	private:
		//std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Texture> m_texture;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};
}