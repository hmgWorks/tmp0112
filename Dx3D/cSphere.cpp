#include "stdafx.h"
#include "cSphere.h"


cSphere::cSphere()
	:m_pMeshSphere(NULL)
	, m_vPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWordl);
}


cSphere::~cSphere()
{
	SAFE_RELEASE(m_pMeshSphere);
}

void cSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, 1, 10, 5, &m_pMeshSphere, 0);

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void cSphere::Update()
{
	
}

void cSphere::Render()
{	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWordl);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	m_pMeshSphere->DrawSubset(0);
}

void cSphere::SetWorldTM(D3DXMATRIXA16& matWorldTM)
{
	m_matWordl = matWorldTM;
}