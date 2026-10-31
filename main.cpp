#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <chrono>
#include <thread>

#define version "1.0.0_mwestudent"
using namespace std;


DWORD FindProcessId(const wstring& name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    DWORD pid = 0;

    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(name.c_str(), pe.szExeFile) == 0) {
                pid = pe.th32ProcessID;
                break;
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return pid;
}

int main() {
    cout << "ver:" << version << endl;

    int ret = system("taskkill /F /IM StudentMain.exe");
    cout << "[开发者参考 devloper]taskkill ret=" << ret << endl;
    bool gone = false;
    for (int i = 0; i < 30; ++i) {
        if (FindProcessId(L"StudentMain.exe") == 0) {
            gone = true;
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    if (gone){
        cout << "欸嘿，跑了，万岁~\(≧▽≦)/~！但……有没有可能没它？ Process is gone! Hooooooooray! But...it's not here?" << endl;
    }else{
        cout << "操，杀不死，跟他妈黏墙上的鸡屎一样！ Fuck, like chicken poop clinging to the wall!" << endl;
    }
    Beep(32, 100);
    Beep(800, 1000);
    cout << "5\n";
    Beep(800, 1000);
    cout << "4\n";
    Beep(800, 1000);
    cout << "3\n";
    Beep(800, 1000);
    cout << "2\n";
    Beep(800, 1000);
    cout << "1\n";
    Beep(1600, 1000);
    system("pause");
    return 0;
}
