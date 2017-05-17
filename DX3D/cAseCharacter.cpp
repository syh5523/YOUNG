#include "stdafx.h"
#include "cAseCharacter.h"


cAseCharacter::cAseCharacter()
	:m_pRunFrame(NULL)
	, m_pStandingFrame(NULL)
	, m_pFont(0)
	, m_pRunFrameMesh(NULL)
	, m_pStandingFrameMesh(NULL)
{
}


cAseCharacter::~cAseCharacter()
{
	m_pRunFrameMesh->Destroy();
	m_pStandingFrameMesh->Destroy();
	m_pStandingFrame->Destroy();
	m_pRunFrame->Destroy();
	SAFE_RELEASE(m_pFont);
}

void cAseCharacter::Setup()
{
	cAseCharacterMove::Setup();

	cAseLoader load;
	m_pStandingFrame = load.LoadAse("woman/woman_01_all_stand.ASE");
	m_pStandingFrame->SetIsMove(false);
	m_pStandingFrame->Setup(false);

	cAseLoader load2;
	m_pRunFrame = load2.LoadAse("woman/woman_01_all.ASE");
	m_pRunFrame->SetIsMove(true);
	m_pRunFrame->Setup(false);

	cAseLoader loadMesh;
	m_pStandingFrameMesh = loadMesh.LoadAse("woman/woman_01_all_stand.ASE");
	m_pStandingFrameMesh->SetIsMove(false);
	m_pStandingFrameMesh->Setup(true);

	cAseLoader loadMesh1;
	m_pRunFrameMesh = loadMesh1.LoadAse("woman/woman_01_all.ASE");
	m_pRunFrameMesh->SetIsMove(false);
	m_pRunFrameMesh->Setup(true);

	//--폰트
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_LIGHT;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	AddFontResource("font/umberto.ttf");
	strcpy_s(fd.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void cAseCharacter::Update()
{
	cAseCharacterMove::Update();

	if (m_IsMove)
	{
		//그냥 렌더했을 경우
		m_pRunFrame->Update(m_pRunFrame->GetKeyFrame(), &m_matWorld);
		if (m_IsBooster) m_pRunFrame->SetfFrameSpeed(4);
		else m_pRunFrame->SetfFrameSpeed(2);

		//메쉬렌더 했을 경우
		m_pRunFrameMesh->Update(m_pRunFrameMesh->GetKeyFrame(), &m_matWorld);
		if (m_IsBooster) m_pRunFrameMesh->SetfFrameSpeed(4);
		else m_pRunFrameMesh->SetfFrameSpeed(2);
	}
	else
	{
		//그냥 렌더했을 경우
		m_pStandingFrame->Update(m_pStandingFrame->GetKeyFrame(), &m_matWorld);
		//메쉬렌더 했을 경우
		m_pStandingFrameMesh->Update(m_pStandingFrameMesh->GetKeyFrame(), &m_matWorld);
	}



}

void cAseCharacter::Render()
{

	//그냥 렌더했을 경우
	if (m_IsMove)	m_pRunFrame->Render();
	else m_pStandingFrame->Render();

	
	//메쉬렌더 했을 경우
	if (m_IsMove)	m_pRunFrameMesh->Render();
	else m_pStandingFrameMesh->Render();



	//--폰트
	string str, str1;
	str = to_string(frame);
	str1 = to_string(MeshFrame);


	string sText("기존렌더:" + str + "  메쉬렌더:" + str1);
	RECT rc;
	SetRect(&rc, 10, 10, 50, 50);
	m_pFont->DrawTextA(NULL, sText.c_str(), sText.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));
}

