#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	:m_vDirection(0,0,1), m_vPosition(0,0,0), m_fRotY(0.0f)
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

	//�����̼�
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_fRotY);

	//�̵�
	D3DXMATRIXA16 matTranslation;
	D3DXMatrixTranslation(&matTranslation, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	//���� ���尪
	m_matWorld =  matR * matTranslation;

	//�ڽ��𷺼� �� �ʱ�ȭ
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&m_vDirection, &m_vDirection, &matR);

	//Ű ����
	KeySetting();
}

void cCharacter::Render()
{
}

void cCharacter::KeySetting()
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
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
