#include "stdafx.h"
#include "cAseCharacter.h"


cAseCharacter::cAseCharacter()
	:m_pRunFrame(NULL)
	, m_pStandingFrame(NULL)
	, m_pFont(0)
{
}


cAseCharacter::~cAseCharacter()
{
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
	m_pStandingFrame->Setup();

	cAseLoader load2;
	m_pRunFrame = load2.LoadAse("woman/woman_01_all.ASE");
	m_pRunFrame->SetIsMove(true);
	m_pRunFrame->Setup();


	//--폰트
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	fd.Weight = FW_MEDIUM;
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
		m_pRunFrame->Update(m_pRunFrame->GetKeyFrame(), &m_matWorld);
		if (m_IsBooster) m_pRunFrame->SetfFrameSpeed(4);
		else m_pRunFrame->SetfFrameSpeed(2);
	}
	else
	{
		m_pStandingFrame->Update(m_pStandingFrame->GetKeyFrame(), &m_matWorld);
	}


}

void cAseCharacter::Render()
{
	DWORD time1, time2;

	time1 = GetTickCount();

	if (m_IsMove)	m_pRunFrame->Render();	
	else m_pStandingFrame->Render();
	
	time2 = GetTickCount();

	m_Frame = time2 - time1;

	//--폰트
	string str, str1;
	str = to_string(m_Frame);
	str1 = to_string(m_Frame1);


	string sText(str + "  " + str1);
	RECT rc;
	SetRect(&rc, 100, 100, 101, 100);
	m_pFont->DrawTextA(NULL, sText.c_str(), sText.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));
}

