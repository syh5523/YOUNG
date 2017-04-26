#pragma once
#include "cCubeNode.h"

class cGrid : public cCubeNode
{
public:
	cGrid();
	~cGrid();

	virtual void Setup() override;	// << :

	D3DMATERIAL9	m_stMaterial;

	std::vector<ST_PNT_VERTEX> m_hexagon;
};

