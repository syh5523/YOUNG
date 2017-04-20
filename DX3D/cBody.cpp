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
	cCubePNT::Setup();
	//ªÁ¿Ã¡Ó
	D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.2f, 1.2f, 0.6f);

	m_vLocalPos = D3DXVECTOR3(0, 1.4f, 0);

	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matS);
	}
}
