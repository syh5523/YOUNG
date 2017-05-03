#include "stdafx.h"
#include "cCubeMan.h"

#include "cHead.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"
#include "cGroup.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL),
	m_pTexture(NULL),
	m_Destination_Index(4), m_Currunt_Index(0), m_via_Index(2),
	m_u(0), m_v(0), m_dist(0)
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
	m_savePos = m_vPosition;
	m_savePos2 = m_vHexagon[m_via_Index].p;
	//첫번째 방향 정해주기
	D3DXVECTOR3 temp1;

	D3DXVec3Normalize(&temp1, &(m_vHexagon[m_via_Index].p - m_vPosition));
	m_fRotY += (D3DX_PI - acos(D3DXVec3Dot(&D3DXVECTOR3(0, 0, 1), &temp1)));

	//경유지 버텍스
	//m_vVia
	float length1, length2;
	//목적지 1의 벡터 크기
	m_Lenght1 = D3DXVec3Length(&(m_vHexagon[m_Destination_Index].p - m_vPosition)) / CUVNUMBER;
	m_Lenght2 = D3DXVec3Length(&(m_vHexagon[m_Destination_Index].p - m_vHexagon[m_via_Index].p)) / CUVNUMBER;
	m_cuvNum = CUVNUMBER;

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

	//캐릭터 이동(베지어 곡선)
	MoveCharacter();

	//바닥 충돌
	IntersectTri();


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

void cCubeMan::GetFloor(vector<cGroup*> floor)
{
	m_vFloor = floor;
}

void cCubeMan::IntersectTri()
{
	bool IsFrontDown = false;
	bool IsBackDown = false;
	for (int i = 0; i < m_vFloor[0]->GetVertex().size() - 1; i += 3)
	{
		D3DXVECTOR3 v0 = m_vFloor[0]->GetVertex()[i].p * OBJECT_SCAILING;
		D3DXVECTOR3 v1 = m_vFloor[0]->GetVertex()[i + 1].p* OBJECT_SCAILING;
		D3DXVECTOR3 v2 = m_vFloor[0]->GetVertex()[i + 2].p* OBJECT_SCAILING;
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
		D3DXVec3TransformCoord(&v0, &v0, &matR);
		D3DXVec3TransformCoord(&v1, &v1, &matR);
		D3DXVec3TransformCoord(&v2, &v2, &matR);

		//주변만 검색하기
		if (D3DXVec3Length(&(m_vPosition - v0)) > 5 &&
			D3DXVec3Length(&(m_vPosition - v1)) > 5 &&
			D3DXVec3Length(&(m_vPosition - v2)) > 5) continue;

		//높이가 높은곳에 가게되면 못움직이게(전진)
		if (D3DXIntersectTri(&v0, &v1, &v2,
			&D3DXVECTOR3(m_vPosition.x - m_vDirection.x * EXAMDISTANCE, 1000, m_vPosition.z - m_vDirection.z * EXAMDISTANCE),
			&D3DXVECTOR3(0, -1, 0), &m_u, &m_v, &m_dist))
		{
			//전진시 올라 갈수 있는 위치이면 올라감
			if ((1000 - m_dist) - m_vPosition.y < POSSIBLEUPHEIGHT)
			{
				m_vPosition.y = 1000 - m_dist;
			}
			//높으면 못올라감
			else if ((1000 - m_dist) - m_vPosition.y > POSSIBLEUPHEIGHT) SetIsDontMoveS(true);

			//한번이라도 들어오게 되면 서페이스위에 있는것
			IsFrontDown = true;
		}

		
		
		//높이가 높은곳에 가게되면 못움직이게(후진)
		if (D3DXIntersectTri(&v0, &v1, &v2,
			&D3DXVECTOR3(m_vPosition.x + m_vDirection.x * EXAMDISTANCE, 1000, m_vPosition.z + m_vDirection.z * EXAMDISTANCE),
			&D3DXVECTOR3(0, -1, 0), &m_u, &m_v, &m_dist))
		{
			//올라 갈수 있는 위치이면 올라감
			if ((1000 - m_dist) - m_vPosition.y < POSSIBLEUPHEIGHT)
			{
				m_vPosition.y = 1000 - m_dist;
			}
			//높이가 낮은곳만 올라갈 수 있음
			else if ((1000 - m_dist) - m_vPosition.y > POSSIBLEUPHEIGHT) SetIsDontMoveW(true);

		}
		//한번이라도 들어오게 되면 서페이스위에 있는것
		IsBackDown = true;
	}
	
	//앞쪽이 떨어지는 곳일 때
	if (!IsFrontDown)
	{
		m_vPosition.y = 0;
	}
	//뒤쪽이 떨어지는 곳일 때
	if (!IsBackDown)
	{
		m_vPosition.y = 0;
	}
}



