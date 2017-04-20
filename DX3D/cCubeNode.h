#pragma once
#include "cCubePNT.h"

class cCubeNode : public cCubePNT
{
public:
	cCubeNode();
	
protected:
	D3DXVECTOR3			m_vLocalPos;										//ū��ü�� ���� ����������
	D3DXMATRIXA16		m_matLocalTM;										//���� ������ǥ
	D3DXMATRIXA16		m_matWorldTM;										//���� ������ǥ
	D3DXMATRIXA16		m_matScailing;
	bool				m_IsRotate;
	//TM : transMatrix;
	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM)				//�θ��� ������ǥ
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

