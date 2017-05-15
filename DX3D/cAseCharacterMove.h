#pragma once
class cAseCharacterMove
{
public:
	cAseCharacterMove();
	~cAseCharacterMove();

protected:
	SYNTHESIZE(bool, m_IsMove, IsMove)
	SYNTHESIZE(bool, m_IsBooster, IsBooster)

	float					m_fRotY;
	float					m_fSpeed;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;
	D3DXMATRIXA16			m_matWorld;
public:
	virtual void Setup();
	virtual void Update();


	virtual D3DXVECTOR3 & GetPosition();
};

