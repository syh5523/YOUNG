#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0), m_IsMove(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
	//
}

void cCharacter::Update()
{
	m_IsMove = false;

	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.037f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.037f;
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + m_vDirection * 0.1f;
		m_IsMove = true;
	}	
	else if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - m_vDirection * 0.1f;
		m_IsMove = true;
	}


	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

	//Rotate
	D3DXMATRIXA16 matR, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotY);
	matR = matRY;

	//���� ����
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	//Translate
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS * matR * matT;
}

void cCharacter::Render()
{
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
