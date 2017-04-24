#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0), m_IsMove(false),
	m_IdleCount(0), m_IsIdle(false)
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
	//캐릭이동및 회전
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

	//IDLE일 때
	{
		if (!m_IsMove)
		{
			//가만히 있고, 빛생성 안했을 때
			if (!m_IsIdle) m_IdleCount++;
			else
			{
				m_fRotY += 0.03f;
			}
			//가만히 있고 20초지나면 라이트 생성
			if (m_IdleCount > 100)
			{
				m_IsIdle = true;
				m_IdleCount = 0;
				//CreateLight();
			}

			
		}
		else
		{
			m_IsIdle = false;
			g_pD3DDevice->LightEnable(0, false);
		}
	}
}

void cCharacter::Render()
{
}

void cCharacter::CreateLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	g_pD3DDevice->GetLight(0, &stLight);
	D3DXVECTOR3 vPos(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	stLight.Position = vPos;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
