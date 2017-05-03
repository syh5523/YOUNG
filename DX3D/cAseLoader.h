#pragma once
class cGroup;
class cMtlTex;

#define BUFFER 1024

class cAseLoader
{
public:
	cAseLoader();
	~cAseLoader();

private:
	map<int, cMtlTex*>	m_mapMtlTex;
	map<string, D3DXMATRIXA16*> m_mapMatWorld;

public:

	void LoadAse(OUT vector<cGroup*>& vecGroup, IN char * szFolder, IN char * szFile);
};

