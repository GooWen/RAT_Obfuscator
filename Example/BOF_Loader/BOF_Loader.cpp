﻿#include "Loader.h"

/*
* ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
* 1.Release x64
* 2.常规: 平台工具集(LLVM (clang-cl))
* 3.C/C++
* 优化: 优化(已禁用)
* 代码生成: 运行库(多线程); 安全检查(禁用安全检查)
* 命令行: 其他选项(-fno-optimize-sibling-calls -mno-avx -mno-avx2 -mno-sse -mno-sse2 -mno-sse3 -mno-ssse3 -mno-sse4 -mno-sse4.1 -mno-sse4.2)
* 4.链接器
* 清单文件: 生成清单(否)
* 调试: 生成调试信息(否)
*/

int main() {
    // 读取 Payload
    HANDLE hFile = CreateFileA("..\\..\\Obfuscator\\ObfBOF.bin", GENERIC_READ, NULL, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Failed to open ObfBOF.bin." << endl;
        return 0;
    }
    DWORD payloadSize = GetFileSize(hFile, NULL);
    PVOID pPayload = malloc(payloadSize);
    if (pPayload == NULL) {
        return 0;
    }
    DWORD readFileLen;
    ReadFile(hFile, pPayload, payloadSize, &readFileLen, NULL);

    // 运行 Payload
    char* commandPara = (char*)"cmd /c tasklist";
    int commandParaLen = strlen(commandPara) + 1;
    char* outputData;
    int outputDataLen = 0;
    PVOID specialParaList[] = { NULL };
    if (RunPayload((PBYTE)pPayload, payloadSize, -504283653, commandPara, commandParaLen, outputData, outputDataLen, specialParaList)) {
        if (outputDataLen > 0) {
            *(outputData + outputDataLen) = '\0';
            cout << outputData << endl;
        }
    }
    else {
        free(pPayload);
        pPayload = NULL;
    }

    commandPara = (char*)"C:\\Windows\\System32\\*";
    commandParaLen = strlen(commandPara) + 1;
    outputDataLen = 0;
    if (RunPayload((PBYTE)pPayload, payloadSize, 1280936002, commandPara, commandParaLen, outputData, outputDataLen, specialParaList)) {
        if (outputDataLen > 0) {
            *(outputData + outputDataLen) = '\0';
            cout << outputData << endl;
        }
    }
    else {
        free(pPayload);
        pPayload = NULL;
    }
}