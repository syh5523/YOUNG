#pragma once
#include "cCharacter.h"
#define CUVNUMBER 100

class cCubeNode;

class cCubeMan2 : public cCharacter
{
public:
	cCubeMan2();
	~cCubeMan2();

private:
	//----------------------ĳ���� �̵� ����--------------------
	std::vector<ST_PC_VERTEX>		m_vHexagon;					//������ ���� ���ؽ�

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

