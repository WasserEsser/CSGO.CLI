﻿#include "HooksService.h"

namespace CLI
{
    HooksService::HooksService(
        Memory::SharedRemoteProcessService remoteProcessService,
        Memory::SharedRemoteFunctionService remoteFunctionService ) :
        _remoteProcessService( remoteProcessService ),
        _remoteFunctionService( remoteFunctionService ),
        _remoteHookService( std::make_shared<Memory::RemoteHookService>( remoteProcessService ) )
    {
        auto originProcessHandle = OpenProcess( PROCESS_REMOTE, FALSE, GetCurrentProcessId() );
        _sharedOriginProcessHandle = remoteProcessService->GetSharedHandle( originProcessHandle );
    }
}
