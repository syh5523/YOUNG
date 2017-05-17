#pragma once
#include "cObject.h"
#include "cMtlTex.h"

class cFrame : public cObject
{
public:
	cFrame();
	~cFrame();

private:
	SYNTHESIZE(LPD3DXMESH, m_pMesh, Mesh)
	
	SYNTHESIZE_PASS_BY_REF(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex)
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocalTM, LocalTM)
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM)
	SYNTHESIZE_PASS_BY_REF(vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack)
	SYNTHESIZE_PASS_BY_REF(vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack)
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex)
	vector<cFrame*> m_vecChild;

	SYNTHESIZE(bool, m_IsMove, IsMove)
	SYNTHESIZE(bool, m_IsMeshRender, IsMeshRender)						
	SYNTHESIZE(int, m_fFrameSpeed, fFrameSpeed)


	SYNTHESIZE(DWORD, m_Frame, Frame)

public:
	void Setup(bool IsMeshRender);
	void Update(int nKeyFrame, D3DXMATRIXA16 *pMatParent);
	void Render();
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalcOriginalLocalTM(D3DXMATRIXA16 *pMatParent);

	DWORD m_dwFirstFrame;
	DWORD m_dwLastFrame;
	DWORD m_dwFrameSpeed;
	DWORD m_dwTicksPerFrame;

	int GetKeyFrame();
	void CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matR);


private:
	int							m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
public:
	void BuildVB(vector<ST_PNT_VERTEX>& vecVertex);

};

