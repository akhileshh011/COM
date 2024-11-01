#include<windows.h>
#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"

//Global Callback Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declarations
ISum* pISum = NULL; 
ISubtract* pISubtract = NULL;

//Entry-point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyWindow_ARM"); //TEXT() is a macro 
	HRESULT hr = S_OK;

	//code 
	//Start COM Engine
	hr = CoInitialize(NULL); //COM Initialize (COM Engine Libraries )
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Co Initializtion failed"), TEXT("COM Error"), MB_OK|MB_ICONERROR);
		exit(0);
	}
	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

	//Initializing Window Class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
	 
	 //Register the aboove Window class
	RegisterClassEx(&wndclass);

	//Create the window in moemory
	hwnd = CreateWindow(szClassName, TEXT("Akhilesh Mali: First Name"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	//Show the window on the desktop
	ShowWindow(hwnd, iCmdShow);

	//Update / Paint the window on the desktop
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize(); //Stopping COM Engine	

	return((int)msg.wParam);
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM LParam)
{
	//function declarations
	void SafeInterfaceRelease(void);

	//variable declarations
	HRESULT hr = NULL;
	int num1=0, num2=0;
	int sum = 0, subtract = 0;
	TCHAR str[255];

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum); //Mentioned in Flow
		if (FAILED(hr))
		{ 
			MessageBox(NULL, TEXT("ISum Interface could not be obtained"), TEXT("COM Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
	
		//MessageBox(NULL, TEXT("ISum Interface Obtained"), TEXT("COM Success"), MB_OK | MB_ICONINFORMATION);
		num1 = 10;
		num2 = 20;
		pISum->SumOfTwoIntegers(num1, num2, &sum);
		wsprintf(str, TEXT("Sum of %d %d is %d"), num1, num2, sum);
		MessageBox(NULL, str, TEXT("Sum"), MB_OK | MB_ICONINFORMATION);
		hr = pISum->QueryInterface(IID_ISubtract,(void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface could not be obtained"), TEXT("COM Error"), MB_OK | MB_ICONERROR);
			//We should release pISum here if SafeInterfaceRelease() function is not called in WM_DESTROY
			DestroyWindow(hwnd); //GoTo WM_DESTROY
		}
		pISubtract->SubtractionOfTwoIntegers(num1, num2, &subtract);
		wsprintf(str, TEXT("Subtract of %d %d is %d"), num1, num2, subtract);
		MessageBox(NULL, str, TEXT("Subtraction"), MB_OK | MB_ICONINFORMATION);
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	//Calling default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, LParam));

}

void SafeInterfaceRelease(void)
{
	//code
	if (pISubtract)
	{
		pISubtract->Release(); //Memory Release
		pISubtract = NULL; //Bhanda Swachh
	}

	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
}
