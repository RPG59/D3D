#pragma once
#include <string>


namespace d3d { namespace graphics {
	class Shader
	{
	public:
		static const Shader* s_CurrentlyBound;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string GetName() const = 0;
		virtual const std::string GetFilePath() const = 0;

		static void CreateFromFile(const std::string&, const std::string&, void* = nullptr);
		//static bool TryCompile(const std::string, std::string);
		//static bool TryCompileFromFile(const std::string, std::string);
		


	};
}}
