#include "stdafx.h"
#include "cTeapot.h"


cTeapot::cTeapot()
	:m_fSpeed(0.0f)
	, m_vForward(1, 0, 0)
	, m_pTeapot(NULL)
	, m_vPosition(0, 0, 0)
{
}

cTeapot::~cTeapot()
{
	SAFE_RELEASE(m_pTeapot);
}

void cTeapot::Setup(D3DXMATRIXA16& mat, D3DXCOLOR color)
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pTeapot, 0);

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = color;
	m_stMtl.Diffuse = color;
	m_stMtl.Specular = color;

	//D3DXVec3TransformCoord(&m_vPosition, &m_vPosition, &mat);
}

void cTeapot::Update(D3DXMATRIXA16& matT, D3DXVECTOR3 vt, D3DXVECTOR3 dir)
{
	//D3DXVECTOR3 perv = m_vPosition;
	//static int n = 0;
	//D3DXVec3TransformCoord(&m_vPosition, &D3DXVECTOR3(0,0,0), &m_matWorld);
	//float ang = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &vt);
	D3DXVECTOR3 v1 = D3DXVECTOR3(1,0,0);
	D3DXVECTOR3 v2 = dir;
	//float aaa = (v1.x * v2.y - v1.y * v2.x);// >= 0);
	D3DXVec3Normalize(&v1, &v1);
	D3DXVec3Normalize(&v2, &v2);	
	float ang = D3DXVec3Dot(&v1, &v2);
	
	//float lenA = D3DXVec3Length(&vt);
	//float lenB = D3DXVec3Length(&D3DXVECTOR3(1, 0, 0));

	float ang3 = acosf(ang/(D3DXVec3Length(&v1)*D3DXVec3Length(&v2)));
	
	
	ang3 = (v1.x * v2.y - v1.y * v2.x >= 0) ? ang3 : /*(2*D3DX_PI)+ */ang3 =(D3DX_PI /2);
	D3DXMATRIXA16 matTT, matR;
	D3DXMatrixRotationY(&matR, ang3);
	//m_matWorld *= matR;
	//D3DXMatrixTranslation(&m_matWorld, vt.x, vt.y, vt.z);
	D3DXMatrixTranslation(&matTT, vt.x, vt.y, vt.z);
	m_matWorld = matR*matTT;
	//m_matWorld = matR * m_matWorld;
	//n += 5;
}

void cTeapot::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	m_pTeapot->DrawSubset(0);
}

void cTeapot::Rotate(D3DXVECTOR3* dir)
{
	//float amgle = D3DXVec3Dot(&m_vForward,dir);
}