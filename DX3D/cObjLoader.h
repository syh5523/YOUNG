#pragma once
#include "cObject.h"
#include "cMtltex.h"
#include "cObject.h"

#define STRBUF 1024


class cObjLoader
{
private:
	vector<cObject*>					m_vObject;
	map<string, cMtltex*>				m_mMtlTexture;

	//----------------------------------------------------------
	vector<D3DXVECTOR3>					m_vVertex;
	vector<D3DXVECTOR2>					m_vTextureUV;
	vector<D3DXVECTOR3>					m_vNormal;
	vector<D3DXVECTOR3>					m_vIndex_VTN;

	//----------------------------------------------------------

	

public:
	cObjLoader();
	~cObjLoader();

	void Setup();
	void Update();
	void Render();
};

