#include "stdafx.h"
#include "cBody.h"


cBody::cBody()
{
}


cBody::~cBody()
{
}

void cBody::Setup()
{
	//-----------------------------------------------------------
	//						Ω∫ƒ…¿œ
	//-----------------------------------------------------------
	{
		cCubeNode::Setup();

		D3DXMATRIXA16 matS, matT, mat;
		D3DXMatrixScaling(&matS, 0.4f, 0.6f, 0.2f);
		D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
		mat = matS * matT;

		for (size_t i = 0; i < m_vecVertex.size(); i++)
		{
			D3DXVec3TransformCoord(&m_vecVertex[i].p,
				&m_vecVertex[i].p,
				&mat);
		}
	}

	SetTexture(D3DXVECTOR2(20, 20), D3DXVECTOR2(28, 31),
		D3DXVECTOR2(32, 20), D3DXVECTOR2(40, 31),
		D3DXVECTOR2(16, 20), D3DXVECTOR2(20, 31),
		D3DXVECTOR2(28, 20), D3DXVECTOR2(32, 31),
		D3DXVECTOR2(20, 16), D3DXVECTOR2(28, 20),
		D3DXVECTOR2(28, 16), D3DXVECTOR2(36, 20));

}


