#pragma once
#include "cObject.h"
#include "cMtltex.h"

#define STRBUF 1024

struct tagObjLoader
{
	string								useMtlName;

	vector<D3DXVECTOR3>					vVertex;
	vector<D3DXVECTOR2>					vTextureUV;
	vector<D3DXVECTOR3>					vNormal;

	vector<D3DXVECTOR3>					vIndex_VTN;

	vector<ST_PNT_VERTEX>				PNT;
};

struct tagMaterialGroup
{
	string								imgName;
	map<string, D3DMATERIAL9>			mapMaterial;
};

class cObjLoader
{
private: 
	int									m_Index_CurruntGruop;
	

	vector<tagObjLoader>				m_ObjGroup;
	vector<tagMaterialGroup>			m_materGroup;

	////////////-----------------대충그리기 위한 것들
	LPDIRECT3DTEXTURE9					m_Texture;

public:
	cObjLoader();
	~cObjLoader();

	void Setup();
	void Update();
	void Render();
};

