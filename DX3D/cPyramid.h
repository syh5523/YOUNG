#pragma once
class cPyramid
{
public:
	cPyramid();
	~cPyramid();

private:
	std::vector<ST_PC_VERTEX> m_vecVertexX, m_vecVertexY, m_vecVertexZ;
	D3DMATERIAL9	m_stMaterialX, m_stMaterialY, m_stMaterialZ;

public:
	void Setup();
	void Render();
};

