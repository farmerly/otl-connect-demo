#ifndef OTL_CONTROL_H_H_H
#define OTL_CONTROL_H_H_H

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif //!WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <Windows.h>
#include <process.h>
#pragma comment(lib, "Ws2_32.lib")
#undef WIN32_LEAN_AND_MEAN
#endif //!_WIN32

#define OTL_ORA11G_R2
#include "otlv4.h"

#define CONNSTR_LEN	256

namespace otl
{
    class OtlController
    {
    public:
        OtlController();
        virtual ~OtlController();
    public:
        void initialize(const char *conn_str);
        bool connect();
        void disconnect();
        bool connectionTest();
    private:
        CRITICAL_SECTION db_lock_;
        otl_connect db_conn_;
        char *conn_str_;
    };
}

#endif