#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cPyramid;
class cCubeMan;
class cCubeMan2;
class cObjLoader;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	//cCubePC*	m_pCubePC;
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	cPyramid*	m_pPyramid;
	cCubeMan*	m_pCubeMan;
	cCubeMan2*	m_pCubeMan2;
	cObjLoader* m_pObjLoader;
	//LPDIRECT3DTEXTURE9	m_pTexture;
	//std::vector<ST_PT_VERTEX> m_vecVertex;

public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();
};