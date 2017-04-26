#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	:m_fRotY(D3DX_PI),
	m_vDirection(0, 0, 1),
	m_vPosition(6, 0, 0), m_IsMove(false),
	m_IdleCount(0), m_IsIdle(false),
	m_SunDir(0,0,0), m_TimeForDay(0), m_SunX(0), m_SunY(0),
	m_DLightAmbientR(0.1f), m_DLightAmbientG(0.1f), m_DLightAmbientB(0.1f),
	m_DLightDiffuseR(0.1f), m_DLightDiffuseG(0.1f), m_DLightDiffuseB(0.1f),
	m_Destination_Index(4), m_Currunt_Index(0), m_Befor_Index(8), m_via_Index(2),
	m_Length(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);	
}


cCharacter::~cCharacter()
{

}

void cCharacter::Setup()
{	
	//첫번째 방향 정해주기
	D3DXVECTOR3 temp1, temp2;

	D3DXVec3Normalize(&temp1, &(m_vHexagon[m_via_Index].p - m_vPosition));
	D3DXVec3Normalize(&temp2, &(D3DXVECTOR3(6, 0, 1) - m_vPosition));
	m_fRotY -= acos(D3DXVec3Dot(&temp1, &temp2));


	m_Length = D3DXVec3Length(&(m_vHexagon[m_via_Index].p - m_vPosition)) / 5.0f;
}

void cCharacter::Update()
{
	//캐릭이동및 회전
	{
		m_IsMove = false;

		if (GetKeyState('A') & 0x8000)
			m_fRotY -= 0.037f;
		if (GetKeyState('D') & 0x8000)
			m_fRotY += 0.037f;
		if (GetKeyState('S') & 0x8000)
		{
			m_vPosition = m_vPosition + m_vDirection * 0.1f;
			m_IsMove = true;
		}
		else if (GetKeyState('W') & 0x8000)
		{
			m_vPosition = m_vPosition - m_vDirection * 0.1f;
			m_IsMove = true;
		}
	}

	//월드 구하기
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

		//Rotate
		D3DXMATRIXA16 matR, matRY;
		D3DXMatrixRotationY(&matRY, m_fRotY);
		matR = matRY;

		//방향 설정
		m_vDirection = D3DXVECTOR3(0, 0, 1);
		D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

		//Translate
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		m_matWorld = matS * matR * matT;
	}
	//캐릭터 이동
	MoveCharacter();

	//IDLE일 때
	{
		//if (!m_IsMove)
		//{
		//	//가만히 있고, 빛생성 안했을 때
		//	if (!m_IsIdle) m_IdleCount++;
		//	else
		//	{
		//		m_fRotY += 0.03f;
		//	}
		//	//가만히 있고 20초지나면 라이트 생성
		//	if (m_IdleCount > 100)
		//	{
		//		m_IsIdle = true;
		//		m_IdleCount = 0;
		//		CreateLight();
		//		g_pD3DDevice->LightEnable(0, false);
		//	}
		//}
		//else
		//{
		//	m_IsIdle = false;
		//	g_pD3DDevice->LightEnable(1, false);
		//	g_pD3DDevice->LightEnable(0, true);
		//}
	}

	//조명 이동
	//MoveDirectionLight();
}

void cCharacter::Render()
{


}


