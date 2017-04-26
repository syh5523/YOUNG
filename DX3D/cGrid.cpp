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
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(200, 200, 50);

	int nNumHalfTile = 100;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		v.p = D3DXVECTOR3(fMin, 0, i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); m_vecVertex.push_back(v);
	}
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0, 0, fMin);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);  m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); m_vecVertex.push_back(v);


	//머터리얼
	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));
	m_stMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	m_stMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	m_stMaterial.Specular = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	v.c = D3DCOLOR_XRGB(255, 255, 0);
	float x = cosf(D3DX_PI / 3) * 6;
	float y = sinf(D3DX_PI / 3) * 6;

	v.p = D3DXVECTOR3(6, 0, 0); m_Hexagon.push_back(v);
	
	v.p = D3DXVECTOR3(x, 0, y); m_Hexagon.push_back(v);
	v.p = D3DXVECTOR3(x, 0, y); m_Hexagon.push_back(v);

	v.p = D3DXVECTOR3(-x, 0, y); m_Hexagon.push_back(v);
	v.p = D3DXVECTOR3(-x, 0, y); m_Hexagon.push_back(v);

	v.p = D3DXVECTOR3(-6, 0, 0); m_Hexagon.push_back(v);
	v.p = D3DXVECTOR3(-6, 0, 0); m_Hexagon.push_back(v);

	v.p = D3DXVECTOR3(-x, 0, -y); m_Hexagon.push_back(v);
	v.p = D3DXVECTOR3(-x, 0, -y); m_Hexagon.push_back(v);

	v.p = D3DXVECTOR3(x, 0, -y); m_Hexagon.push_back(v);
	v.p = D3DXVECTOR3(x, 0, -y); m_Hexagon.push_back(v);

	v.p = D3DXVECTOR3(6, 0, 0); m_Hexagon.push_back(v);
}

void cGrid::Render()
{
	D3DXMATRIXA16 matLine;
	D3DXMatrixIdentity(&matLine);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matLine);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));


	g_pD3DDevice->SetMaterial(&m_stMaterial);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_Hexagon.size() / 2, &m_Hexagon[0], sizeof(ST_PC_VERTEX));

}
