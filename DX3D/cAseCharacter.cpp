#include "stdafx.h"
#include "cAseCharacter.h"


cAseCharacter::cAseCharacter()
	:m_pRunFrame(NULL)
	, m_pStandingFrame(NULL)
{
}


cAseCharacter::~cAseCharacter()
{
	m_pStandingFrame->Destroy();
	m_pRunFrame->Destroy();
}

void cAseCharacter::Setup()
{
	cAseCharacterMove::Setup();

	cAseLoader load;
	m_pStandingFrame = load.LoadAse("woman/woman_01_all_stand.ASE");
	m_pStandingFrame->SetIsMove(false);

	cAseLoader load2;
	m_pRunFrame = load2.LoadAse("woman/woman_01_all.ASE");
	m_pRunFrame->SetIsMove(true);

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
	cAseCharacterMove::Render();
	if (m_IsMove)	m_pRunFrame->Render();	
	else m_pStandingFrame->Render();
	
}

