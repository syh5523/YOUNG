// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


//------------------------------------------------------------------------
//							���� ��� �߰�
//------------------------------------------------------------------------
#include <vector>
#include <string>
#include <assert.h>
#include <set>
#include <map>
#include <list>
#include <math.h>
using namespace std;
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#include <iostream>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;
#define SAFE_RELEASE(p){if(p) p->Release(); p =NULL;}
#define SAFE_DELETE(p) { if (p) delete p; p = NULL; }
#define SAFE_ADD_REF(p) { if(p) p->AddRef();}

//------------------------------------------------------------------------
//								�̱���
//------------------------------------------------------------------------
#define SINGLETON(class_name) \
	private: \
		class_name(void); \
		~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{\
			static class_name instance; \
			return &instance; \
		}

//------------------------------------------------------------------------
//	��, �� (varType : �ڷ��� // varName : �����̸�  // funName : �Լ� �̸�)
//------------------------------------------------------------------------

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var)\
	{ \
		if(varName != var) \
			{\
				SAFE_ADD_REF(var);\
			} \
		SAFE_RELEASE(varName); \
		varName = var;\
	}

//------------------------------------------------------------------------
//							�̱������ �߰�
//------------------------------------------------------------------------
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cObjectManager.h"

//-----------------------------------------------------------
//						 ����ü
//-----------------------------------------------------------

struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;     //Vector x,y,z ��ǥ ��
	D3DCOLOR		c;	   //DWORD color��

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};

};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;				//������
	D3DXVECTOR3 n;				//��������
	D3DXVECTOR2 t;				//�ؽ�ó, u,v��ǥ

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;	// �ؽ���

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

//-----------------------------------------------------------
//				     �ؽ�ó 
//-----------------------------------------------------------
#define OBJECT_SCAILING (0.01f)
#define EPSILON			(0.001f)
#define SAMPLE_WIDTH    (0.015625f)
#define SAMPLE_HEIGHT   (0.03125f)

