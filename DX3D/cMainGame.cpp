#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"		/// << : 

#include "cCamera.h"
#include "cGrid.h"
#include "cAseCharacter.h"
#include "cMtltex.h"
#include "cObjLoader.h"
#include "cGroup.h"


cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pAseCharacter(NULL)
	,curFrame(0), curFrame1(0)
	, m_lpMesh(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pAseCharacter);

	SAFE_RELEASE(m_pFont);

	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		SAFE_DELETE(m_vecGroup[i]);
	}
	for (int i = 0; i < m_vpMtlTex.size(); ++i)
	{
		SAFE_DELETE(m_vpMtlTex[i]);
	}

	SAFE_RELEASE(m_lpMesh);

	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pAseCharacter = new cAseCharacter;
	m_pAseCharacter->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	cObjLoader Load;
	m_lpMesh = Load.LoadMesh(m_vpMtlTex, "obj", "Map.obj");

	cObjLoader loadObj;
	loadObj.Load(m_vecGroup, "obj", "Map.obj");

	Set_Light();
	Create_Font();
}

void cMainGame::Update()
{
	if (m_pCamera) m_pCamera->Update();
	if (m_pAseCharacter) m_pAseCharacter->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();
	///-----------------------------------------------------------------------BeginScene


	if (m_pGrid) m_pGrid->Render();
	if (m_pAseCharacter) m_pAseCharacter->Render();
	Text_Render();

	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	
	DWORD time1, time2, time3, time4;

	time1 = GetTickCount();

	for (int i = 0; i < REPEATCOUNT; ++i)
	{
		for each(auto p in m_vecGroup)
		{
			p->Render();
		}
	}

	time2 = GetTickCount();
	curFrame = time2 - time1;

	time3 = GetTickCount();

	for (int i = 0; i < REPEATCOUNT; ++i)
	{
		for (int i = 0; i < m_vpMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetTexture(0, m_vpMtlTex[i]->GetTexture());
			g_pD3DDevice->SetMaterial(&m_vpMtlTex[i]->GetMaterial());

			m_lpMesh->DrawSubset(i);
		}
	}

	time4 = GetTickCount();
	curFrame1 = time4 - time3;




	g_pD3DDevice->SetTexture(0, NULL);

	///-----------------------------------------------------------------------EndScene
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);



	
}

void cMainGame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hwnd, message, wParam, lParam);
	}
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight;
	{
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = D3DLIGHT_DIRECTIONAL;
		stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		g_pD3DDevice->SetLight(0, &stLight);
	}

	g_pD3DDevice->LightEnable(0, true);
}

//>>
void cMainGame::Create_Font()
{
	{
	
	}


	{
		//HDC hdc = CreateCompatibleDC(0);
		//LOGFONT lf;
		//ZeroMemory(&lf, sizeof(LOGFONT));
		//lf.lfHeight = 25;
		//lf.lfWidth = 12;
		//lf.lfWeight = 500;  //(0 ~1000 ¹üÀ§)
		//lf.lfItalic = false;
		//lf.lfUnderline = false;
		//lf.lfStrikeOut = false;
		//lf.lfCharSet = DEFAULT_CHARSET;
		//strcpy_s(lf.lfFaceName, "±¼¸²Ã¼");

		//HFONT hFont;
		//HFONT hFontOld;

		//hFont = CreateFontIndirect(&lf);
		//hFontOld = (HFONT)SelectObject(hdc, hFont);
		//D3DXCreateText(g_pD3DDevice, hdc, "Direct3D", 0.001f, 0.01f, &m_p3DText, 0, 0);

		//SelectObject(hdc, hFontOld);
		//DeleteObject(hFont);
		//DeleteDC(hdc);
	}
}

void cMainGame::Text_Render()
{
	{
		
	}


	{
		/*D3DXMATRIXA16 matWorld, matS, matR, matT;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 100.0f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);
		D3DXMatrixTranslation(&matT, -2.0f, 2.0f, 0.0f);

		matWorld = matS * matR * matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_p3DText->DrawSubset(0);*/
	}
}




