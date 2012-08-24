#include <Windows.h>
#include <ShObjIdl.h>

#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	if (argv[1] == NULL) {
		printf("Please provide an appId to launch");
		return -1;
	}
	else {
		LPCWSTR appId = argv[1];

		CoInitialize(NULL);
		IApplicationActivationManager* paam = NULL;
		HRESULT hr = E_FAIL;
		__try {
			hr = CoCreateInstance(CLSID_ApplicationActivationManager,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&paam));
			//if (FAILED(hr)) return 0;

			DWORD pid = 0;
			hr = paam->ActivateApplication(appId,nullptr,AO_NONE,&pid);
			//if (FAILED(hr)) return 0;
			cout<< hex <<hr ;
			if(hr == 0) {
				wprintf(L"Activated  %s with pid %d\r\n",appId,pid);
			}
		}
		__finally {
			if (paam) {
				paam->Release();
			}
		}

		CoUninitialize();
		getchar();
		return 0;
	}
}
