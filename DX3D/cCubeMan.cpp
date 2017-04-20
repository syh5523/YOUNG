#include "stdafx.h"
#include "cCubeMan.h"

#include "cBody.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"
#include "cHead.h"

cCubeMan::cCubeMan()
	:m_pRoot(NULL)
{
	//
}

cCubeMan::~cCubeMan()
{
}

void cCubeMan::Setup()
{
	m_pRoot = new cCubeNode;
	m_pRoot->SetParentWorldTM(&m_matWorld);

	cCubeNode* Body = new cBody;
	Body->Setup();
	m_pRoot->AddChild(Body);

	cCubeNode* Head = new cHead;
	Head->Setup();
	m_pRoot->AddChild(Head);

	cCubeNode* Lleg = new cLeftLeg;
	Lleg->Setup();
	m_pRoot->AddChild(Lleg);

	cCubeNode* Rarm = new cRightArm;
	Rarm->Setup();
	m_pRoot->AddChild(Rarm);

	cCubeNode* Larm = new cLeftArm;
	Larm->Setup();
	m_pRoot->AddChild(Larm);

	cCubeNode* Rleg = new cRightLeg;
	Rleg->Setup();
	m_pRoot->AddChild(Rleg);

}

void cCubeMan::Update()
{
	cCharacter::Update();


	m_pRoot->Update();
	//¿ùµå
	m_pRoot->SetParentWorldTM(&m_matWorld);

}

void cCubeMan::Render()
{
	cCharacter::Render();
	m_pRoot->Render();

}
