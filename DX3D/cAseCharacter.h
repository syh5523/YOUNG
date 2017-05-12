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


public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

