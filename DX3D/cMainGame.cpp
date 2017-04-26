#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"		/// << :

// >> :
#include "cCubePC.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cCubeMan.h"
#include "cCubeMan2.h"


// << :
cMainGame::cMainGame()
	:
	m_pGrid(NULL),
	m_pCamera(NULL),
	m_pPyramid(NULL),
	m_pCubeMan(NULL),
	m_pCubeMan2(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPyramid);
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pCubeMan2);

	g_pDeviceManager->Destroy();	//¼Ò¸êÀÚ ¿ªÈ°À» ÇÏ°Ô²û ¸¸µë
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pPyramid = new cPyramid;
	m_pPyramid->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->RecieveHexaVertext(&m_pGrid->GetHexagonVertex());
	m_pCubeMan->Setup();

	m_pCubeMan2 = new cCubeMan2;
	m_pCubeMan2->RecieveHexaVertext(&m_pGrid->GetHexagonVertex());
	m_pCubeMan2->Setup();


	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, false);
	Set_Light();
}

void cMainGame::Update()
{
	if (m_pCamera) m_pCamera->Update();

	if (m_pCubeMan) m_pCubeMan->Update();
	if (m_pCubeMan2) m_pCubeMan2->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();
	if (m_pPyramid) m_pPyramid->Render();
	if (m_pCubeMan) m_pCubeMan->Render();
	if (m_pCubeMan2) m_pCubeMan2->Render();
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Set_Light()
{

	//---------------------------------------------------------------
	//							µð·º¼Ç
	//---------------------------------------------------------------
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

	//---------------------------------------------------------------
	//							 ½ºÆÌ
	//---------------------------------------------------------------
	
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_SPOT;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	stLight.Range = 10.0f;
	D3DXVECTOR3 vDir1(0.0f, 0.0f, 0.0f);

	stLight.Phi = 1.58f;
	stLight.Theta = 0.8f;

	D3DXVec3Normalize(&vDir1, &vDir1);
	stLight.Direction = vDir1;
	g_pD3DDevice->SetLight(1, &stLight);
	g_pD3DDevice->LightEnable(1, false);

	//---------------------------------------------------------------
	//							Æ÷ÀÎÆ®
	//---------------------------------------------------------------
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_POINT;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	stLight.Range = 10.0f;
	g_pD3DDevice->SetLight(2, &stLight);
	g_pD3DDevice->LightEnable(2, false);

}
