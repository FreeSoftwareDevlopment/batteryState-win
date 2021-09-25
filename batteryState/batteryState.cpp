#include <iostream>
#include <Windows.h>
#include <string>
#include "running.hpp"
#include <thread>
#include <chrono>
#include <ShObjIdl_core.h>
#define ESC 0x1B
#include <stdio.h>
#define pset printf("\033[%d;%dH", 1, 1)

int main()
{
	if (running()) {
		std::cerr << "Application Already Running" << std::endl;
		return 0b00101;
	}

	char buffer[BUFSIZ];
	const char erase[] = "\x1b[2K";
	setvbuf(stdout, buffer, _IOFBF, BUFSIZ);

	pset;
	HWND ConsoleWindow{ GetConsoleWindow() };
	SetConsoleTitle(L"Sharkbyte Battery");
	SetConsoleMode(ConsoleWindow, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	int batteryLevel{ 0 };
	SYSTEM_POWER_STATUS status;
	do {
		std::cout << "Battery Window\nSharkbyteprojects\nBattery State:\n";
		GetSystemPowerStatus(&status);
		batteryLevel = status.BatteryLifePercent;
		std::cout << erase << "Battery Level:\t" << batteryLevel << "%\n";
		std::cout << erase << "AC LINE:\t" << (((char)(status.ACLineStatus)) == ((char)1) ? "PLUGGED IN" : "NOT PLUGGED IN") << "\n";
		std::cout << erase << "Full Lifetime:\t" << status.BatteryFullLifeTime << "\n";
		std::cout << erase << "Lifetime:\t" << status.BatteryLifeTime << std::endl;
		pset;
	} while (!(GetKeyState(VK_ESCAPE) & 0x8000));
	return 0;
}

