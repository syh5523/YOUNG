#pragma once
#include "cCubeMan.h"
#include "cCubeNode.h"

class cBody : public cCubeNode
{
public:
	cBody();
	~cBody();

private:
	

public:
	virtual void Setup() override;
};

