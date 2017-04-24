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


void cCubeNode::SetTexture(D3DXVECTOR2 Front1, D3DXVECTOR2 Front2, D3DXVECTOR2 Back1, D3DXVECTOR2 Back2,
	D3DXVECTOR2 Left1, D3DXVECTOR2 Left2, D3DXVECTOR2 Right1, D3DXVECTOR2 Right2, D3DXVECTOR2 Bottom1,
	D3DXVECTOR2 Bottom2, D3DXVECTOR2 Top1, D3DXVECTOR2 Top2)
{
	//¾Õ
	m_vecVertex[0].t = D3DXVECTOR2(Front1.x, Front2.y);
	m_vecVertex[1].t = D3DXVECTOR2(Front1.x, Front1.y);
	m_vecVertex[2].t = D3DXVECTOR2(Front2.x, Front1.y);

	m_vecVertex[3].t = D3DXVECTOR2(Front1.x, Front2.y);
	m_vecVertex[4].t = D3DXVECTOR2(Front2.x, Front1.y);
	m_vecVertex[5].t = D3DXVECTOR2(Front2.x, Front2.y);

	//µÚ
	m_vecVertex[6].t = D3DXVECTOR2(Back1.x, Back2.y);
	m_vecVertex[7].t = D3DXVECTOR2(Back2.x, Back1.y);
	m_vecVertex[8].t = D3DXVECTOR2(Back1.x, Back1.y);

	m_vecVertex[9].t = D3DXVECTOR2(Back1.x, Back2.y);
	m_vecVertex[10].t = D3DXVECTOR2(Back2.x, Back2.y);
	m_vecVertex[11].t = D3DXVECTOR2(Back2.x, Back1.y);

	//ÁÂ
	m_vecVertex[12].t = D3DXVECTOR2(Left1.x, Left2.y);
	m_vecVertex[13].t = D3DXVECTOR2(Left1.x, Left1.y);
	m_vecVertex[14].t = D3DXVECTOR2(Left2.x, Left1.y);

	m_vecVertex[15].t = D3DXVECTOR2(Left1.x, Left2.y);
	m_vecVertex[16].t = D3DXVECTOR2(Left2.x, Left1.y);
	m_vecVertex[17].t = D3DXVECTOR2(Left2.x, Left2.y);

	//¿ì
	m_vecVertex[18].t = D3DXVECTOR2(Right1.x, Right2.y);
	m_vecVertex[19].t = D3DXVECTOR2(Right1.x, Right1.y);
	m_vecVertex[20].t = D3DXVECTOR2(Right2.x, Right1.y);

	m_vecVertex[21].t = D3DXVECTOR2(Right1.x, Right2.y);
	m_vecVertex[22].t = D3DXVECTOR2(Right2.x, Right1.y);
	m_vecVertex[23].t = D3DXVECTOR2(Right2.x, Right2.y);

	//¹Ø
	m_vecVertex[24].t = D3DXVECTOR2(Bottom1.x, Bottom2.y);
	m_vecVertex[25].t = D3DXVECTOR2(Bottom1.x, Bottom1.y);
	m_vecVertex[26].t = D3DXVECTOR2(Bottom2.x, Bottom1.y);

	m_vecVertex[27].t = D3DXVECTOR2(Bottom1.x, Bottom2.y);
	m_vecVertex[28].t = D3DXVECTOR2(Bottom2.x, Bottom1.y);
	m_vecVertex[29].t = D3DXVECTOR2(Bottom2.x, Bottom2.y);

	//À§
	m_vecVertex[30].t = D3DXVECTOR2(Top1.x, Top2.y);
	m_vecVertex[31].t = D3DXVECTOR2(Top1.x, Top1.y);
	m_vecVertex[32].t = D3DXVECTOR2(Top2.x, Top1.y);

	m_vecVertex[33].t = D3DXVECTOR2(Top1.x, Top2.y);
	m_vecVertex[34].t = D3DXVECTOR2(Top2.x, Top1.y);
	m_vecVertex[35].t = D3DXVECTOR2(Top2.x, Top2.y);


	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].t.x *= SAMPLE_WIDTH;
		m_vecVertex[i].t.y *= SAMPLE_HEIGHT;
	}
}



cCubeNode::~cCubeNode()
{
}
