#pragma once
#include <string>
#include <iostream>

#include <d3d11.h>
#include <d3dcompiler.h>


#include "Shader.h"

namespace d3d { namespace graphics {
	struct D3DShaderErrorInfo
	{
		std::string profile;
		std::string message;
	};

	class D3DShader {
	private:
		struct Data
		{
			ID3D11VertexShader* vertexShader;
			ID3D11PixelShader* pixelShader;
			ID3DBlob* vs;
			ID3DBlob* ps;
		};
	private:
		static const D3DShader* s_CurrentlyBound;
	private:
		std::string m_Name;
		std::string m_FilePath;
		mutable Data m_Data;
	private:
		void Load(const std::string& source);
		void Parse(const std::string& source);
		void CreateBuffers();

		ID3DBlob* Compile(const std::string&, const std::string&, const std::string&, D3DShaderErrorInfo&);

	public:
		D3DShader(const std::string& name, const std::string& source);

	};
} }
