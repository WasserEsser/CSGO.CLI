﻿#ifndef _MEMORY_REMOTEFUNCTIONRESOLVER_H_
#define _MEMORY_REMOTEFUNCTIONRESOLVER_H_

#pragma once

#include <vector>
#include <windows.h>

namespace Memory
{
    class RemoteFunctionResolver
    {
    #ifndef _WIN64
        enum class IntelInstructions : byte
        {
            JMP = 0xE9
        };

        enum class IntelInstructionsLength : byte
        {
            JMP = 0x5
        };
    #else

    #endif

    public:

        bool Resolve( void* functionPtr, std::vector<byte>& functionBytes ) const;

    private:
        
        bool IsAtTheEnd( byte* bytes ) const;
    };
}

#endif /* _MEMORY_REMOTEFUNCTIONRESOLVER_H_ */
