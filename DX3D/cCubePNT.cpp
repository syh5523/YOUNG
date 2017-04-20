#include "stdafx.h"
#include "cCubePNT.h"


cCubePNT::cCubePNT()
{
}


cCubePNT::~cCubePNT()
{
}


void cCubePNT::Setup()
{
	ST_PNT_VERTEX v;
	float cubeSize = 0.5f;

	D3DXVECTOR3 vec1, vec2;
	
	//¹ý¼± º¤ÅÍ
	D3DXVec3Cross(&v.n,
		&(D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize)),
		&(D3DXVECTOR3(cubeSize, cubeSize, -cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize)));

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
 
	//¹ý¼± º¤ÅÍ
	D3DXVec3Cross(&v.n,
		&(D3DXVECTOR3(cubeSize, cubeSize, cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize)),
		&(D3DXVECTOR3(-cubeSize, cubeSize, cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize)));

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);

	//¹ý¼± º¤ÅÍ
	D3DXVec3Cross(&v.n,
		&(D3DXVECTOR3(-cubeSize, cubeSize, cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize)),
		&(D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize)));

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);

	//¹ý¼± º¤ÅÍ
	D3DXVec3Cross(&v.n,
		&(D3DXVECTOR3(cubeSize, cubeSize, cubeSize) - D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize)),
		&(D3DXVECTOR3(cubeSize, cubeSize, -cubeSize) - D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize)));

	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);

	//¹ý¼± º¤ÅÍ
	D3DXVec3Cross(&v.n,
		&(D3DXVECTOR3(cubeSize, cubeSize, cubeSize) - D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize)),
		&(D3DXVECTOR3(-cubeSize, cubeSize, cubeSize) - D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize)));

	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);

	//¹ý¼± º¤ÅÍ
	D3DXVec3Cross(&v.n,
		&(D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize)),
		&(D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize) - D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize)));

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
}

void cCubePNT::Update()
{
}

void cCubePNT::Render()
{
}