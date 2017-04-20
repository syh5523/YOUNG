#include "stdafx.h"
#include "cMainGame.h"

//#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cPyramid.h"
#include "cCubeMan.h"

cMainGame::cMainGame()
	:m_pCubeMan(NULL),
	m_pCamera(NULL),
	m_pGrid(NULL)

{
}


cMainGame::~cMainGame()
{
	//������ ������
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pGrid);

	//�̱��� ������
	g_pDeviceManager->Destroy();
}

// >> : 
void cMainGame::Setup()
{
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pPyramid = new cPyramid;
	m_pPyramid->Setup();

	//����Ʈ ���� ������ ���ش�. (�ؽ�ó�� �����Ƿ� ����Ʈ�� �����)
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

}

void cMainGame::Update()
{
	if (m_pCamera) m_pCamera->Update();
	if (m_pCubeMan) m_pCubeMan->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	//------------------------------------------------------------------------
	//							�׸��� ����
	//------------------------------------------------------------------------
	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();
	if (m_pCubeMan) m_pCubeMan->Render();
	if (m_pPyramid) m_pPyramid->Render();


	g_pD3DDevice->EndScene();

	//------------------------------------------------------------------------
	//							�׸��� ��
	//------------------------------------------------------------------------

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!m_pCamera) return;

	m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
// << : 