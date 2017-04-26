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

	//----------------------캐릭터 이동 관련--------------------
	std::vector<ST_PC_VERTEX>		m_vHexagon;					//목적지 관련 버텍스
	std::vector<D3DXVECTOR3>		m_vVia;						//경유지 벅텍스

	float							m_Length;
	int								m_Befor_Index;
	int								m_via_Index;
	int								m_Currunt_Index;
	int								m_Destination_Index;
	//---------------------라이트 관련-----------------------
	D3DLIGHT9		m_CurruntLight;
	D3DXVECTOR3		m_SunDir;
	float			m_DLightAmbientR, m_DLightAmbientG, m_DLightAmbientB;
	float			m_DLightDiffuseR, m_DLightDiffuseG, m_DLightDiffuseB;
	int				m_TimeForDay;
	float			m_SunY;
	float			m_SunX;
public:
	virtual ~cCharacter();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	//라이트 관련
	void CreateLight();
	void MoveDirectionLight();
	void OffAllLight();

	//캐릭터 이동
	void MoveCharacter();

	virtual D3DXVECTOR3 & GetPosition();
};

