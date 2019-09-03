#include "DXShader.h"
#include "D3DContext.h"


namespace d3d {
	namespace graphics {
		D3DShader::D3DShader(const std::string& name, const std::string& source)
			: m_Name(name)
		{
			Load(source);
			Parse(source);
			CreateBuffers();
		}

		void D3DShader::Load(const std::string& source)
		{
			D3DShaderErrorInfo info;
			m_Data.vs = Compile(source, "vs_4_0", "VSMain", info);
			m_Data.ps = Compile(source, "ps_4_0", "PSMain", info);

			HRESULT hr;

			hr = D3DContext::GetDevice()->CreateVertexShader(m_Data.vs->GetBufferPointer(), m_Data.vs->GetBufferSize(), NULL, &m_Data.vertexShader);
			if (FAILED(hr))
			{
				DebugBreak();
			}
			hr = D3DContext::GetDevice()->CreatePixelShader(m_Data.ps->GetBufferPointer(), m_Data.ps->GetBufferSize(), NULL, &m_Data.pixelShader);
			if (FAILED(hr))
			{
				DebugBreak();
			}

			D3DContext::GetDeviceContext()->VSSetShader(m_Data.vertexShader, NULL, NULL);
			D3DContext::GetDeviceContext()->PSSetShader(m_Data.pixelShader, NULL, NULL);

			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			ID3D11InputLayout* pLayout;

			D3DContext::GetDevice()->CreateInputLayout(ied, 2, m_Data.vs->GetBufferPointer(), m_Data.vs->GetBufferSize(), &pLayout);
			D3DContext::GetDeviceContext()->IASetInputLayout(pLayout);
		}

		ID3DBlob* D3DShader::Compile(const std::string& source, const std::string& profile, const std::string& main, D3DShaderErrorInfo& info)
		{
			ID3DBlob* shaderBlob;
			ID3DBlob* errorBlob;

			HRESULT hr = D3DCompile(source.c_str(), source.size(), NULL, NULL, NULL, main.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
			if (hr != S_OK)
				info.message = "Unable to compile shader from source\n";
			if (errorBlob)
			{
				info.profile += profile + "\n";
				if (errorBlob->GetBufferSize())
					std::cout << "Shader compile Errors: " << std::endl << (const char*)errorBlob->GetBufferPointer() << std::endl;
				errorBlob->Release();
			}
			if (hr == S_OK)
				return shaderBlob;
			return NULL;
		}

		void D3DShader::Parse(const std::string& source)
		{

		}

		void D3DShader::CreateBuffers()
		{

		}


	}
}