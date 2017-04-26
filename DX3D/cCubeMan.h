#pragma once
#include "cCharacter.h"

class cCubeNode;

class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();

private:
	//----------------------ĳ���� �̵� ����--------------------
	std::vector<ST_PC_VERTEX>		m_vHexagon;					//������ ���� ���ؽ�
	std::vector<D3DXVECTOR3>		m_vVia;						//������ ���ؽ�

	float							m_Length;
	int								m_Befor_Index;
	int								m_via_Index;
	int								m_Currunt_Index;
	int								m_Destination_Index;

public:
	cCubeNode*	m_pRoot;

	D3DMATERIAL9	m_stMaterial;
	LPDIRECT3DTEXTURE9	m_pTexture;

	void RecieveHexaVertext(std::vector<ST_PC_VERTEX> *vertext);
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;


	//ĳ���� �̵�
	void MoveCharacter();
};

