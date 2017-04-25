#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}


void cPyramid::Setup()
{
	ST_PC_VERTEX v;

	float size1 = 0.4f;
	float size2 = 0.1f;

	ZeroMemory(&m_stMaterialX, sizeof(D3DMATERIAL9));
	m_stMaterialX.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_stMaterialX.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_stMaterialX.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	ZeroMemory(&m_stMaterialY, sizeof(D3DMATERIAL9));
	m_stMaterialY.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_stMaterialY.Ambient = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_stMaterialY.Specular = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	ZeroMemory(&m_stMaterialZ, sizeof(D3DMATERIAL9));
	m_stMaterialZ.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_stMaterialZ.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_stMaterialZ.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, -size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, -size2, -size2);   m_vecVertexX.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, -size2, -size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, -size2, size2);   m_vecVertexX.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, -size2, size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, size2);   m_vecVertexX.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, -size2);   m_vecVertexX.push_back(v);

	v.p = D3DXVECTOR3(size1, -size2, -size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, -size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, size2);   m_vecVertexX.push_back(v);

	v.p = D3DXVECTOR3(size1, -size2, -size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, size2, size2);   m_vecVertexX.push_back(v);
	v.p = D3DXVECTOR3(size1, -size2, size2);   m_vecVertexX.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, - size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(-size2, size1, - size2);   m_vecVertexY.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(-size2, size1, - size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(-size2, size1,size2);   m_vecVertexY.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(-size2, size1,size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, size2);   m_vecVertexY.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, - size2);   m_vecVertexY.push_back(v);

	v.p = D3DXVECTOR3(-size2, size1, - size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, - size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, size2);   m_vecVertexY.push_back(v);

	v.p = D3DXVECTOR3(-size2, size1, - size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(size2, size1, size2);   m_vecVertexY.push_back(v);
	v.p = D3DXVECTOR3(-size2, size1,size2);   m_vecVertexY.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(-size2, size2, size1);		m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(-size2, -size2, size1);		 m_vecVertexZ.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(-size2, -size2, size1);		m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, -size2, size1);	m_vecVertexZ.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, -size2, size1);	m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, size2, size1);	m_vecVertexZ.push_back(v);

	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, size2, size1);	m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(-size2, size2, size1);	m_vecVertexZ.push_back(v);

	v.p = D3DXVECTOR3(-size2, -size2, size1);		m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(-size2, size2, size1);	 m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, size2, size1);	m_vecVertexZ.push_back(v);

	v.p = D3DXVECTOR3(-size2, -size2, size1);		m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, size2, size1);	 m_vecVertexZ.push_back(v);
	v.p = D3DXVECTOR3(size2, -size2, size1);	 m_vecVertexZ.push_back(v);
}

void cPyramid::Render()			
{								
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMaterialX);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertexX.size() / 3,
		&m_vecVertexX[0], sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMaterialY);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertexY.size() / 3,
		&m_vecVertexY[0], sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMaterialZ);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertexZ.size() / 3,
		&m_vecVertexZ[0], sizeof(ST_PC_VERTEX));
}
