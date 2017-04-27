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

		if (firstWord == "stop") break;

		if (firstWord == "g")
		{
			char str[128] = { 0, };
			sscanf_s(szBuf, "%*s%s", str, sizeof(str));

			//g가 나왔는데 뒤에 아무것도 없을 시엔 오브젝트를 하나 형성한다.
			if (str[0] == NULL)
			{
				//사이즈가 0이면 크기만 늘림
				if (m_vObject.size() == 0)
				{
					cObject* tempObject = new cObject;
					m_vObject.push_back(tempObject);
					continue;
				}
				//사이즈가 0이 아니면 PNT 정리하기
				else
				{
					//PNT 정리하기					
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
			//g가 나왔는데 뒤에 오브젝트 이름이 있을 시
			else
			{
				//이름 저장
				m_vObject[m_vObject.size() - 1]->SetObjName(str);
				continue;
			}	
		}


		//mtlLib(머터리얼 라이브러리)는 다읽고 일어봐야 하므로 저장해둠.
		if (firstWord == "mtllib")
		{
			sscanf_s(szBuf, "%*s%s", &MtlFileName, sizeof(MtlFileName));
			continue;
		}
		
		//v라면 버텍스 
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

		//vn라면 법선벡터
		if (firstWord == "vn")
		{
			sscanf_s(szBuf, "%*s%f%f%f", &x, &y, &z);

			D3DXVECTOR3 tempNormal = D3DXVECTOR3(x, y, z);
			m_vNormal.push_back(tempNormal);

			continue;
		}


		//인덱스
		if (firstWord == "f")
		{
			//첫번째 
			sscanf_s(szBuf, "%*s %f %*c %f %*c %f", &x, &y, &z);
			D3DXVECTOR3 tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_vIndex_VTN.push_back(tempIndex);

			//두번째
			sscanf_s(szBuf, "%*s%*s %f %*c %f %*c %f", &x, &y, &z);
			tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_vIndex_VTN.push_back(tempIndex);


			//세번째
			sscanf_s(szBuf, "%*s %*s %*s %f %*c %f %*c %f", &x, &y, &z);
			tempIndex = D3DXVECTOR3(x - 1, y - 1, z - 1);
			m_vIndex_VTN.push_back(tempIndex);
			continue;

		}

		//그룹 네임
		if (firstWord == "usemtl")
		{
			char str[128];

			sscanf_s(szBuf, "%*s %s", &str, sizeof(str));
			m_vObject[m_vObject.size() - 1]->SetMtlName(str);
		}
	}

	fclose(fp);

	//머터리얼 불러오기 
	fopen_s(&fp, MtlFileName, "r");
	char curruntMtlName[128] = { 0, };;
	char curruntImgName[128] = { 0, };;

	D3DCOLORVALUE Ambient;
	D3DCOLORVALUE Diffuse;
	D3DCOLORVALUE Specular;
	float Power = 0.0f;

	//머터리얼 자료 파싱하기
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
	//사이즈
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.025f, 0.025f, 0.025f);

	//로테이션
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationX(&matR, -D3DX_PI*0.5f);

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	mat = matR * matS;


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	for (int i = 0; i < m_vObject.size() - 1; ++i)
	{
	
		//텍스처
		LPDIRECT3DTEXTURE9 tempTexture;
		ZeroMemory(&tempTexture, sizeof(LPDIRECT3DTEXTURE9));
		D3DXCreateTextureFromFile(g_pD3DDevice, 
			m_mMtlTexture.find(m_vObject[i]->GetMtlName())->second->GetImgName().c_str(), &tempTexture);

		//머터리얼, 텍스쳐 설정
		g_pD3DDevice->SetMaterial(&m_mMtlTexture.find(m_vObject[i]->GetMtlName())->second->GetMtl());
		g_pD3DDevice->SetTexture(0, tempTexture);

		//삼각형 그리기
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vObject[i]->GetPNT().size() / 3,
			&m_vObject[i]->GetPNT()[0], sizeof(ST_PNT_VERTEX));

		
		g_pD3DDevice->SetTexture(0, NULL);
		SAFE_RELEASE(tempTexture);
	}


}
