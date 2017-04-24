#include "stdafx.h"
#include "cHead.h"


cHead::cHead()
{
}


cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPosition.y = 0.5f;


	SetTexture(D3DXVECTOR2(8, 8), D3DXVECTOR2(16, 16),
		D3DXVECTOR2(24, 8), D3DXVECTOR2(32, 16),
		D3DXVECTOR2(0, 8), D3DXVECTOR2(8, 16),
		D3DXVECTOR2(16, 8), D3DXVECTOR2(24, 16),
		D3DXVECTOR2(16, 0), D3DXVECTOR2(24, 8),
		D3DXVECTOR2(8, 0), D3DXVECTOR2(16, 8));
	
}