#pragma once
#include "cCubePNT.h"
class cCubeNode : public cCubePNT
{
public:
	cCubeNode();

protected:
	D3DXVECTOR3		m_vLocalPosition;
	D3DXMATRIXA16	m_matLocalTransMatrix;
	D3DXMATRIXA16	m_matWorldTransMatrix;
	std::vector<cCubeNode*>	m_vecChild;


	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTransMatrix, ParentWorldTransMatrix)
	SYNTHESIZE(float, m_fRotDeltaX, RotateDeltaX)
	SYNTHESIZE(bool, m_IsRotate, IsRotate)
	SYNTHESIZE(bool*, m_IsMove, IsMove)
	



public:


	virtual	~cCubeNode();

	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(D3DXVECTOR2 Front1, D3DXVECTOR2 Front2, D3DXVECTOR2 Back1, D3DXVECTOR2 Back2,
		D3DXVECTOR2 Left1, D3DXVECTOR2 Left2, D3DXVECTOR2 Right1, D3DXVECTOR2 Right2, D3DXVECTOR2 Bottom1,
		D3DXVECTOR2 Bottom2, D3DXVECTOR2 Top1, D3DXVECTOR2 Top2);
};

