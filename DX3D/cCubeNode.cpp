#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	:m_IsRotate(false)
{
	
}


cCubeNode::~cCubeNode()
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		SAFE_DELETE(m_vecChild[i]);
	}
}
//---------------------------------------------
void cCubeNode::Setup()
{
}

void cCubeNode::Update()
{
	//회전
	

	if (m_fRotDeltaX < -1.5f) m_IsRotate = true;
	else if (m_fRotDeltaX > 1.5f) m_IsRotate = false;

	if (m_IsRotate) m_fRotDeltaX += 0.1f;
	else m_fRotDeltaX -= 0.1f;

	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		

		D3DXMATRIXA16 matR;
		D3DXMatrixIdentity(&matR);
		D3DXMatrixRotationX(&matR, m_vecChild[i]->m_fRotDeltaX);

		//이동
		D3DXMATRIXA16 matTranslation;
		D3DXMatrixTranslation(&matTranslation, m_vecChild[i]->m_vLocalPos.x, 
			m_vecChild[i]->m_vLocalPos.y, m_vecChild[i]->m_vLocalPos.z);

		m_vecChild[i]->m_matLocalTM = matR * matTranslation;

		m_vecChild[i]->m_matWorldTM = m_vecChild[i]->m_matLocalTM  * *m_pParentWorldTM;

		if (i >= 2 && i < 4) m_vecChild[i]->SetrotDeltaX(m_fRotDeltaX);
		else if (i >= 4)	m_vecChild[i]->SetrotDeltaX(-m_fRotDeltaX);
	}
}

void cCubeNode::Render()
{
	//몸통
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecChild[i]->m_matWorldTM);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecChild[i]->m_vecVertex.size() / 3,
			&m_vecChild[i]->m_vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
}

