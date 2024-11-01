Providing you with 3 Files:
1. ClassFactoryDllServerWithRegFile.h
2. ClassFactoryDllServerWithRegFile.dll
3. ClassFactoryDllServerWithRegFile.reg

Header File contains 2 Interfaces ISum and ISubtract
ISum provides sum of 2 integers (functionality)
ISubtract provides difference of 2 integers (functionality)

Both interfaces inherit from IUnknown
Both interfaces and required GUIDs are given in header file 
You can call above mentioned functions on respective interface pointers

Before building your client application do the following steps:
1. Copy the DLL to C:\Windows\System32
2. Double Click on .reg file to register the DLL
3. Build & Run your client application 	