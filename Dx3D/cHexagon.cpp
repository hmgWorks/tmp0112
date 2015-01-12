#include "stdafx.h"
#include "cHexagon.h"
#include "cSphere.h"
#include "cTeapot.h"

cHexagon::cHexagon()
	:m_pVB(NULL)
	, m_pIB(NULL)
	, m_pTeapot(NULL)
	, m_pTeapot2(NULL)
{
}

cHexagon::~cHexagon()
{
	SAFE_DELETE(m_pTeapot2);
	SAFE_DELETE(m_pTeapot);
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);
	for (auto p : m_vecSphere)
		SAFE_DELETE(p);
		
}

void cHexagon::Setup(int num, int length, float time)
{
	//m_st = GetTickCount();
	
	float angle = 0.0f;
	ST_PC_VERTEX v;
	D3DXVECTOR3 vertex = D3DXVECTOR3(0, 0, 0);
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	D3DXMATRIXA16 matT, matR, matS, matWorld/*, matWorld2*/;
	m_vecSphere.resize(num);
	D3DXMatrixTranslation(&m_matT, length, 0, 0);
	D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);

	//teapot
	m_pTeapot = new cTeapot;
	m_pTeapot->Setup(m_matT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pTeapot2 = new cTeapot;
	m_pTeapot2->Setup(m_matT, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	for (int i = 0; i < num; i++)
	{
		D3DXMatrixRotationY(&matR, angle);
		matWorld = matS * m_matT * matR;
		m_vecSphere[i] = new cSphere;
		m_vecSphere[i]->Setup();
		m_vecSphere[i]->SetWorldTM(matWorld);
		angle += (2 * D3DX_PI) / num;
		
		D3DXVec3TransformCoord(&v.p, &vertex, &matWorld);
		m_vecListVertex.push_back(v);

	}

	//D3DXVECTOR3 mmm =  m_vecSphere[1]->GetPosition() - m_vecSphere[0]->GetPosition();
	//m_pTeapot->SetForward(mmm);
	//index
	/*for (int i = 0; i < m_vecListVertex.size(); i++)
	{

	}*/
	m_vecLineIndex = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 0 };
	D3DXVECTOR3 vv = m_vecListVertex[1].p - m_vecListVertex[0].p;
	float len = D3DXVec3Length(&vv);
	m_time = len / ((1000 * time) / num);
	m_time2 = len / ((1000 * time) / 3);

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	g_pD3DDevice->CreateVertexBuffer(
		m_vecListVertex.size()*sizeof(ST_PC_VERTEX),
		0, ST_PC_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVB, 0);
	
	ST_PC_VERTEX* vp;
	m_pVB->Lock(0, 0, (LPVOID*)&vp, 0);
	{
		memcpy(vp, &m_vecListVertex[0], m_vecListVertex.size()*sizeof(ST_PC_VERTEX));
	}
	m_pVB->Unlock();

	g_pD3DDevice->CreateIndexBuffer(
		m_vecLineIndex.size()*sizeof(WORD),
		0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, 0);
	
	WORD* ib;
	m_pIB->Lock(0, 0, (LPVOID*)&ib, 0);
	{
		memcpy(ib, &m_vecLineIndex[0], m_vecLineIndex.size()*sizeof(WORD));
	}
	m_pIB->Unlock();
}

void cHexagon::Update()
{		
	//m_end = GetTickCount();
	
	static float n = 0;
	static float nn = 0;
	n +=  m_time;
	nn += m_time2;
	static int i = 0, j = 1;
	static int ii = 0, jj = 1, kk =2;
	if (n > 1.0f )
	{
		i++; j++; 
		if (i == 6){
			i = 0;
		}
		if (j == 6){
			j = 0;
		}
		
		n = 0.0f;
	}
	if (nn > 1.0f)
	{
		ii += 2; jj += 2; kk += 2;
		if (ii == 6){
			ii = 0;
		}
		if (jj == 7){
			jj = 1;
		}
		if (kk == 6){
			kk = 0;
		}
		nn = 0.0f;
	}
	D3DXVECTOR3 dir = m_vecListVertex[j].p - m_vecListVertex[i].p;
	D3DXVECTOR3 dir1 = LinearInterpolation(m_vecListVertex[ii].p, m_vecListVertex[jj].p,nn);
	D3DXVECTOR3 dir2 = LinearInterpolation(m_vecListVertex[jj].p, m_vecListVertex[kk].p, nn);
	D3DXVECTOR3 dir3 = dir2 - dir1;

	m_pTeapot->Update(m_matT,
		LinearInterpolation(m_vecListVertex[i].p, m_vecListVertex[j].p, n),dir);
	m_pTeapot2->Update(m_matT,
		BezierInterpolation(m_vecListVertex[ii].p, m_vecListVertex[jj].p,	m_vecListVertex[kk].p,nn),dir3);
}

void cHexagon::Render()
{		
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetIndices(m_pIB);	
	g_pD3DDevice->DrawIndexedPrimitive(
		D3DPT_LINELIST, 0, 0, 
		m_vecListVertex.size(),
		0, m_vecListVertex.size());
	/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecListVertex.size() / 2,
		&m_vecListVertex[0], sizeof(ST_PC_VERTEX));*/
	for (auto p : m_vecSphere)
		p->Render();

	m_pTeapot->Render();
	m_pTeapot2->Render();
	
}

D3DXVECTOR3 cHexagon::LinearInterpolation(D3DXVECTOR3& vecP0, D3DXVECTOR3& vecP1, float n)
{	
	return (vecP0 + (vecP1 - vecP0) * n);
	
}

D3DXVECTOR3 cHexagon::BezierInterpolation(
	D3DXVECTOR3& vecP0, D3DXVECTOR3& vecP1, D3DXVECTOR3& vecP2, float n)
{
	D3DXVECTOR3 p0 = (vecP0 + (vecP1 - vecP0) * n);
	D3DXVECTOR3 p1 = (vecP1 + (vecP2 - vecP1) * n);
	return LinearInterpolation(p0, p1,n);
	
}