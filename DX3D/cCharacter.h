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

	//----------------------ĳ���� �̵� ����--------------------
	std::vector<ST_PC_VERTEX>		m_vHexagon;					//������ ���� ���ؽ�
	std::vector<D3DXVECTOR3>		m_vVia;						//������ ���ؽ�

	float							m_Length;
	int								m_Befor_Index;
	int								m_via_Index;
	int								m_Currunt_Index;
	int								m_Destination_Index;
	//---------------------����Ʈ ����-----------------------
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

	//����Ʈ ����
	void CreateLight();
	void MoveDirectionLight();
	void OffAllLight();

	//ĳ���� �̵�
	void MoveCharacter();

	virtual D3DXVECTOR3 & GetPosition();
};

