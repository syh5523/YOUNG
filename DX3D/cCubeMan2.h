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
	//----------------------캐릭터 이동 관련--------------------
	std::vector<ST_PC_VERTEX>		m_vHexagon;					//목적지 관련 버텍스

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


	//캐릭터 이동
	void MoveCharacter();
};

