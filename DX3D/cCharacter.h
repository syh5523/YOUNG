#pragma once

#define SUNPOSCHANGEVALUE	(0.005f)
#define EPSILON				(0.1f)
class cCharacter
{
public:
	cCharacter();

protected:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

	bool			m_IsMove;

	bool			m_IsIdle;
	int				m_IdleCount;

public:
	virtual ~cCharacter();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual D3DXVECTOR3 & GetPosition();
};

