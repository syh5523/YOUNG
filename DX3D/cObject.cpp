#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
{
}


cObject::~cObject()
{
}

void cObject::PushPNT(ST_PNT_VERTEX tagPNT)
{
	m_vPNT.push_back(tagPNT);
}
