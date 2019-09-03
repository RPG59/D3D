#include "Shader.h"
#include "DXShader.h"
#include <fstream>
#include <iterator>	

#define spnew new(__FILE__, __LINE__);

namespace d3d { namespace graphics {
	void Shader::CreateFromFile(const std::string& path, const std::string& source, void* address)
	{
		//D3DShader* result = address ? new(address) D3DShader(name, source) : spnew D3DShader(name, source);

		std::ifstream ifs(path.c_str());
		std::string result((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

		D3DShader* res = new D3DShader("stet", result);
	}

}}