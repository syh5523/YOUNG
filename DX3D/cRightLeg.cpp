#include "stdafx.h"
#include "cRightLeg.h"


cRightLeg::cRightLeg()
{
}


cRightLeg::~cRightLeg()
{
}

void cRightLeg::Setup()
{
	cCubeNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.1f, -0.3f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPosition.y = -0.3f;

	SetTexture(D3DXVECTOR2(40, 20), D3DXVECTOR2(44, 32),
		D3DXVECTOR2(48, 20), D3DXVECTOR2(52, 32),
		D3DXVECTOR2(52, 20), D3DXVECTOR2(56, 32),
		D3DXVECTOR2(44, 20), D3DXVECTOR2(48, 32),
		D3DXVECTOR2(48, 16), D3DXVECTOR2(52, 20),
		D3DXVECTOR2(44, 16), D3DXVECTOR2(48, 20));
}