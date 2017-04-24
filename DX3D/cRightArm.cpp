#include "stdafx.h"
#include "cRightArm.h"


cRightArm::cRightArm()
{
}


cRightArm::~cRightArm()
{
}

void cRightArm::Setup()
{
	cCubeNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.3f, -0.3f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPosition.y = 0.3f;

	SetTexture(D3DXVECTOR2(4, 20), D3DXVECTOR2(8, 32),
		D3DXVECTOR2(12, 20), D3DXVECTOR2(16, 32),
		D3DXVECTOR2(0, 20), D3DXVECTOR2(4, 32),
		D3DXVECTOR2(8, 20), D3DXVECTOR2(12, 32),
		D3DXVECTOR2(4, 16), D3DXVECTOR2(8, 20),
		D3DXVECTOR2(8, 16), D3DXVECTOR2(12, 20));
}