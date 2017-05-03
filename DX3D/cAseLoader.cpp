#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtltex.h"

cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{
}

void cAseLoader::LoadAse(OUT vector<cGroup*>& vecGroup, IN char * szFolder, IN char * szFile)
{
	string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));
	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	vector<D3DXVECTOR3> vecP;
	//vector<D3DXVECTOR2> vecTexture;
	vector<ST_PNT_VERTEX> vecPNT;

	string sMtlName;
	string ParentsName;
	string MyName;
	D3DXMATRIXA16 matWorld;
	
	int nCur_mIndex = 0;		//<< 현재 머터리얼 인덱스 저장


	while (true)
	{
		if (feof(fp)) break;

		char szTemp[BUFFER];
		char cFirstName[BUFFER];
		string sFirstName;

		fgets(szTemp, BUFFER, fp);
		sscanf_s(szTemp, "%s", cFirstName, BUFFER);
		sFirstName = cFirstName;

		//컨티뉴
		if (sFirstName == "{" || sFirstName == "}") continue;


		////머터리얼 갯수 검사
		//else if (sFirstName == ID_MATERIAL_COUNT)
		//{
		//	int nMaterial_Count;
		//	char cTemp[BUFFER];

		//	sscanf_s(szTemp, "%*s %s", cTemp, BUFFER);
		//	nMaterial_Count = atoi(cTemp);

		//	continue;
		//}
		//현재 머터리얼 인덱스 저장
		else if (sFirstName == ID_MATERIAL)
		{
			int nMaterial_Index;
			sscanf_s(szTemp, "%*s %d", &nCur_mIndex);

			//현재 머터리얼이 저장되어 있지 않으면 생성
			if (m_mapMtlTex.find(nCur_mIndex) == m_mapMtlTex.end())
				m_mapMtlTex[nCur_mIndex] = new cMtlTex;

			continue;
		}
		//현재 머터리얼 Ambient 저장
		else if (sFirstName == ID_AMBIENT)
		{
			float r, g, b;

			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.r = r;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.g = g;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.b = b;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.a = 1.0f;

			continue;
		}
		//현재 머터리얼 Diffuse 저장
		else if (sFirstName == ID_DIFFUSE)
		{
			float r, g, b;

			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);

			m_mapMtlTex[nCur_mIndex]->GetMaterial().Diffuse.r = r;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Diffuse.g = g;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Diffuse.b = b;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Diffuse.a = 1.0f;

			continue;
		}
		//현재 머터리얼 Specular 저장
		else if (sFirstName == ID_SPECULAR)
		{
			float r, g, b;

			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);

			m_mapMtlTex[nCur_mIndex]->GetMaterial().Specular.r = r;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Specular.g = g;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Specular.b = b;
			m_mapMtlTex[nCur_mIndex]->GetMaterial().Specular.a = 1.0f;

			continue;
		}
		//BITMAP 저장
		else if (sFirstName == ID_BITMAP)
		{
			char cTemp[BUFFER];
			sscanf_s(szTemp, "%*s %*c %s", cTemp, BUFFER);		
			sFullPath = cTemp;
			sFullPath.pop_back();
		
			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[nCur_mIndex]->SetTexture(pTexture);

			continue;
		}

		//-----------------------------------------------------머터리얼 끝
		//-----------------------------------------------------GEOMOBJECT 시작
		
		//시작시 이름들 초기화
		else if (sFirstName == ID_GEOMETRY)
		{
			MyName = "";
			ParentsName = "";
		
			while (true)
			{
				fgets(szTemp, BUFFER, fp);
				sscanf_s(szTemp, "%s", cFirstName, BUFFER);
				sFirstName = cFirstName;
				if (sFirstName == "}") break;

				//자신의 이름 저장
				if (sFirstName == ID_NODE_NAME)
				{
					
					char cTemp[BUFFER];
					sscanf_s(szTemp, "%*s %*c %s", cTemp, BUFFER);
					MyName = cTemp;
					MyName.pop_back();

					continue;
				}
				//부모의 이름 저장
				else if (sFirstName == ID_NODE_PARENT)
				{
					char cTemp[BUFFER];
					sscanf_s(szTemp, "%*s %*c %s", cTemp, BUFFER);
					ParentsName = cTemp;
					ParentsName.pop_back();
				}
				//행렬저장부분일 시 
				else if (sFirstName == ID_NODE_TM)
				{
					D3DXMatrixIdentity(&matWorld);


					while (true)
					{
						fgets(szTemp, BUFFER, fp);
						sscanf_s(szTemp, "%s", cFirstName, BUFFER);
						sFirstName = cFirstName;
						if (sFirstName == "}")	break;
						
						//행렬 저장(row0)
						if (sFirstName == ID_TM_ROW0 || sFirstName == ID_TM_ROW1 ||
							sFirstName == ID_TM_ROW2 || sFirstName == ID_TM_ROW3)
						{
							float x, y, z;
							int nRow;

							if (sFirstName == ID_TM_ROW0) nRow = 0;
							else if (sFirstName == ID_TM_ROW1) nRow = 1;
							else if (sFirstName == ID_TM_ROW2) nRow = 2;
							else if (sFirstName == ID_TM_ROW3) nRow = 3;

							sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
							matWorld.m[nRow][0] = x;
							matWorld.m[nRow][1] = y;
							matWorld.m[nRow][2] = z;

							if (ParentsName != "")
							{
								matWorld *= *m_mapMatWorld.find(ParentsName)->second;
							}

							//현재 행렬이 저장되어 있지 않으면 생성
							if (m_mapMatWorld.find(MyName) == m_mapMatWorld.end())
								m_mapMatWorld[MyName] = new D3DXMATRIXA16(matWorld);
						}
					}
				}
				//메시 저장 부분일 시
				else if (sFirstName == ID_MESH)
				{
					while (true)
					{
						fgets(szTemp, BUFFER, fp);
						sscanf_s(szTemp, "%s", cFirstName, BUFFER);
						sFirstName = cFirstName;
						if (sFirstName == "}") break;

						//버텍스 갯수저장
						if (sFirstName == ID_MESH_NUMVERTEX)
						{
							int nMesh_NumVertex;
							sscanf_s(szTemp, "%*s %d", &nMesh_NumVertex);
							vecP.clear();
							//버텍스 사이즈만큼 리사이징
							vecP.resize(nMesh_NumVertex);
						}

						//삼각형 갯수 저장
						else if (sFirstName == ID_MESH_NUMFACES)
						{
							int nMesh_NumFaces;
							sscanf_s(szTemp, "%*s %d", &nMesh_NumFaces);
							vecPNT.clear();
							vecPNT.resize(nMesh_NumFaces * 3);
						}

						//버텍스 좌표 리스트 저장
						else if (sFirstName == ID_MESH_VERTEX_LIST)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}") break;

								//버텍스 저장
								if (sFirstName == ID_MESH_VERTEX)
								{
									int nIndex;
									float x, y, z;

									sscanf_s(szTemp, "%*s %d %f %f %f", &nIndex, &x, &y, &z);
									vecP[nIndex].x = x;
									vecP[nIndex].y = y;
									vecP[nIndex].z = z;
								}
							}
						}

						//삼각형 버텍스 저장
						else if (sFirstName == ID_MESH_FACE_LIST)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}") break;

								if (sFirstName == ID_MESH_FACE)
								{
									int meshIndex;
									int Index1, Index2, Index3;

									sscanf_s(szTemp, "%*s %d: %*s %d %*s %d %*s %d", &meshIndex, &Index1, &Index2, &Index3);

									vecPNT[(meshIndex * 3)].p = vecP[Index1];
									vecPNT[(meshIndex * 3) + 1].p = vecP[Index2];
									vecPNT[(meshIndex * 3) + 2].p = vecP[Index3];
								}
							}

						}	

						//텍스처 버텍스 갯수저장
						else if (sFirstName == ID_MESH_NUMTVERTEX)
						{
						}

						//법선벡터 저장 
						else if (sFirstName == ID_MESH_NUMTVERTEX)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}") break;

								if (sFirstName == ID_MESH_FACENORMAL)
								{
									int nIdx_Normal;
									float x, y, z;

									sscanf_s(szTemp, "%*s %d %f %f %f", &nIdx_Normal, &x, &y, &z);

									vecPNT[(nIdx_Normal * 3)].n = D3DXVECTOR3(x, y, z);
									vecPNT[(nIdx_Normal * 3) + 1].n = D3DXVECTOR3(x, y, z);
									vecPNT[(nIdx_Normal * 3) + 2].n = D3DXVECTOR3(x, y, z);

								}
							}
						}
			
					}
				}
			}
		}
		
		
		
		
		
		
	}
}