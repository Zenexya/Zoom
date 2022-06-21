#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <iterator>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>
#include <thread>
DWORD Proc;
DWORD PID;
using namespace std;

void print(const char* text) {
	std::cout << text, "\n";
}

void Start() {
	const auto freecon = &FreeConsole;
	DWORD old;
	VirtualProtect(freecon, 1, PAGE_EXECUTE_READWRITE, &old);
	*reinterpret_cast<std::uint8_t*>(freecon) = 0xC3;
	VirtualProtect(freecon, 1, old, &old);
	AllocConsole();
	FILE* file_stream;
	freopen_s(&file_stream, "CONIN$", "r", stdin);
	freopen_s(&file_stream, "CONOUT$", "w", stdout);
	freopen_s(&file_stream, "CONOUT$", "w", stderr);
	SetConsoleTitleA("Zoom");
}

int main() {
	Start();
	print("Injected");
}

// Credits to fishy for the code below

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		std::thread(main).detach();
		break;
	}
	return TRUE;
}

// Credits to fishy for the code ^^
