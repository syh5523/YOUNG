#pragma once

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice	cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
//public:
//	cDeviceManager();
//	~cDeviceManager();
//private:
//
//public:
//	static cDeviceManager* getInstance()
//	{
//		static  cDeviceManager instance;
//		return &instance;
//	}

public: 
	SINGLETON(cDeviceManager);

private:
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9		GetDevice();
	void Destroy();
};

