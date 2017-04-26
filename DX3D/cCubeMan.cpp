#include "stdafx.h"
#include "cCubeMan.h"

#include "cHead.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL),
	m_pTexture(NULL),
	m_Destination_Index(2), m_Currunt_Index(0), m_Befor_Index(10), m_via_Index(0),
	m_Length(0.0f)
{

	
}


cCubeMan::~cCubeMan()
{
	SAFE_RELEASE(m_pTexture);

	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCubeMan::RecieveHexaVertext(std::vector<ST_PC_VERTEX> *vertext)
{
	m_vHexagon = *vertext;

}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	//첫번째 방향 정해주기
	D3DXVECTOR3 temp1;

	D3DXVec3Normalize(&temp1, &(m_vHexagon[m_Destination_Index].p - m_vPosition));
	m_fRotY += (D3DX_PI - acos(D3DXVec3Dot(&D3DXVECTOR3(0, 0, 1), &temp1)));

	m_Length = D3DXVec3Length(&(m_vHexagon[m_via_Index].p - m_vPosition)) / 5.0f;

	//머터리얼
	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));
	m_stMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMaterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//텍스처
	ZeroMemory(&m_pTexture, sizeof(LPDIRECT3DTEXTURE9));
	D3DXCreateTextureFromFile(g_pD3DDevice, "sample1.PNG", &m_pTexture);

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTransMatrix(&m_matWorld);
	pBody->SetIsMove(&m_IsMove);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cLeftArm* pLeftArm = new cLeftArm;
	pLeftArm->Setup();
	m_pRoot->AddChild(pLeftArm);

	cRightLeg* pRightLeg = new cRightLeg;
	pRightLeg->Setup();
	m_pRoot->AddChild(pRightLeg);

	cRightArm* pRightArm = new cRightArm;
	pRightArm->Setup();
	m_pRoot->AddChild(pRightArm);

	cLeftLeg* pLeftLeg = new cLeftLeg;
	pLeftLeg->Setup();
	m_pRoot->AddChild(pLeftLeg);

	

}

void cCubeMan::Update()
{
	cCharacter::Update();
	if (m_pRoot)
		m_pRoot->Update();

	//캐릭터 이동
	MoveCharacter();
}

void cCubeMan::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMaterial);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	cCharacter::Render();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pRoot)
		m_pRoot->Render();

	g_pD3DDevice->SetTexture(0, NULL);
}


void cCubeMan::MoveCharacter()
{

	//그냥 육각형 돌기
	{

		//-------------------------------------------------------
		//						그냥 돌기
		//-------------------------------------------------------

		//목적지 도착
		if (fabs(m_vPosition.x - m_vHexagon[m_Destination_Index].p.x) < EPSILON &&
			fabs(m_vPosition.z - m_vHexagon[m_Destination_Index].p.z) < EPSILON)
		{
			//인덱스 갱신
			m_Currunt_Index = m_Destination_Index;
			m_Destination_Index += 2;
			if (m_Destination_Index >= m_vHexagon.size()) m_Destination_Index = 0;

			//다음 목적지로 가능 방향의 벡터 구하기
			D3DXVECTOR3 vtemp1;
			vtemp1 = m_vHexagon[m_Destination_Index].p - m_vHexagon[m_Currunt_Index].p;
			D3DXVec3Normalize(&vtemp1, &vtemp1);

			m_fRotY -= acos(D3DXVec3Dot(&vtemp1, &-m_vDirection));

			m_vPosition = m_vHexagon[m_Currunt_Index].p;
	
		}
	}



	m_vPosition = m_vPosition - m_vDirection * 0.1f;


}