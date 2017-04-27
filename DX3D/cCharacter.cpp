#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	:m_fRotY(0),
	m_vDirection(0, 0, 1),
	m_vPosition(6, 0, 0), m_IsMove(false),
	m_IdleCount(0), m_IsIdle(false)
{
	D3DXMatrixIdentity(&m_matWorld);	
}


cCharacter::~cCharacter()
{

}

void cCharacter::Setup()
{	
	
}

void cCharacter::Update()
{
	//캐릭이동및 회전
	{
		m_IsMove = false;

		if (GetKeyState('A') & 0x8000)
			m_fRotY -= 0.057f;
		if (GetKeyState('D') & 0x8000)
			m_fRotY += 0.057f;
		if (GetKeyState('S') & 0x8000)
		{
			m_vPosition = m_vPosition + m_vDirection * 1.1f;
			m_IsMove = true;
		}
		else if (GetKeyState('W') & 0x8000)
		{
			m_vPosition = m_vPosition - m_vDirection * 1.1f;
			m_IsMove = true;
		}
	}

	//월드 구하기
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

		//Rotate
		D3DXMATRIXA16 matR, matRY;
		D3DXMatrixRotationY(&matRY, m_fRotY);
		matR = matRY;

		//방향 설정
		m_vDirection = D3DXVECTOR3(0, 0, 1);
		D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

		//Translate
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		m_matWorld = matS * matR * matT;
	}

}

void cCharacter::Render()
{


}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
