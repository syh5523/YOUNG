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

	//회전
	D3DXMatrixRotationX(&matR, m_fRotDeltaX);

	//IDLE일 때
	if (!(*m_IsMove))
	{
		D3DLIGHT9 stLight;
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		g_pD3DDevice->GetLight(0, &stLight);
		stLight.Position
		
		D3DXVECTOR3 vPos(0.0f, 10.0f, 0.0f);
		D3DXVECTOR3 vRan(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		stLight.Position = vPos;
		stLight.Range = 10.0f;
		g_pD3DDevice->SetLight(0, &stLight);
		g_pD3DDevice->LightEnable(0, false);
	}

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
