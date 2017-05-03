#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtltex.h"
#include "cGroup.h"

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
	vector<D3DXVECTOR2> vecT;
	vector<ST_PNT_VERTEX> vecPNT;

	

	D3DXMATRIXA16 matWorld;
	
	int nCur_mIndex = 0;		//<< ���� ���͸��� �ε��� ����


	while (true)
	{
		if (feof(fp)) break;

		char szTemp[BUFFER];
		char cFirstName[BUFFER];
		string sFirstName;

		fgets(szTemp, BUFFER, fp);
		sscanf_s(szTemp, "%s", cFirstName, BUFFER);
		sFirstName = cFirstName;
	
		string sMtlName;
		string ParentsName;
		string MyName;
		int nMtl = -1;
		if (sFirstName == "Bip01 Footsteps") break;
		//��Ƽ��
		if (sFirstName == "{") continue;
		
		//���͸���� ����
		if (sFirstName == ID_MATERIAL_LIST)
		{
			while (true)
			{
				fgets(szTemp, BUFFER, fp);
				sscanf_s(szTemp, "%s", cFirstName, BUFFER);
				sFirstName = cFirstName;
				if (sFirstName == "}")	break;

				////���͸��� ���� �˻�
				//else if (sFirstName == ID_MATERIAL_COUNT)
				//{
				//	int nMaterial_Count;
				//	char cTemp[BUFFER];

				//	sscanf_s(szTemp, "%*s %s", cTemp, BUFFER);
				//	nMaterial_Count = atoi(cTemp);

				//	continue;
				//}

				//���� ���͸��� �ε��� ����
				if (sFirstName == ID_MATERIAL)
				{
					int nMaterial_Index;
					sscanf_s(szTemp, "%*s %d", &nCur_mIndex);

					//���� ���͸����� ����Ǿ� ���� ������ ����
					if (m_mapMtlTex.find(nCur_mIndex) == m_mapMtlTex.end())
						m_mapMtlTex[nCur_mIndex] = new cMtlTex;

					while (true)
					{
						fgets(szTemp, BUFFER, fp);
						sscanf_s(szTemp, "%s", cFirstName, BUFFER);
						sFirstName = cFirstName;
						if (sFirstName == "}")	break;

						//���� ���͸��� Ambient ����
						if (sFirstName == ID_AMBIENT)
						{
							float r, g, b;

							sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
							m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.r = r;
							m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.g = g;
							m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.b = b;
							m_mapMtlTex[nCur_mIndex]->GetMaterial().Ambient.a = 1.0f;

							continue;
						}
						//���� ���͸��� Diffuse ����
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
						//���� ���͸��� Specular ����
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
						//��ǻ�� ������ ����
						else if (sFirstName == ID_MAP_DIFFUSE)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}")	break;

								//BITMAP ����
								if (sFirstName == ID_BITMAP)
								{
									char cTemp[BUFFER];
									sscanf_s(szTemp, "%*s %*c %s", cTemp, BUFFER);
									sFullPath = cTemp;
									sFullPath.pop_back();

									LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
									m_mapMtlTex[nCur_mIndex]->SetTexture(pTexture);
								}
							}
						}
						
					}
				}
			}
		}


		//������Ʈ�� ����
		if (sFirstName == ID_GEOMETRY)
		{
			MyName = "";
			ParentsName = "";
		
			while (true)
			{
				fgets(szTemp, BUFFER, fp);
				sscanf_s(szTemp, "%s", cFirstName, BUFFER);
				sFirstName = cFirstName;




				if (sFirstName == "}") break;

				//�ڽ��� �̸� ����
				if (sFirstName == ID_NODE_NAME)
				{
					char* cTemp;
					strtok_s(szTemp, " ", &cTemp);
	
					MyName = cTemp;
					MyName.pop_back();
					MyName.pop_back();
					MyName.erase(0, 1);
					continue;
				}
				//�θ��� �̸� ����
				else if (sFirstName == ID_NODE_PARENT)
				{
					char* cTemp;
					strtok_s(szTemp, " ", &cTemp);

					ParentsName = cTemp;
					ParentsName.pop_back();
					ParentsName.pop_back();
					ParentsName.erase(0, 1);
					continue;
				}
				//�������κ��� �� 
				else if (sFirstName == ID_NODE_TM)
				{
					D3DXMatrixIdentity(&matWorld);

					while (true)
					{
						fgets(szTemp, BUFFER, fp);
						sscanf_s(szTemp, "%s", cFirstName, BUFFER);
						sFirstName = cFirstName;
						if (sFirstName == "}")	break;
						
						//��� ����(row0)
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
						}
					}

					if (ParentsName != "")
					{
						matWorld *= *m_mapMatWorld.find(ParentsName)->second;
					}

					//���� ����� ����Ǿ� ���� ������ ����
					if (m_mapMatWorld.find(MyName) == m_mapMatWorld.end())
						m_mapMatWorld[MyName] = new D3DXMATRIXA16(matWorld);
				}
				//�޽� ���� �κ��� ��
				else if (sFirstName == ID_MESH)
				{
					while (true)
					{
						fgets(szTemp, BUFFER, fp);
						sscanf_s(szTemp, "%s", cFirstName, BUFFER);
						sFirstName = cFirstName;
						if (sFirstName == "}") break;

						//���ؽ� ��������
						if (sFirstName == ID_MESH_NUMVERTEX)
						{
							int nMesh_NumVertex;
							sscanf_s(szTemp, "%*s %d", &nMesh_NumVertex);
							vecP.clear();
							//���ؽ� �����ŭ ������¡
							vecP.resize(nMesh_NumVertex);
						}

						//�ﰢ�� ���� ����
						else if (sFirstName == ID_MESH_NUMFACES)
						{
							int nMesh_NumFaces;
							sscanf_s(szTemp, "%*s %d", &nMesh_NumFaces);
							vecPNT.clear();
							vecPNT.resize(nMesh_NumFaces * 3);
						}

						//���ؽ� ��ǥ ����Ʈ ����
						else if (sFirstName == ID_MESH_VERTEX_LIST)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}") break;

								//���ؽ� ����
								if (sFirstName == ID_MESH_VERTEX)
								{
									int nIndex;
									float x, y, z;

									sscanf_s(szTemp, "%*s %d %f %f %f", &nIndex, &z, &x, &y);

									D3DXVECTOR3 vTemp;
									D3DXVec3TransformCoord(&vTemp, &(D3DXVECTOR3(x, y, z)), 
										m_mapMatWorld.find(MyName)->second);
		
									vecP[nIndex] = D3DXVECTOR3(x, y, z);
									
								}
							}
						}

						//�ﰢ�� ���ؽ� ����
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

						//�ؽ�ó ���ؽ� ��������
						else if (sFirstName == ID_MESH_NUMTVERTEX)
						{
							int nMesh_NumTVertex;
							sscanf_s(szTemp, "%*s %d", &nMesh_NumTVertex);
							vecT.resize(nMesh_NumTVertex);
						}
					
						//�ؽ�ó ���ؽ� ��ǥ ����Ʈ
						else if (sFirstName == ID_MESH_TVERTLIST)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}") break;
								
								if (sFirstName == ID_MESH_TVERT)
								{
									int nIndex;
									float u, v;

									sscanf_s(szTemp, "%*s %d %f %f", &nIndex, &u, &v);

									vecT[nIndex].x = u;
									vecT[nIndex].y = v;
								}
							}
						}
						
						//�ﰢ�� �ؽ��� ��ǥ ����
						else if (sFirstName == ID_MESH_TFACELIST)
						{
							while (true)
							{
								fgets(szTemp, BUFFER, fp);
								sscanf_s(szTemp, "%s", cFirstName, BUFFER);
								sFirstName = cFirstName;
								if (sFirstName == "}") break;

								if (sFirstName == ID_MESH_TFACE)
								{
									int nIndex;
									float x, y, z;

									sscanf_s(szTemp, "%*s %d %f %f %f", &nIndex, &x, &y, &z);

									vecPNT[(nIndex * 3)].t = vecT[x];
									vecPNT[(nIndex * 3) + 1].t = vecT[y];
									vecPNT[(nIndex * 3) + 2].t = vecT[z];
								}
							}

							
						}
						
						//�������� ���� 
						else if (sFirstName == ID_MESH_NORMALS)
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

				//���͸��� ����
				else if (sFirstName == ID_MATERIAL_REF)
				{				
					sscanf_s(szTemp, "%*s %d", &nMtl);	

				}
				
				
			}
		}
		
		
		if (!vecPNT.empty())
		{
			cGroup* pGroup = new cGroup;
			pGroup->SetVertex(vecPNT);			
			if(nMtl != -1) pGroup->SetMtlTex(m_mapMtlTex[nMtl]);
			vecGroup.push_back(pGroup);
			vecPNT.clear();
			vecP.clear();
			vecT.clear();
		}
		
	}


	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapMtlTex.clear();
}