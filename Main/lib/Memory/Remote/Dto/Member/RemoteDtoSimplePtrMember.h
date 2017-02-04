﻿#ifndef _MEMORY_REMOTEDTOSIMPLEPTRMEMBER_H_
#define _MEMORY_REMOTEDTOSIMPLEPTRMEMBER_H_

#pragma once

#include "Base/RemoteDtoMemberBase.h"

namespace Memory
{
    template <class T>
    class RemoteDtoSimplePtrMember : public RemoteDtoMemberBase
    {
        std::vector<T>  _dataValues;
        uintptr_t       _ptrValue;

    public:

        explicit        RemoteDtoSimplePtrMember( const size_t& offset, const size_t& size );
                        ~RemoteDtoSimplePtrMember() {}

        bool            OnUpdate( SharedRemoteProcessService remoteProcessService, size_t level, std::vector<byte>* data ) override;
        size_t          GetSize() const override;

        T*              GetPtr();
    };

    template <class T>
    RemoteDtoSimplePtrMember<T>::RemoteDtoSimplePtrMember( const size_t& offset, const size_t& size ) :
        RemoteDtoMemberBase( offset ),
        _ptrValue( 0x0 )
    {
        _dataValues = std::vector<T>( size );
    }

    template <class T>
    bool RemoteDtoSimplePtrMember<T>::OnUpdate( SharedRemoteProcessService remoteProcessService, size_t /*level*/, std::vector<byte>* data )
    {
        _ptrValue = *reinterpret_cast< uintptr_t* >( &data->at( GetOffset() ) );
        return _ptrValue != 0x0 && remoteProcessService->Read( _ptrValue, &_dataValues.at( 0 ), _dataValues.size() );
    }

    template <class T>
    size_t RemoteDtoSimplePtrMember<T>::GetSize() const
    {
        return sizeof( T* );
    }

    template <class T>
    T* RemoteDtoSimplePtrMember<T>::GetPtr()
    {
        if( _ptrValue == 0x0 )
            return nullptr;
        return reinterpret_cast< T* >( &_dataValues.at( 0 ) );
    }

    using RemoteString = RemoteDtoSimplePtrMember<char>;
}

#endif /* _MEMORY_REMOTEDTOSIMPLEPTRMEMBER_H_ */
