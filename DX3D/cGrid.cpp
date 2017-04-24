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

}

void cGrid::Render()
{
	D3DXMATRIXA16 matLine;
	D3DXMatrixIdentity(&matLine);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matLine);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));

}
