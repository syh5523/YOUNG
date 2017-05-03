#pragma once

#define SUNPOSCHANGEVALUE	(0.005f)
#define SPEEED	(0.15f)

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

	SYNTHESIZE(bool, m_IsDontMoveW, IsDontMoveW);
	SYNTHESIZE(bool, m_IsDontMoveS, IsDontMoveS);
	SYNTHESIZE(bool, m_IsJump, IsJump)
	SYNTHESIZE(bool, m_IsFall, IsFall)
	SYNTHESIZE(float, m_JumpHeight, JumpHeight)
public:
	virtual ~cCharacter();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual D3DXVECTOR3 & GetPosition();

	void Jump();
};

