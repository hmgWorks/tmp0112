#pragma once
class cTeapot
{
private:
	float			m_fSpeed;
	D3DXVECTOR3		m_vForward;
	LPD3DXMESH		m_pTeapot;
	D3DMATERIAL9	m_stMtl;

	D3DXMATRIXA16	m_matR;
	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vPosition;
public:
	cTeapot();
	~cTeapot();

	void SetSpeed(float speed) { m_fSpeed = speed; }
	void SetForward(D3DXVECTOR3 forward){ D3DXVec3Normalize(&m_vForward, &forward); }
	void SetWorldTM(D3DXMATRIXA16& world){ m_matWorld = world; }
	D3DXVECTOR3& GetPosition(){ return m_vPosition; }
	void Rotate(D3DXVECTOR3* dir);
	void Setup(D3DXMATRIXA16& mat, D3DXCOLOR color);
	void Update(D3DXMATRIXA16& matT, D3DXVECTOR3 vt, D3DXVECTOR3 dir);
	void Render();
};