//-----------------------------------------------------------
//						  캐릭터 이동관련
//-----------------------------------------------------------
void cCharacter::MoveCharacter()
{
	//그냥 돌기

	
	
	
	//그냥 육각형 돌기
	{
		////목적지에 도달하면 앵글, 인덱스 바꿔주기
		//if (fabs(m_vPosition.x - m_vHexagon[m_Destination_Index].p.x) < EPSILON &&
		//	fabs(m_vPosition.z - m_vHexagon[m_Destination_Index].p.z) < EPSILON)
		//{
		//	m_fRotY -= D3DX_PI / 3;
		//	m_vPosition = m_vHexagon[m_Destination_Index].p;

		//	//목적지에 도달했으니 현재인덱스가 이전인덱스가 됨.
		//	m_Befor_Index = m_Currunt_Index;
		//	//목적지에 도달했으니 목적지가 현재 인덱스가 됨.
		//	m_Currunt_Index = m_Destination_Index;
		//	//목적지 인덱스는 다음점으로 이동
		//	m_Destination_Index += 2;
		//}
	}
	
	//원형으로 돌기
	{
		D3DXVECTOR3 temp1;
		D3DXVec3Normalize(&temp1, &(-m_vDirection));

		//첫번째 점
		temp1 = temp1* m_Length + m_vHexagon[m_Currunt_Index].p;
		//m_vVia.push_back(temp1);



		if (fabs(m_vPosition.x - temp1.x) < EPSILON)
		{
			m_fRotY -= D3DX_PI / 3;

			//첫번째 방향 정해주기
			D3DXVECTOR3 temp1, temp2, temp3;
			temp3 = m_vPosition;
			if (m_vPosition.z > 0)	temp3.z += 1;
			else 	temp3.z -= 1;
			
			D3DXVECTOR3 viaTemp;


			D3DXVec3Normalize(&temp1, &(m_vHexagon[m_via_Index].p - m_vPosition));
			D3DXVec3Normalize(&temp2, &(temp3 - m_vPosition));
			m_fRotY -= acos(D3DXVec3Dot(&temp1, &temp2));
		}

		////목적지에 도달하면 앵글, 인덱스 바꿔주기
		//if (fabs(m_vPosition.x - m_vHexagon[m_Destination_Index].p.x) < EPSILON &&
		//	fabs(m_vPosition.z - m_vHexagon[m_Destination_Index].p.z) < EPSILON)
		//{


		//	//------------------------------------------------------------
		//	//						인덱스 처리
		//	//-------------------------------------------------------------

		//	//목적지에 도달했으니 현재인덱스가 이전인덱스가 됨.
		//	m_Befor_Index = m_Currunt_Index;
		//	//목적지에 도달했으니 목적지가 현재 인덱스가 됨.
		//	m_Currunt_Index = m_Destination_Index;

		//	//목적지 저장
		//	m_Destination_Index += 4;
		//	//인덱스가 넘어설경우
		//	if (m_Destination_Index >= m_vHexagon.size()) m_Destination_Index = 0;
		//	//경유지 저장
		//	m_via_Index -= 2;
		//	if (m_via_Index < 0) m_via_Index = 10;

		//	//현재지점 초기화
		//	m_vPosition = m_vHexagon[m_Currunt_Index].p;

		//	//------------------------------------------------------------
		//	//						버텍스 저장
		//	//-------------------------------------------------------------

		//}
	}

	m_vPosition = m_vPosition - m_vDirection * 0.06f;


}