void cCubeMan::MoveCharacter()
{
	//-------------------------------------------------------
	//						곡선으로 돌기
	//-------------------------------------------------------
	////현재 포지션이 지난포지션보다 길이1만큼 더 갔다면 들어와라
	//if (fabs(m_vPosition.x - (m_savePos + (-m_vDirection * m_Lenght1)).x) < EPSILON &&
	//	fabs(m_vPosition.z - (m_savePos + (-m_vDirection * m_Lenght1)).z) < EPSILON)
	//{
	//	if (m_cuvNum == 0)
	//	{
	//		m_vPosition = m_vPosition - m_vDirection * 0.05f;
	//		return;
	//	}
	//	//비아에서 렝쓰만큼 간벡터 구하기
	//	D3DXVECTOR3 vtemp1;
	//	vtemp1 = m_vHexagon[m_Destination_Index].p - m_vHexagon[m_via_Index].p;
	//	D3DXVec3Normalize(&vtemp1, &vtemp1);
	//	vtemp1 *= m_Lenght2;
	//	m_savePos2 += vtemp1;

	//	//위 벡터에서 현재 포지션을 뺀 후 각도를 구해 빼줌
	//	vtemp1 = m_savePos2 - m_vPosition;
	//	D3DXVec3Normalize(&vtemp1, &vtemp1);

	//	m_fRotY -= (acos(D3DXVec3Dot(&vtemp1, &-m_vDirection)));

	//	//현재포지션 지정해줌
	//	//m_vPosition = m_savePos + (-m_vDirection * m_Lenght1);
	//	m_savePos = m_vPosition;

	//	m_cuvNum--;
	//}



	////목적지 도착
	//if (fabs(m_vPosition.x - m_vHexagon[m_Destination_Index].p.x) < EPSILON &&
	//	fabs(m_vPosition.z - m_vHexagon[m_Destination_Index].p.z) < EPSILON)
	//{
	//	//인덱스 갱신
	//	m_Currunt_Index = m_Destination_Index;
	//	m_via_Index = m_Currunt_Index + 2;
	//	m_Destination_Index += 4;
	//	if (m_Destination_Index >= m_vHexagon.size()) m_Destination_Index = 0;

	//	//방향 정해주기
	//	D3DXVECTOR3 temp1;

	//	D3DXVec3Normalize(&temp1, &(m_vHexagon[m_via_Index].p - m_vHexagon[m_Currunt_Index].p));
	//	m_fRotY -= acos(D3DXVec3Dot(&-m_vDirection, &temp1));

	//	m_savePos = m_vPosition;
	//	m_Lenght1 = D3DXVec3Length(&(m_vHexagon[m_Destination_Index].p - m_vPosition)) / CUVNUMBER;
	//	m_Lenght2 = D3DXVec3Length(&(m_vHexagon[m_Destination_Index].p - m_vHexagon[m_via_Index].p)) / CUVNUMBER;
	//
	//	m_savePos2 = m_vHexagon[m_via_Index].p;
	//	m_cuvNum = CUVNUMBER;
	//}

	//m_vPosition = m_vPosition - m_vDirection * 0.1f;
}


