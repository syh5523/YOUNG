#pragma once

#define SUNPOSCHANGEVALUE	(0.005f)
#define EPSILON				(0.0001f)
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

	//--------------------------------------------
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
	void CreateLight();


	void CreateSpotLight();
	void CreatePointLight();
	void CreateDirectionLight();

	void MoveSpotLight();
	void MovePointLight();
	void MoveDirectionLight();

	void OffAllLight();

	virtual D3DXVECTOR3 & GetPosition();
};

