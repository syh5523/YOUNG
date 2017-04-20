#pragma once
#include "cCubePNT.h"

class cCubeNode : public cCubePNT
{
public:
	cCubeNode();
	
protected:
	D3DXVECTOR3			m_vLocalPos;										//큰객체들 간의 로컬포지션
	D3DXMATRIXA16		m_matLocalTM;										//나의 로컬좌표
	D3DXMATRIXA16		m_matWorldTM;										//나의 월드좌표
	D3DXMATRIXA16		m_matScailing;
	bool				m_IsRotate;
	//TM : transMatrix;
	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM)				//부모의 월드좌표
	SYNTHESIZE(float, m_fRotDeltaX, rotDeltaX)

	
	std::vector<cCubeNode*>		m_vecChild;

public:
	virtual ~cCubeNode();

	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

