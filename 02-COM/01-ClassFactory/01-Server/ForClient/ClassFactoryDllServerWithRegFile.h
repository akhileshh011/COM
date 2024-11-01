#pragma once

class ISum :public IUnknown
{
public:
	//ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0; //pure virtual int * as return type is HRESULT (compulsary) sum will be in this int*	
};

class ISubtract :public IUnknown
{
public:
	//ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

//CLSID of SumSubtract Component {939E1C5E-861F-4FBA-9148-56B7BD4405F1} - Stringised GUID
const CLSID CLSID_SumSubtract = {0x939e1c5e, 0x861f, 0x4fba, 0x91, 0x48, 0x56, 0xb7, 0xbd, 0x44, 0x5, 0xf1}; //Numeric Form of GUID

// IID of ISum Interface {A7CBCF56-58F2-4840-873A-EF59CB1303EB}
const IID IID_ISum = { 0xa7cbcf56, 0x58f2, 0x4840, 0x87, 0x3a, 0xef, 0x59, 0xcb, 0x13, 0x3, 0xeb };

// IID of ISubtract Interface {7E4B81D8-8376-47F0-BA10-0AFF29E63CB6}
const IID IID_ISubtract = { 0x7e4b81d8, 0x8376, 0x47f0, 0xba, 0x10, 0xa, 0xff, 0x29, 0xe6, 0x3c, 0xb6 };
