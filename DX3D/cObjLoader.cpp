#include "stdafx.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cMtlTex.h"

cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
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

		//���͸��� �̸�
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
		//�Ŀ�
		else if (szTemp[0] == 'd')
		{
			float d;
			sscanf_s(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		//�ؽ��� �̸�
		else if (szTemp[0] == 'm')
		{
			char szTexFile[1024];
			sscanf_s(szTemp, "%*s %s", szTexFile, 1024);
			sFullPath = std::string(szFolder);
			sFullPath += (std::string("/") + std::string(szTexFile));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
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
	vector<D3DXVECTOR3> vecV;					//���ؽ� 
	vector<D3DXVECTOR2> vecVT;					//�ؽ���
	vector<D3DXVECTOR3> vecVN;
	vector<DWORD> vecSubset;
	vector<ST_PNT_VERTEX> vecVertex;
	string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	int size = 0;
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
				cMtlTex* pmtl = new cMtlTex;
				pmtl->SetMaterial(it.second->GetMaterial());
				pmtl->SetTexture(it.second->GetTexture());
				vecMtlTex.push_back(pmtl);
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
				int attributeNum = -1;
				int mapCountNum = 0;
				for each (auto it in m_mapMtlTex)
				{
					if (it.first == sMtlName)
					{
						attributeNum = mapCountNum;
						break;
					}
					else mapCountNum++;
				}
				for (int i = 0; i < size; ++i)
				{
					vecSubset.push_back(attributeNum);
				}				
				size = 0;				
			}
		}
		
		else if (szTemp[0] == 'v')
		{

			//���ؽ� 
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);

				vecV.push_back(D3DXVECTOR3(x, y, z));
			
			}

			//�ؽ���
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}

			//�븻
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}

		//���͸��� �̸�
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}

		//�ε���
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
			size++;
			
		}
	}

	fclose(fp);


	LPD3DXMESH pMesh;

	D3DXCreateMeshFVF(vecVertex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF,
	g_pD3DDevice, &pMesh);

	//���ؽ� ����
	ST_PNT_VERTEX* meshV = 0;
	pMesh->LockVertexBuffer(0, (LPVOID*)&meshV);	
	memcpy(meshV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	//�ε��� ����
	WORD* Index = 0;
	pMesh->LockIndexBuffer(0, (LPVOID*)&Index);
	
	for (int i = 0; i < vecVertex.size(); ++i)
	{
		Index[i] = i;
	}
	
	pMesh->UnlockIndexBuffer();

	//��Ʈ����Ʈ ����
	DWORD* attribute = 0;

	pMesh->LockAttributeBuffer(0, &attribute);
	memcpy(attribute, &vecSubset[0], vecSubset.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();


	vector<DWORD> adjacencyBuffer(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	pMesh->OptimizeInplace(	
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


	return pMesh;
}
