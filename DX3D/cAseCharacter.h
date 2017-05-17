#pragma once

#include "cFrame.h"
#include "cAseCharacterMove.h"
#include "cAseLoader.h"

class cAseCharacter : public cAseCharacterMove
{
public:
	cAseCharacter();
	~cAseCharacter();

private:
	cFrame*					m_pRunFrame;
	cFrame*					m_pStandingFrame;

	cFrame*					m_pRunFrameMesh;
	cFrame*					m_pStandingFrameMesh;

	SYNTHESIZE(DWORD, m_Frame, Frame)
	SYNTHESIZE(DWORD, m_Frame1, Frame1)
	LPD3DXFONT		  m_pFont;
public:
	virtual void Setup() override;
	virtual void Update() override;
	void Render();
};

