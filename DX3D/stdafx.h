// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


//------------------------------------------------------------------------
//							공용 헤더 추가
//------------------------------------------------------------------------
#include <vector>
#include <string>
#include <assert.h>
#include <set>
#include <map>
#include <list>
#include <math.h>

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;
#define SAFE_RELEASE(p){if(p) p->Release(); p =NULL;}
#define SAFE_DELETE(p) { if (p) delete p; p = NULL; }

//------------------------------------------------------------------------
//								싱글톤
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
//	겟, 셋 (varType : 자료형 // varName : 변수이름  // funName : 함수 이름)
//------------------------------------------------------------------------

#define SYNTHESIZE(varType, varName, funName)\
private: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var) { varName = var; }

//------------------------------------------------------------------------
//							싱글톤헤더 추가
//------------------------------------------------------------------------
#include "cDeviceManager.h"


//-----------------------------------------------------------
//						 구조체
//-----------------------------------------------------------

struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;     //Vector x,y,z 좌표 값
	D3DCOLOR		c;	   //DWORD color값

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};

};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;				//포지션
	D3DXVECTOR3 n;				//법선벡터
	D3DXVECTOR2 t;				//텍스처, u,v좌표

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;	// 텍스쳐

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

//-----------------------------------------------------------
//				     텍스처 
//-----------------------------------------------------------
#define EPSILON			(0.1f)
#define SAMPLE_WIDTH    (0.015625f)
#define SAMPLE_HEIGHT   (0.03125f)




//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")