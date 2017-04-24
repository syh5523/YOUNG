#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	: m_fRotDeltaX(0.0f)
	, m_pParentWorldTransMatrix(NULL),
	m_vLocalPosition(0, 0, 0),
	m_IsRotate(false), m_IsMove(false)
{
	D3DXMatrixIdentity(&m_matLocalTransMatrix);
	D3DXMatrixIdentity(&m_matWorldTransMatrix);
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	pChild->m_pParentWorldTransMatrix = &m_matWorldTransMatrix;
	pChild->m_IsMove = m_IsMove;

	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
	for each(auto p in m_vecChild)
	{
		p->Destroy();
	}
	delete this;
}

void cCubeNode::Setup()
{
	cCubePNT::Setup();
}

void cCubeNode::Update()
{
	cCubePNT::Update();

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	//È¸Àü
	D3DXMatrixRotationX(&matR, m_fRotDeltaX);

	D3DXMatrixTranslation(&matT, m_vLocalPosition.x,
		m_vLocalPosition.y,
		m_vLocalPosition.z);

	m_matLocalTransMatrix = matR * matT;

	m_matWorldTransMatrix = m_matLocalTransMatrix;

	if (m_pParentWorldTransMatrix)
	{
		m_matWorldTransMatrix *= *m_pParentWorldTransMatrix;
	}

	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Update();

		
		
		
		if (i == 0) continue;
		if (*m_IsMove)
		{
			if (i >= 1 && i < 3)
			{
				if (m_vecChild[i]->GetRotateDeltaX() < -1.2f) m_vecChild[i]->SetIsRotate(true);
				else if (m_vecChild[i]->GetRotateDeltaX() > 1.2f) m_vecChild[i]->SetIsRotate(false);
			}
			else
			{
				if (m_vecChild[i]->GetRotateDeltaX() < -1.2f) m_vecChild[i]->SetIsRotate(false);
				else if (m_vecChild[i]->GetRotateDeltaX() > 1.2f) m_vecChild[i]->SetIsRotate(true);
			}

			if (m_vecChild[i]->GetIsRotate())
			{
				if (i >= 1 && i < 3)	m_vecChild[i]->SetRotateDeltaX(m_vecChild[1]->GetRotateDeltaX() + 0.1f);
				else if (i >= 3) m_vecChild[i]->SetRotateDeltaX(m_vecChild[1]->GetRotateDeltaX() - 0.1f);
			}
			else
			{
				if (i >= 1 && i < 3) m_vecChild[i]->SetRotateDeltaX(m_vecChild[1]->GetRotateDeltaX() - 0.1f);
				else if (i >= 3) m_vecChild[i]->SetRotateDeltaX(-(m_vecChild[1]->GetRotateDeltaX() + 0.1f));
			}
		}
		else
		{
			m_vecChild[i]->SetRotateDeltaX(0.0f);
		}
	}	
}

void cCubeNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTransMatrix);

	cCubePNT::Render();
	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}




cCubeNode::~cCubeNode()
{
}
