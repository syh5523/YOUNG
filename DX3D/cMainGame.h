#pragma once

class cCamera;
class cGrid;
class cAseCharacter;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cAseCharacter*			m_pAseCharacter;
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;

public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();


};

