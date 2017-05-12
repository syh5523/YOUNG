#include "stdafx.h"
#include "cAseCharacterMove.h"


cAseCharacterMove::cAseCharacterMove()
	:m_IsMove(false), m_IsBooster(false)
	, m_fRotY(0.0f)
	, m_vDirection(0, 0, 0)
	, m_vPosition(0, 0, 0)
	, m_fSpeed(0.3f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cAseCharacterMove::~cAseCharacterMove()
{
}

void cAseCharacterMove::Setup()
{
}

void cAseCharacterMove::Update()
{
	m_IsMove = false;
	
	if (GetKeyState('W') & 0x8000)
	{
		 m_IsMove = true;
		 m_vPosition = m_vPosition - m_vDirection * m_fSpeed;		 
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_IsMove = true;
		m_vPosition = m_vPosition + m_vDirection * m_fSpeed;
	}
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.03f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.03f;
	}

	if (m_IsMove)
	{
		if (GetKeyState('Q') & 0x8000)
		{
			m_fSpeed = 0.06f;
			m_IsBooster = true;
		}
		else if (GetKeyState('E') & 0x8000)
		{
			m_fSpeed = 0.03f;
			m_IsBooster = false;
		}
	}
	else
	{
		m_fSpeed = 0.03f;
		m_IsBooster = false;
	}

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

	m_matWorld = matR * matT;
}

void cAseCharacterMove::Render()
{
}
