#pragma once
#include "cBody.h"
#include "cCharacter.h"
class cCubeNode;

class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();

private:


public:
	cCubeNode* m_pRoot;

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

