#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

//class declarations
class CSumSubtract :public ISum, ISubtract 
{
private:
	long m_cRef; // Binary Encapsulation. IRajeshPradhan telling about details thickness of brush etc 
public:
	//constructor method declarations
	CSumSubtract(void);
	//destructor method declarations
	~CSumSubtract(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall	AddRef(void);
	ULONG __stdcall Release(void);

	//ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	//ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
}; 

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtractClassFactory(void);

	//destructor method declarations
	~CSumSubtractClassFactory(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDLl, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}

//Implementation of CSumSubtract's Constructor Method
CSumSubtract::CSumSubtract(void)
{
	//hardcoded initialization to anticipate possible failure of QueryInterface()
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CSumSubtract's Destructor Method
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
}

//Implementation of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this); //Why ISum Answer in notes
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0); //m_cRef vagaire sagla udala ahe so no common return and seperate return(0)
	}
	return(m_cRef);
}

//Implementation of ISum's Methods 
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;

	return(S_OK);
}

//Implementation of ISubtract's Methods 
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;

	return(S_OK);
}

//Implementation Of CSumSubtractClassFactory's Constructor Method 
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Implementation Of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//no code 
}

//Implementation Of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods 
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{ 
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef(); //Type cast *ppv in IUnknown and give call to AddRef() {Necessary to typecast)

	return(S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this); //Call to Destructor
		return(0);
	}

	return(m_cRef);
}

//Implementation Of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr = S_OK;

	//code 
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	
	//create the instance of component i.e. of CSumSubtract class 
	pCSumSubtract = new CSumSubtract;  

	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface 
	hr = pCSumSubtract->QueryInterface(riid, ppv);

	pCSumSubtract->Release(); //anticipate possible failure of QueryInterface() 
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock) //Flag Lock
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

//Implementation Of Exported Functions From This Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) //COM's Function (Procedural to Object	Oriented)
{
	//variable declarations
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr = S_OK;

	//code
	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory; //Call to Constructor of CSumSubtractClassFactory (Go to Constructor - Flow)
	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv); //ClassFactory chya QueryInterface la call
	pCSumSubtractClassFactory->Release(); // anticipate possible failure of QueryInterface()

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}