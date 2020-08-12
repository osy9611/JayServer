#pragma once
#pragma waring(disable :4819)
#define _WINSOCKAPI_
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WS2tcpip.h>
#include<Windows.h>
#include<cassert>
#include<iostream>
#include<atltime.h>
#include<vector>
#include<deque>
#include<queue>
#include<string>
#pragma comment(lib, "ws2_32.lib")

#include"CriticalSection.h"
#include "GlobalSingleton.h"


#include "MemoryStream.h"
#include "PacketProc.h"

#include"IOCP.h"
#include"ServerSession.h"


#ifndef CONCATENATE
#define CONCATENATE( arg1, arg2 )   _CONCATENATE1( arg1, arg2 )
#define _CONCATENATE1( arg1, arg2 )  _CONCATENATE2( arg1, arg2 )
#define _CONCATENATE2( arg1, arg2 )  arg1##arg2	//## : 연산자와 두 식별자를 하나로 결합하는 연산자
#endif

#define DUMMY_STATEMENT	CONCATENATE(unsigned int  _DUMMY, __LINE__) =0; \
	CONCATENATE(_DUMMY,__LINE__) +=1;


