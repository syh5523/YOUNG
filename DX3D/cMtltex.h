#pragma once

class cMtltex 
{
private:
	SYNTHESIZE(string, m_sImgName, ImgName)
	SYNTHESIZE(string, m_sMtlName, MtlName)
	SYNTHESIZE(D3DMATERIAL9, m_stMtl, Mtl)
	SYNTHESIZE(float, m_Power, Power)

public:
	cMtltex();
	~cMtltex();

};

