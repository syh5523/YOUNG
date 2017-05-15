#include "stdafx.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cMtlTex.h"

cObjLoader::cObjLoader()
	:m_lpMesh(NULL)
{
}


cObjLoader::~cObjLoader()
{
	SAFE_RELEASE(m_lpMesh);
}
void cObjLoader::Load(OUT std::vector<cGroup*>& vecGroup, IN char * szFolder, IN char * szFile)
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<ST_PNT_VERTEX> vecVertex;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}

	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapMtlTex.clear();
}
void cObjLoader::LoadMtlLib(char * szFolder, char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	DWORD nSubset = 0;

	std::string sMtlName;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		//머터리얼 이름
		if (szTemp[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);

			if (m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				
			}
		}

		else if (szTemp[0] == 'K')
		{
			if (szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			else if (szTemp[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if (szTemp[1] == 's')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		//파워
		else if (szTemp[0] == 'd')
		{
			float d;
			sscanf_s(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		//텍스쳐 이름
		else if (szTemp[0] == 'm')
		{
			char szTexFile[1024];
			sscanf_s(szTemp, "%*s %s", szTexFile, 1024);
			sFullPath = std::string(szFolder);
			sFullPath += (std::string("/") + std::string(szTexFile));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);

			m_mapMtlTex[sMtlName]->SetSubset(nSubset);
			nSubset++;
		}
	}

	fclose(fp);
}

void cObjLoader::LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface, IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pMat)
{
	std::vector<D3DXVECTOR3> vecV;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);
			for (int i = 0; i < 3; ++i)
			{
				vecSurface.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}

	fclose(fp);

	if (pMat)
	{
		for (size_t i = 0; i < vecSurface.size(); ++i)
		{
			D3DXVec3TransformCoord(&vecSurface[i], &vecSurface[i], pMat);
		}
	}
}

LPD3DXMESH cObjLoader::LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char * szFolder, IN char * szFile)
{
	vector<D3DXVECTOR3> vecV;					//버텍스 
	vector<D3DXVECTOR2> vecVT;					//텍스쳐
	vector<D3DXVECTOR3> vecVN;
	vector<DWORD> vecSubset;
	vector<ST_PNT_VERTEX> vecVertex;
	
	string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);

			for each(auto it in m_mapMtlTex)
			{
				cMtlTex* mtltex = new cMtlTex;
				mtltex->SetMaterial(it.second->GetMaterial());
				mtltex->SetTexture(it.second->GetTexture());
				vecMtlTex.push_back(mtltex);
			}
		}
		else if (szTemp[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				/*cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				pGroup->SetSubset(m_mapMtlTex[sMtlName]->GetSubset());
				vecGroup.push_back(pGroup);
				vecVertex.clear();*/
			
				//vecMtlTex.push_back(m_mapMtlTex[sMtlName]);
				
			}
		}
		
		else if (szTemp[0] == 'v')
		{

			//버텍스 
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);

				vecV.push_back(D3DXVECTOR3(x, y, z));
			
			}

			//텍스쳐
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}

			//노말
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}

		//머터리얼 이름
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}

		//인덱스
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}

			vecSubset.push_back(m_mapMtlTex[sMtlName]->GetSubset());
		}
	}

	fclose(fp);


	
	D3DXCreateMeshFVF(vecVertex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF,
	g_pD3DDevice, &m_lpMesh);

	//버텍스 저장
	ST_PNT_VERTEX* meshV = 0;
	m_lpMesh->LockVertexBuffer(0, (LPVOID*)&meshV);	
	memcpy(meshV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_lpMesh->UnlockVertexBuffer();

	//인덱스 저장
	WORD* Index = 0;
	m_lpMesh->LockIndexBuffer(0, (LPVOID*)&Index);
	
	for (int i = 0; i < vecVertex.size(); ++i)
	{
		Index[i] = i;
	}
	
	m_lpMesh->UnlockIndexBuffer();

	//어트리뷰트 저장
	DWORD* attribute = 0;

	m_lpMesh->LockAttributeBuffer(0, &attribute);
	
	for (int i = 0; i < vecSubset.size(); ++i)
	{
		attribute[i] = vecSubset[i];
	}

	m_lpMesh->UnlockAttributeBuffer();


	vector<DWORD> adjacencyBuffer(m_lpMesh->GetNumFaces() * 3);
	m_lpMesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	m_lpMesh->OptimizeInplace(	
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&adjacencyBuffer[0],
			0, 0, 0);



	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapMtlTex.clear();


	return m_lpMesh;
}
