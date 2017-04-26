
#pragma once
class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	std::vector<ST_PC_VERTEX>		m_vecVertex;

	SYNTHESIZE(std::vector<ST_PC_VERTEX>, m_Hexagon, HexagonVertex)

	D3DMATERIAL9	m_stMaterial;
public:
	void Setup();
	void Render();

};