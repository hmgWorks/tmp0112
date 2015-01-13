#pragma once

class cSphere;
class cTeapot;

class cHexagon
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	std::vector<cSphere*>		m_vecSphere;
	std::vector<ST_PC_VERTEX>	m_vecListVertex;
	std::vector<WORD>			m_vecLineIndex;
	D3DMATERIAL9				m_stMtl;

	D3DXMATRIXA16				m_matWorld, m_matT;
	cTeapot*					m_pTeapot, *m_pTeapot2;
	float						m_fT;
	float						m_time, m_time2,m_time3;
	DWORD						m_st, m_end;
public:
	cHexagon();
	~cHexagon();

	void Setup(int num, int length, float time);
	void Update(float delta);
	void Render();
	D3DXVECTOR3 LinearInterpolation(D3DXVECTOR3& vecP0, D3DXVECTOR3& vecP1, float n);
	D3DXVECTOR3 BezierInterpolation(D3DXVECTOR3& vecP0, D3DXVECTOR3& vecP1, D3DXVECTOR3& vecP2,float n);
};

