#pragma once
#include "cMtltex.h"

class cObject 
{
private:
	SYNTHESIZE(string, m_sObjName, ObjName)
	SYNTHESIZE(string, m_sMtlName, MtlName)
	SYNTHESIZE(vector<ST_PNT_VERTEX>, m_vPNT, PNT)
	
public:
	cObject();
	~cObject();

	void PushPNT(ST_PNT_VERTEX tagPNT);
	

};

