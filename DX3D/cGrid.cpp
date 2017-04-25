#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{
	cCubeNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 100.0f, 1.0f, 100.0f);

	D3DXMatrixTranslation(&matT, 0.0f, -1.5f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));
	m_stMaterial.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_stMaterial.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_stMaterial.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

}
