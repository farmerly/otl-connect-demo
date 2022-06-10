#include "otl_control.h"

otl::OtlController::OtlController()
{
    conn_str_ = new char[CONNSTR_LEN];
    memset(conn_str_, 0, CONNSTR_LEN);
    InitializeCriticalSection(&db_lock_);
}

otl::OtlController::~OtlController()
{
    DeleteCriticalSection(&db_lock_);
    if (conn_str_ != nullptr) {
        delete[] conn_str_;
        conn_str_ = nullptr;
    }
}

void otl::OtlController::initialize(const char *conn_str)
{
    memcpy(conn_str_, conn_str, strlen(conn_str));
}

bool otl::OtlController::connect()
{
    try {
        otl_connect::otl_initialize();
        db_conn_.rlogon(conn_str_, 1);
        return true;
    } catch (otl_exception &p) {
        printf("database connect error: ");
        printf("    errcode: %d", p.code);
        printf("    message: %s", p.msg);
        printf("    stmtext: %s", p.stm_text);
    }
    return false;
}

void otl::OtlController::disconnect()
{
    try {
        db_conn_.logoff();
    } catch (otl_exception &p) {
        printf("database disconnect error: ");
        printf("    errcode: %d", p.code);
        printf("    message: %s", p.msg);
        printf("    stmtext: %s", p.stm_text);
    }
}

bool otl::OtlController::connectionTest()
{
    try {
        char sql[] = "select * from dual";
        otl_stream select(1, sql, db_conn_);
        select.close();
        printf("database connection connected");
        return true;
    } catch (otl_exception &p) {
        printf("database connection disconnect: ");
        printf("    errcode: %d", p.code);
        printf("    message: %s", p.msg);
        printf("    stmtext: %s", p.stm_text);
    }
    return false;
}