#include "stdafx.h"
#include "cObjLoader.h"


cObjLoader::cObjLoader()
	:m_Index_CurruntGruop(0)
{
}


cObjLoader::~cObjLoader()
{
	SAFE_RELEASE(m_Texture);
}


void cObjLoader::Setup()
{
	FILE* fp;
	fopen_s(&fp, "box.obj", "r");
	char szBuf[STRBUF] = { 0, };
	char saveBuf[STRBUF] = { 0, };
	char GroupName[STRBUF];
	float x;
	float y;
	float z;

	int BufNum = 0;
	
	//자료파싱하기
	while (true)
	{	
		if (feof(fp)) break;

		//한줄씩 읽어옴
		fgets(szBuf, sizeof(szBuf), fp);
		
		//# == 주석이므로 skip함
		if (szBuf[0] == '#' || szBuf[0] == '\n') continue;

		//첫번째 단어 저장
		string firstWord;
		sscanf_s(szBuf, "%s", saveBuf, sizeof(saveBuf));
		firstWord = saveBuf;

		if (firstWord == "g")
		{
			//m_Index_CurruntGruop++;
			tagObjLoader tempObjLoader;
			ZeroMemory(&tempObjLoader, sizeof(tagObjLoader));

			m_ObjGroup.push_back(tempObjLoader);
			
		}


		//mtlLib(머터리얼 라이브러리)는 다읽고 일어봐야 하므로 저장해둠.
		if (firstWord == "mtllib")
		{
			sscanf_s(szBuf, "%*s%s", &GroupName, sizeof(GroupName));
			continue;
		}
		
		//v라면 버텍스 
		if(firstWord == "v")
		{
			sscanf_s(szBuf, "%*s%f%f%f", &x, &y, &z);

			D3DXVECTOR3 tempVertex = D3DXVECTOR3(x, y, z);
			m_ObjGroup[m_Index_CurruntGruop].vVertex.push_back(tempVertex);

			continue;
		}

			//vn라면 법선벡터
		if (firstWord == "vt")
		{
			sscanf_s(szBuf, "%*s%f%f", &x, &y);

			D3DXVECTOR2 tempUV = D3DXVECTOR2(x, y);
			m_ObjGroup[m_Index_CurruntGruop].vTextureUV.push_back(tempUV);
			continue;
		}

		//vn라면 법선벡터
		if (firstWord == "vn")
		{
			sscanf_s(szBuf, "%*s%f%f%f", &x, &y, &z);

			D3DXVECTOR3 tempNormal = D3DXVECTOR3(x, y, z);
			m_ObjGroup[m_Index_CurruntGruop].vNormal.push_back(tempNormal);

			continue;
		}


		//인덱스
		if (firstWord == "f")
		{
			//첫번째 
			sscanf_s(szBuf, "%*s %f %*c %f %*c %f", &x, &y, &z);
			D3DXVECTOR3 tempIndex = D3DXVECTOR3(x-1, y-1, z-1);
			m_ObjGroup[m_Index_CurruntGruop].vIndex_VTN.push_back(tempIndex);

			//두번째
			sscanf_s(szBuf, "%*s%*s %f %*c %f %*c %f", &x, &y, &z);
			tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_ObjGroup[m_Index_CurruntGruop].vIndex_VTN.push_back(tempIndex);


			//세번째
			sscanf_s(szBuf, "%*s %*s %*s %f %*c %f %*c %f", &x, &y, &z);
			tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_ObjGroup[m_Index_CurruntGruop].vIndex_VTN.push_back(tempIndex);
			continue;

		}

		//그룹 네임
		if (firstWord == "usemtl")
		{
			char c[128];

			sscanf_s(szBuf, "%*s %s", &c, sizeof(c));
			m_ObjGroup[m_Index_CurruntGruop].useMtlName = c;
		}
	}

	//PNT 정리하기	
	for (int i = 0; i < m_ObjGroup.size(); ++i)
	{
		for (int j = 0; j < m_ObjGroup[i].vIndex_VTN.size(); ++j)
		{
			ST_PNT_VERTEX temp;
			ZeroMemory(&temp, sizeof(temp));

			temp.p = m_ObjGroup[i].vVertex[m_ObjGroup[i].vIndex_VTN[j].x];
			temp.t = m_ObjGroup[i].vTextureUV[m_ObjGroup[i].vIndex_VTN[j].y];
			temp.n = m_ObjGroup[i].vNormal[m_ObjGroup[i].vIndex_VTN[j].z];

			m_ObjGroup[i].PNT.push_back(temp);
		}
	}

	fclose(fp);

	//머터리얼 불러오기 
	fopen_s(&fp, GroupName, "r");

	//머터리얼 자료 파싱하기
	//m_Index_CurruntGruop = -1;
	while (true)
	{
		if (feof(fp)) break;

		//한줄씩 읽어옴
		fgets(szBuf, sizeof(szBuf), fp);

		//# == 주석이므로 skip함
		if (szBuf[0] == '#' || szBuf[0] == '\n') continue;

		//첫번째 단어 저장
		string firstWord;
		sscanf_s(szBuf, "%s", saveBuf, sizeof(saveBuf));
		firstWord = saveBuf;


		if (firstWord == "newmtl")
		{
			//m_Index_CurruntGruop++;
			sscanf_s(szBuf, "%*s%s", &GroupName, sizeof(GroupName));
			string str = GroupName;


			D3DMATERIAL9 tempMat;
			tagMaterialGroup temp;
			
			temp.mapMaterial.insert(make_pair(str, tempMat));
			m_materGroup.push_back(temp);
			continue;
		}
		if (firstWord == "ka")
		{
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);		
			m_materGroup[m_Index_CurruntGruop].mapMaterial.find(GroupName)->second.Ambient 
				= D3DXCOLOR(x, y, z, 1.0f);

		}
		if (firstWord == "kd")
		{
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
			m_materGroup[m_Index_CurruntGruop].mapMaterial.find(GroupName)->second.Diffuse 
				= D3DXCOLOR(x, y, z, 1.0f);
		}
		if (firstWord == "ks")
		{
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
			m_materGroup[m_Index_CurruntGruop].mapMaterial.find(GroupName)->second.Specular 
				= D3DXCOLOR(x, y, z, 1.0f);

		}
		if (firstWord == "map_Kd")
		{

			char strTemp[128];

			sscanf_s(szBuf, "%*s%s", &strTemp, sizeof(strTemp));

			m_materGroup[m_Index_CurruntGruop].imgName = strTemp;
		}

	}
	fclose(fp);

	//텍스쳐 세팅
	ZeroMemory(&m_Texture, sizeof(LPDIRECT3DTEXTURE9));
	D3DXCreateTextureFromFile(g_pD3DDevice, "box.JPG", &m_Texture);
}

void cObjLoader::Update()
{
}

void cObjLoader::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_ObjGroup[0].PNT.size() / 3,
		&m_ObjGroup[0].PNT[0], sizeof(ST_PNT_VERTEX));



}
