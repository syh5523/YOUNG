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
	//������
	D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.2f, 1.2f, 0.6f);

	m_vLocalPos = D3DXVECTOR3(0, 1.4f, 0);

	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matS);
	}

	//>>
	/*cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&mat);

	D3DXMatrixScaling(&matS, 0.4f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}*/

	//<<
}
