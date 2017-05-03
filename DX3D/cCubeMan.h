#pragma once
#include "cCharacter.h"
#define CUVNUMBER 100
#define POSSIBLEUPHEIGHT 0.25f
#define EXAMDISTANCE 0.3f

class cCubeNode;
class cGroup;

class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();

private:
	//----------------------캐릭터 이동 관련(베지어 곡선)-------------------
	vector<ST_PC_VERTEX>		m_vHexagon;					//목적지 관련 버텍스
	vector<D3DXVECTOR3>			m_vVia;						//경유지 벅텍스

	float							m_Lenght1, m_Lenght2;
	D3DXVECTOR3						m_savePos, m_savePos2;
	int								m_cuvNum;

	int								m_via_Index;
	int								m_Currunt_Index;
	int								m_Destination_Index;
	//----------------------------------바닥 충돌--------------------------------------
	vector<cGroup*>					m_vFloor;
	float							m_u, m_v, m_dist;
public:
	cCubeNode*	m_pRoot;

	D3DMATERIAL9	m_stMaterial;
	LPDIRECT3DTEXTURE9	m_pTexture;

	void RecieveHexaVertext(std::vector<ST_PC_VERTEX> *vertext);
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;


	//캐릭터 이동(베지어곡선)
	void MoveCharacter();

	//캐릭터 이동 D3DXIntersectTri 
	void GetFloor(vector<cGroup*> floor);
	void IntersectTri();
};