//-----------------------------------------------------------
//						  라이트 관련
//-----------------------------------------------------------
void cCharacter::MoveDirectionLight()
{

	if (m_TimeForDay > 850) m_TimeForDay = 0;
	//날이 시작되면 라이트 키기
	if (m_TimeForDay == 0)
	{
		m_SunX = 1;
		m_SunY = -0.5;
		m_DLightAmbientR = 0.2f;
		m_DLightAmbientG = 0.2f;
		m_DLightAmbientB = 0.2f;

		m_DLightDiffuseR = 0.1f;
		m_DLightDiffuseG = 0.1f;
		m_DLightDiffuseB = 0.1f;

		//스포트라이트 끄기
		g_pD3DDevice->LightEnable(1, false);
		g_pD3DDevice->LightEnable(2, false);
	}

	m_TimeForDay++;

	//태양 뜨기 시작
	if (m_TimeForDay <= 100)
	{
		//포지션 이동
		m_SunY += SUNPOSCHANGEVALUE;

		//컬러 변화
		m_DLightAmbientR += SUNPOSCHANGEVALUE;
		m_DLightAmbientG += SUNPOSCHANGEVALUE;
		m_DLightAmbientB += SUNPOSCHANGEVALUE;

		m_DLightDiffuseR += SUNPOSCHANGEVALUE;
		m_DLightDiffuseG += SUNPOSCHANGEVALUE;
		m_DLightDiffuseB += SUNPOSCHANGEVALUE;
	}
	//아침~낮동안 태양 움직임.
	else if (m_TimeForDay <= 300)
	{
		m_SunY += SUNPOSCHANGEVALUE;
		m_SunX -= SUNPOSCHANGEVALUE;

	}
	//낮~밤동안 태양 움직임
	else if (m_TimeForDay <= 500)
	{
		m_SunY -= SUNPOSCHANGEVALUE;
		m_SunX -= SUNPOSCHANGEVALUE;

		m_DLightDiffuseR += 0.0010f;
		m_DLightDiffuseG -= 0.0015f;
		m_DLightDiffuseB -= 0.0025f;
	}
	//태양 지기 시작
	else if (m_TimeForDay <= 600)
	{
		m_SunY -= SUNPOSCHANGEVALUE;

		//컬러 변화
		m_DLightAmbientR -= SUNPOSCHANGEVALUE;
		m_DLightAmbientG -= SUNPOSCHANGEVALUE;
		m_DLightAmbientB -= SUNPOSCHANGEVALUE;
	}


	//밤엔 어둡게
	else
	{
		CreateLight();
		g_pD3DDevice->LightEnable(2, true);

		m_SunX = 0;
		m_SunY = 1.0f;
		m_DLightAmbientR = 0.1f;
		m_DLightAmbientG = 0.1f;
		m_DLightAmbientB = 0.1f;

		m_DLightDiffuseR = 0.1f;
		m_DLightDiffuseG = 0.1f;
		m_DLightDiffuseB = 0.1f;
	}

	//밸류값 조정
	if (m_SunX > -EPSILON && m_SunX < EPSILON) m_SunX = 0;
	if (m_SunY > -EPSILON && m_SunY < EPSILON) m_SunY = 0;
	if (m_DLightAmbientR > -EPSILON && m_DLightAmbientR< EPSILON) m_DLightAmbientR = 0;
	if (m_DLightAmbientG > -EPSILON && m_DLightAmbientG< EPSILON) m_DLightAmbientG = 0;
	if (m_DLightAmbientB > -EPSILON && m_DLightAmbientB< EPSILON) m_DLightAmbientB = 0;
	if (m_DLightDiffuseR > -EPSILON && m_DLightDiffuseR < EPSILON) m_DLightDiffuseR = 0;
	if (m_DLightDiffuseG > -EPSILON && m_DLightDiffuseG < EPSILON) m_DLightDiffuseG = 0;
	if (m_DLightDiffuseB > -EPSILON && m_DLightDiffuseB < EPSILON) m_DLightDiffuseB = 0;

	//태양 위치 조정
	ZeroMemory(&m_CurruntLight, sizeof(D3DLIGHT9));
	g_pD3DDevice->GetLight(0, &m_CurruntLight);
	m_SunDir = D3DXVECTOR3(m_SunX, m_SunY, m_SunX);	
	D3DXVECTOR3 tempV = D3DXVECTOR3(0,0,0) - m_SunDir;
	D3DXVec3Normalize(&tempV, &tempV);
	m_CurruntLight.Direction = tempV;


	//태양 걸러 조정
	m_CurruntLight.Ambient = D3DXCOLOR(m_DLightAmbientR, m_DLightAmbientG, m_DLightAmbientB, 1.0f);
	m_CurruntLight.Diffuse = D3DXCOLOR(m_DLightDiffuseR, m_DLightDiffuseG, m_DLightDiffuseB, 1.0f);
	g_pD3DDevice->SetLight(0, &m_CurruntLight);
}

void cCharacter::OffAllLight()
{
	for (int i = 0; i < 3; ++i)
	{
		g_pD3DDevice->LightEnable(i, false);
	}	
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}

void cCharacter::CreateLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	g_pD3DDevice->GetLight(1, &stLight);
	D3DXVECTOR3 vPos(m_vPosition.x, m_vPosition.y + 5.0f, m_vPosition.z);
	stLight.Position = vPos;
	g_pD3DDevice->SetLight(1, &stLight);
	g_pD3DDevice->LightEnable(1, true);
}