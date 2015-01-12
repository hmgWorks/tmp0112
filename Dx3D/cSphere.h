#pragma once
class cSphere
{
private:
	LPD3DXMESH		m_pMeshSphere;
	D3DMATERIAL9	m_stMtl;
	D3DXMATRIXA16	m_matWordl;
	D3DXVECTOR3		m_vPosition;

public:
	cSphere();
	~cSphere();

	void SetWorldTM(D3DXMATRIXA16& matWorldTM);
	D3DXVECTOR3& GetPosition()
	{
		D3DXVec3TransformCoord(&m_vPosition, &m_vPosition, &m_matWordl); 
		return m_vPosition;
	}
	void Setup();
	void Update();
	void Render();
};

