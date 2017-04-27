#include "stdafx.h"
#include "cObjLoader.h"

cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}


void cObjLoader::Setup()
{

	FILE* fp;
	fopen_s(&fp, "Map.obj", "r");
	//fopen_s(&fp, "Box.obj", "r");
	//fopen_s(&fp, "map_surface.obj", "r");
	
	char szBuf[STRBUF] = { 0, };
	char saveBuf[STRBUF] = { 0, };
	char MtlFileName[STRBUF];
	float x;
	float y;
	float z;

	//�ڷ��Ľ��ϱ�
	while (true)
	{	
		if (feof(fp)) break;
		

		//���پ� �о��
		fgets(szBuf, sizeof(szBuf), fp);

		//# == �ּ��̹Ƿ� skip��
		if (szBuf[0] == '#' || szBuf[0] == '\n') continue;

		//ù��° �ܾ� ����
		string firstWord;
		sscanf_s(szBuf, "%s", saveBuf, sizeof(saveBuf));
		firstWord = saveBuf;

		if (firstWord == "stop") break;

		if (firstWord == "g")
		{
			char str[128] = { 0, };
			sscanf_s(szBuf, "%*s%s", str, sizeof(str));

			//g�� ���Դµ� �ڿ� �ƹ��͵� ���� �ÿ� ������Ʈ�� �ϳ� �����Ѵ�.
			if (str[0] == NULL)
			{
				//����� 0�̸� ũ�⸸ �ø�
				if (m_vObject.size() == 0)
				{
					cObject* tempObject = new cObject;
					m_vObject.push_back(tempObject);
					continue;
				}
				//����� 0�� �ƴϸ� PNT �����ϱ�
				else
				{
					//PNT �����ϱ�					
					for (int j = 0; j < m_vIndex_VTN.size(); ++j)
					{
						ST_PNT_VERTEX temp;
						ZeroMemory(&temp, sizeof(temp));

						temp.p = m_vVertex[m_vIndex_VTN[j].x];
						temp.t = m_vTextureUV[m_vIndex_VTN[j].y];
						temp.n = m_vNormal[m_vIndex_VTN[j].z];

						m_vObject[m_vObject.size() - 1]->PushPNT(temp);

						
					}
					cObject* tempObject = new cObject;
					m_vObject.push_back(tempObject);
					m_vIndex_VTN.clear();
					continue;
				}
			}
			//g�� ���Դµ� �ڿ� ������Ʈ �̸��� ���� ��
			else
			{
				//�̸� ����
				m_vObject[m_vObject.size() - 1]->SetObjName(str);
				continue;
			}	
		}


		//mtlLib(���͸��� ���̺귯��)�� ���а� �Ͼ���� �ϹǷ� �����ص�.
		if (firstWord == "mtllib")
		{
			sscanf_s(szBuf, "%*s%s", &MtlFileName, sizeof(MtlFileName));
			continue;
		}
		
		//v��� ���ؽ� 
		if(firstWord == "v")
		{
			sscanf_s(szBuf, "%*s%f%f%f", &x, &y, &z);

			D3DXVECTOR3 tempVertex = D3DXVECTOR3(x, y, z);
			m_vVertex.push_back(tempVertex);

			continue;
		}

		//vt
		if (firstWord == "vt")
		{
			sscanf_s(szBuf, "%*s%f%f", &x, &y);

			D3DXVECTOR2 tempUV = D3DXVECTOR2(x, y);
			m_vTextureUV.push_back(tempUV);
			continue;
		}

		//vn��� ��������
		if (firstWord == "vn")
		{
			sscanf_s(szBuf, "%*s%f%f%f", &x, &y, &z);

			D3DXVECTOR3 tempNormal = D3DXVECTOR3(x, y, z);
			m_vNormal.push_back(tempNormal);

			continue;
		}


		//�ε���
		if (firstWord == "f")
		{
			//ù��° 
			sscanf_s(szBuf, "%*s %f %*c %f %*c %f", &x, &y, &z);
			D3DXVECTOR3 tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_vIndex_VTN.push_back(tempIndex);

			//�ι�°
			sscanf_s(szBuf, "%*s%*s %f %*c %f %*c %f", &x, &y, &z);
			tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_vIndex_VTN.push_back(tempIndex);


			//����°
			sscanf_s(szBuf, "%*s %*s %*s %f %*c %f %*c %f", &x, &y, &z);
			tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_vIndex_VTN.push_back(tempIndex);
			continue;

		}

		//�׷� ����
		if (firstWord == "usemtl")
		{
			char str[128];

			sscanf_s(szBuf, "%*s %s", &str, sizeof(str));
			m_vObject[m_vObject.size() - 1]->SetMtlName(str);
		}
	}

	fclose(fp);

	//���͸��� �ҷ����� 
	fopen_s(&fp, MtlFileName, "r");
	char curruntMtlName[128] = { 0, };;
	char curruntImgName[128] = { 0, };;

	D3DCOLORVALUE Ambient;
	D3DCOLORVALUE Diffuse;
	D3DCOLORVALUE Specular;
	float Power = 0.0f;

	//���͸��� �ڷ� �Ľ��ϱ�
	while (true)
	{
		if (feof(fp)) break;

		//���پ� �о��
		fgets(szBuf, sizeof(szBuf), fp);

		//# == �ּ��̹Ƿ� skip��
		if (szBuf[0] == '#' || szBuf[0] == '\n') continue;

		//ù��° �ܾ� ����
		string firstWord;
		sscanf_s(szBuf, "%s", saveBuf, sizeof(saveBuf));
		firstWord = saveBuf;


		if (firstWord == "newmtl")
		{
			sscanf_s(szBuf, "%*s%s", &curruntMtlName, sizeof(curruntMtlName));
			continue;
		}
		if (firstWord == "Ka")
		{
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);		
			Ambient = D3DXCOLOR(x, y, z, 1.0f);

		}
		if (firstWord == "Kd")
		{
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
			Diffuse = D3DXCOLOR(x, y, z, 1.0f);
		}
		if (firstWord == "Ks")
		{
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
			Specular = D3DXCOLOR(x, y, z, 1.0f);
		}
		if (firstWord == "d")
		{
			sscanf_s(szBuf, "%*s %f", &Power);
		}


		if (firstWord == "map_Kd")
		{
			sscanf_s(szBuf, "%*s%s", &curruntImgName, sizeof(curruntImgName));
			
			cMtltex* tempMtl = new cMtltex;
			D3DMATERIAL9 stMtl;
			ZeroMemory(&stMtl, sizeof(stMtl));
			stMtl.Ambient = Ambient;
			stMtl.Diffuse = Diffuse;
			stMtl.Specular = Specular;
			stMtl.Power = Power;

			tempMtl->SetImgName(curruntImgName);
			tempMtl->SetMtlName(curruntMtlName);
			tempMtl->SetMtl(stMtl);

			m_mMtlTexture.insert(make_pair(curruntMtlName, tempMtl));
		}

	}

	fclose(fp);



}

void cObjLoader::Update()
{
}

void cObjLoader::Render()
{
	//������
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.025f, 0.025f, 0.025f);

	//�����̼�
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationX(&matR, -D3DX_PI*0.5f);

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	mat = matR * matS;


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	for (int i = 0; i < m_vObject.size() - 1; ++i)
	{
	
		//�ؽ�ó
		LPDIRECT3DTEXTURE9 tempTexture;
		ZeroMemory(&tempTexture, sizeof(LPDIRECT3DTEXTURE9));
		D3DXCreateTextureFromFile(g_pD3DDevice, 
			m_mMtlTexture.find(m_vObject[i]->GetMtlName())->second->GetImgName().c_str(), &tempTexture);

		//���͸���, �ؽ��� ����
		g_pD3DDevice->SetMaterial(&m_mMtlTexture.find(m_vObject[i]->GetMtlName())->second->GetMtl());
		g_pD3DDevice->SetTexture(0, tempTexture);

		//�ﰢ�� �׸���
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vObject[i]->GetPNT().size() / 3,
			&m_vObject[i]->GetPNT()[0], sizeof(ST_PNT_VERTEX));

		
		g_pD3DDevice->SetTexture(0, NULL);
		SAFE_RELEASE(tempTexture);
	}


}
