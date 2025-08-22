# 🕵️‍♂️ shellcode-stealth 🚀

A sophisticated shellcode loader implementation that leverages Base32 encoding and class constructor execution to bypass traditional detection methods. This loader demonstrates advanced techniques for executing payloads in memory while minimizing detection signatures.

## 📊 Overview

This shellcode loader uses several innovative techniques to avoid detection:

- **🔒 Base32 Encoding**: Payloads are encoded with Base32 to avoid signature-based detection
- **⚡ Class Constructor Execution**: The payload executes via a class constructor before `main()` is called
- **🛡️ API Obfuscation**: Uses `EnumCalendarInfoEx` for execution instead of more common APIs
- **💾 Memory Protection Manipulation**: Properly adjusts memory permissions from RW to RX

## 🚨 Detection Rate

**Current detection: 2/36** (as reported by KleenScan)  
- One detection is marked as "unknown"  
- One generic detection  

[🔍 View full scan results](https://kleenscan.com/scan_result/2db13e2dfcd5935a09b02e82e09545bc8e5bb45041093adf80ee1167ff9b899d)

## ⚙️ How It Works

The loader employs several evasion techniques:

1. **🏗️ Constructor Execution**: The `shell_exec` class constructor runs before `main()`
2. **🖥️ Console Removal**: `FreeConsole()` detaches from the current console window
3. **🔓 Base32 Decoding**: Decodes the payload from Base32 format in memory
4. **🧠 Memory Allocation**: Uses `VirtualAlloc` to allocate RW memory
5. **🛡️ Permission Modification**: Changes memory protection from RW to RX using `VirtualProtect`
6. **⚡ API Execution**: Uses `EnumCalendarInfoEx` to execute the shellcode
7. **✅ Dummy Binary**: Embeds a innocent executable (such as `RobloxPlayerInstaller.exe`) as a resource

## 🚀 Usage

### 1. Generate Shellcode with Donut

First, generate your shellcode using Donut:

```bash
donut -i stub.exe
```

### 2. Encode the Shellcode

Use the provided `encode.py` script to convert your shellcode to Base32 format:

```bash
python encode.py
```

This will generate a `payload.h` file containing your Base32-encoded shellcode.

### 3. Compile the Loader

Open the provided `shellcode-stealth.sln` solution file in Visual Studio and simply press `Ctrl+B` to build the project! 🏗️⚡

## 🔬 Technical Details

### Constructor Execution

The payload executes through the `shell_exec` class constructor, which runs before the `main()` function. This technique bypasses expectations about program execution flow.

```cpp
class shell_exec {
public:
    shell_exec() {
        FreeConsole();
        // decoding + execution
    }
};
// create a instance which triggers execution before main
shell_exec x;
int main() {
    return 0; // never executes
}
```

### Memory Protection

The loader properly handles memory protection:
1. Allocates memory as READWRITE (`PAGE_READWRITE`)
2. Copies the decoded shellcode
3. Changes protection to EXECUTE_READ (`PAGE_EXECUTE_READ`)
4. Executes the shellcode

### Execution

Uses `EnumCalendarInfoEx` instead of more common APIs like `CreateThread` or `EnumChildWindows` to avoid API based detection(s).

## 📋 Requirements

- Windows OS
- C++ Compiler (Visual Studio recommended for easy building) 🏗️
- Python 3 (for encode.py) 🐍
- Donut (for shellcode generation) 🍩

## ⚠️ Disclaimer

This tool is for educational and research purposes only. Use only on systems you own or have explicit permission to test. The authors are not responsible for any misuse of this tool.

## 📜 License

This project is provided for educational purposes only.
