#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0), m_IsMove(false),
	m_IdleCount(0), m_IsIdle(false),
	m_SunDir(0,0,0), m_TimeForDay(0), m_SunX(0), m_SunY(0),
	m_DLightAmbientR(0.1f), m_DLightAmbientG(0.1f), m_DLightAmbientB(0.1f),
	m_DLightDiffuseR(0.1f), m_DLightDiffuseG(0.1f), m_DLightDiffuseB(0.1f)

{
	D3DXMatrixIdentity(&m_matWorld);
	
}


cCharacter::~cCharacter()
{

}

void cCharacter::Setup()
{
	//
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

		//조명
		if (GetKeyState('1') & 0x8000)
		{
			CreateDirectionLight();
		}
		if (GetKeyState('2') & 0x8000)
		{
			CreateSpotLight();	
		}
		if (GetKeyState('3') & 0x8000)
		{
			CreatePointLight();
		}

	}

	//조명 이동
	MoveDirectionLight();


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
}

void cCharacter::Render()
{
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

void cCharacter::CreateSpotLight()
{
	OffAllLight();
	g_pD3DDevice->LightEnable(1, true);
}

void cCharacter::CreatePointLight()
{
	OffAllLight();
	g_pD3DDevice->LightEnable(2, true);
}

void cCharacter::CreateDirectionLight()
{
	OffAllLight();
	g_pD3DDevice->LightEnable(0, true);
}

void cCharacter::MoveSpotLight()
{
}

void cCharacter::MovePointLight()
{
}

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

		m_DLightDiffuseR = 0.0f;
		m_DLightDiffuseG = 0.0f;
		m_DLightDiffuseB = 0.0f;

		//스포트라이트 끄기
		g_pD3DDevice->LightEnable(1, false);
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

		m_DLightDiffuseR += 0.0005f;
		m_DLightDiffuseG -= 0.0025f;
		m_DLightDiffuseB -= 0.0035f;
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
