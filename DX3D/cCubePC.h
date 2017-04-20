#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();

private:
	std::vector<ST_PC_VERTEX>			m_vecVertex, m_vecVertex2;
	float								m_fRotY;
	float								m_size;
	D3DXVECTOR3							m_vDirection;
	D3DXVECTOR3							m_vPosition;
	D3DXMATRIXA16						m_matWorld;

public:
	void Setup();
	void Update();
	void Render();
	void CubeSetup();
	void KeySetting();

	D3DXVECTOR3& GetPosition();
};

