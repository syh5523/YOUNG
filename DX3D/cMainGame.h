#pragma once

class cCamera;
class cGrid;
class cAseCharacter;
class cMtlTex;
class cGroup;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cAseCharacter*			m_pAseCharacter;
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;

	LPD3DXFONT				m_pFont;
	DWORD					tic, tic1, frame, frame1;
	DWORD					curFrame, curFrame1;

	//----
	vector<cMtlTex*>		m_vpMtlTex;

	LPD3DXMESH m_lpMesh;

	vector<cGroup*>			m_vecGroup;
public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();

	void Create_Font();
	void Text_Render();

	void Frame();


};

