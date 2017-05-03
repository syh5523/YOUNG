#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	:m_fRotY(0),
	m_vDirection(0, 0, 1),
	m_vPosition(6, 0, 0), m_IsMove(false),
	m_IdleCount(0), m_IsIdle(false), 
	m_IsDontMoveW(false), m_IsDontMoveS(false),
	m_JumpHeight(0.0f), m_IsFall(false)
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
	//점프시
	Jump();

	//캐릭이동및 회전
	{
		m_IsMove = false;
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (m_JumpHeight > 0.0f) return;

			m_JumpHeight = 0.0f;
			m_vPosition.y += 0.05f;
			m_IsJump = true;
		}
		if (GetKeyState('A') & 0x8000)
			m_fRotY -= 0.057f;
		if (GetKeyState('D') & 0x8000)
			m_fRotY += 0.057f;
		if (GetKeyState('S') & 0x8000)
		{
			if (m_IsDontMoveW)
			{
				m_IsDontMoveW = false;
				return;
			}
			
			m_vPosition = m_vPosition + m_vDirection * SPEEED;
			m_IsMove = true;
		}
		else if (GetKeyState('W') & 0x8000)
		{
			if (m_IsDontMoveS)
			{
				m_IsDontMoveS = false;
				return;
			}
			m_vPosition = m_vPosition - m_vDirection * SPEEED;
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

void cCharacter::Jump()
{
	if (m_IsJump)
	{
		m_JumpHeight += 0.05f;

		if (m_JumpHeight >= 1.5f)  m_IsJump = false;
	}

	if (!m_IsJump && m_JumpHeight > 0.0f)
	{
		if (m_vPosition.y < 0.0f) return;
		m_JumpHeight -= 0.05f;
	}
	if (m_JumpHeight < 0)
	{
		m_JumpHeight = 0.0;
	}
	m_vPosition.y = m_vPosition.y + m_JumpHeight;

}
