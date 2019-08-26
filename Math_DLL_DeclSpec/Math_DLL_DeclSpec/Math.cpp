
#include<Windows.h>

bool WINAPI DllMain(HINSTANCE hInstance, DWORD dwreason, LPVOID lpResrved)
{
	// Perform actions based on the reason for calling.
	switch (dwreason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}


extern "C" __declspec(dllexport) int MakeSquare(int num)
{
	return num * num;
}

extern "C" bool IsNumberNegative(int num)
{
	if (num > 0)
		return true;
	else
		return false;
}