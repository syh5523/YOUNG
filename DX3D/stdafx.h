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


#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;
#define SAFE_RELEASE(p){if(p) p->Release(); p =NULL;}
#define SAFE_DELETE(p) { if (p) delete p; p = NULL; }

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
private: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var) { varName = var; }

//------------------------------------------------------------------------
//							�̱������ �߰�
//------------------------------------------------------------------------
#include "cDeviceManager.h"


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
	D3DXVECTOR3 t;				//�ؽ�ó, u,v��ǥ

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

//-----------------------------------------------------------
//				
//-----------------------------------------------------------