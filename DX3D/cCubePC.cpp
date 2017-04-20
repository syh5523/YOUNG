#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC()
	:m_vDirection(0, 0, 1), m_vPosition(0, 0, 0),
	m_fRotY(0.0f), m_size(1.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	//삼각형 하나만 그리게끔
	CubeSetup();
}

void cCubePC::Update()
{
	//사이즈
	D3DXMATRIXA16 matS;
	//D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, m_size, m_size, m_size);

	//로테이션
	D3DXMATRIXA16 matR;
	//D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);

	//이동
	D3DXMATRIXA16 matTranslation;
	//D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixTranslation(&matTranslation, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	//최종 월드값
	m_matWorld = matS * matR * matTranslation;

	//박스디렉션 값 초기화
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&m_vDirection, &m_vDirection, &matR);

	//키 셋팅
	KeySetting();

}

void cCubePC::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	//몸통
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

void cCubePC::CubeSetup()
{
	ST_PC_VERTEX v;
	float cubeSize = 0.5f;

	v.c = D3DCOLOR_XRGB(50, 50, 0);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 50, 50);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(50, 0, 50);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(200, 50, 50);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(50, 200, 50);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(50, 50, 200);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 50, 50);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.c = D3DCOLOR_XRGB(50, 0, 50);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.c = D3DCOLOR_XRGB(200, 50, 50);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.c = D3DCOLOR_XRGB(50, 200, 50);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.c = D3DCOLOR_XRGB(50, 50, 200);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);   m_vecVertex2.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);   m_vecVertex2.push_back(v);
}

void cCubePC::KeySetting()
{
	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}
	else if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vDirection * 0.1f);
	}

	if (GetKeyState('Z') & 0x8000)
	{
		m_size += 0.1f;
	}
	else if (GetKeyState('X') & 0x8000)
	{
		m_size -= 0.1f;
	}
}

D3DXVECTOR3& cCubePC::GetPosition()
{
	return m_vPosition;
}

