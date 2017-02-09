/**
 * @file platform.h
 * @Synopsis  实现代码移植、跨平台、方便调用的宏定义.
 *	1) 什么是封装?
 *	2) 为什么要封装?
 *	3) 如何实现封装?
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.12.1
 * @date 2014-07-19
 */
#pragma once

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>			// va_list
#include <assert.h>			// asert
#include <unistd.h>			// uint32_t int32_t ... 
#include <unordered_map>	// Hash Map
#include <string>			// std::string

#define DEBUG 1
#if DEBUG
#define SCREEN_LOG 1
#else
#define SCREEN_LOG 0
#endif

#define RAYMAN_ASIO_SERVER_VERSION 22

#if !defined __GNUC__
#error st_asio_application only support gcc.
#endif

#if defined __GNUC__ && (__GNUC__ < 4 || __GNUC__ == 4 && __GNUC_MINOR__ < 7)
#error st_asio_application must be compiled with gcc4.7 or higher.
#endif

#if defined __GNUC__
#define size_t_format "%tu"
#define TP_THIS this->
#endif               
                       
#ifndef UNIFIED_OUT_BUF_NUM
#define UNIFIED_OUT_BUF_NUM 1024
#endif 

/// 定义extern "C" 的宏
#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
/*The lines within extern "C" */
#define DECLS_BEGIN
#define DECLS_END
#endif/*__cplusplus*/

#ifndef SERVER_IP
#define SERVER_IP "0.0.0.0"
#endif
#ifndef LOCAL_SERVER_IP
#define LOCAL_SERVER_IP "127.0.0.1"
#endif
#ifndef SERVER_PORT
#define SERVER_PORT 5050
#endif

// 移植代码需要用到的宏
#define NetworkServer CNetworkServer
#define xAppliction CApplication
#define xHashMap std::unordered_map
#define xstring std::string
#define xHashMap std::unordered_map
#define CMulitThreadDB CMutiThreadDB
#define MulitThreadDB CMutiThreadDB
#define CustParament CCustomParameters
#define TimetToMysqlDataTime timeToMysqlDataTime
#define Long64ToString uint64ToString
#define Singleton CSingleton
#define Config operatorconfig::CConfig
#define getAPPDB() xAppliction::getSingleton().getDBPointer()
#define getSMPageSize() CApplication::getSingleton().getMaxClient()
// 应对之前代码使用CTimer、CNetworkListener的问题 25/09/14
//#define CTimer ITimer
//#define CNetworkListener INetworkListener

#define LONG64 int64_t 
///8位整型-125--125之间 
#define int8 int8_t 
//无符8位整理0--255之间 
#define uint8 uint8_t
#define int16 int16_t
#define uint16 uint16_t
#define uint32 uint32_t
#define int32 int32_t

#define strcpy_s(dest, size, src) strncpy(dest, src, size)

#define XClass 
#define _TEXT
#define TCHAR char
#define Sleep(a) usleep(a*1000)

#define IntToStr(a) Helper::intToString(a)
#define NowTime (uint32_t)time(NULL)

#define stows(a) a 
#define wtos(a) a 
#define ifstream std::ifstream 

#define THROW(a) xLogMessager::getSingleton().logMessage(xstring("THROW:")+a,Log_ErrorLevel);\
std::exception ex(std::string(std::string(__FILE__)+Helper::IntToString( __LINE__)+ a).c_str());throw(ex); 

// 禁止使用拷贝构造函数和 operator= 赋值操作的宏
// 应该类的 private: 中使用
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
            TypeName(const TypeName&); \
            void operator=(const TypeName&)

#define SafeDelete(a) do { if (NULL != a) { delete a; a = NULL; } } while(0);
#define SafeDeleteArray(a) do { if (NULL !=a) { delete []a; a = NULL; } } while(0);
#define SafeFree(a) do { if (NULL != a) { free(a); a = NULL;} } while(0);
#define IfFalseReturn(a) do { if (false == a) { return; } } while(0);

#define CHECKERRORANDRETURN(b) if( b == false) {return ;} 

#define CHECKERRORANDCONTINUE(b) if(b == false) { continue;} 

#define CHECKERRORANDRETURNRESULT(b) if(b == false) { return b;} 
#define CHECKNULLANDRETURNRESULT(b) if(NULL == b) { return b;} 

#define CHECKERROR(b) if (b == false) { } 

#define CHECKERRORANDRETURNVALUE(b,ret) if(b==false) { return ret;}

#define MEMBER_DECLARE(Type, Member) Type m_##Member;  
#define MEMBER_GETTER(Type, Member) const Type get##Member(void) const { return m_##Member; }  
#define MEMBER_SETTER(Type, Member) void set##Member(const Type &t) { m_##Member = t; }  
#define MEMBER_ACCESSOR(Type, Member) MEMBER_GETTER(Type, Member) MEMBER_SETTER(Type, Member)

///////////////////////////////////////////////////
class log_formater {
public:
	static void all_out(char* buff, const char* fmt, va_list& ap) {
		assert(nullptr != buff);
		time_t now = time(nullptr);
		ctime_r(&now, buff);
		auto len = strlen(buff);
		assert(len > 0);
		if ('\n' == *std::next(buff, len - 1)) {
			--len;
		}
		strcpy(std::next(buff, len), " -> ");
		len += 4;
		vsnprintf(std::next(buff, len), UNIFIED_OUT_BUF_NUM - len, fmt, ap);
	}
};  // class log_formater

#define all_out_helper(buff) va_list ap; va_start(ap, fmt); log_formater::all_out(buff, fmt, ap); va_end(ap)
#define all_out_helper2 char output_buff[UNIFIED_OUT_BUF_NUM]; all_out_helper(output_buff); puts(output_buff)

#ifndef CUSTOM_LOG
class unified_out {
public:
#ifdef NO_UNIFIED_OUT
	static void fatal_out(const char* fmt, ...) {}
	static void error_out(const char* fmt, ...) {}
	static void warning_out(const char* fmt, ...) {}
	static void info_out(const char* fmt, ...) {}
	static void debug_out(const char* fmt, ...) {}
#else
	static void fatal_out(const char* fmt, ...) {all_out_helper2;}
	static void error_out(const char* fmt, ...) {all_out_helper2;}
	static void warning_out(const char* fmt, ...) {all_out_helper2;}
	static void info_out(const char* fmt, ...) {all_out_helper2;}
	static void debug_out(const char* fmt, ...) {all_out_helper2;}
#endif
}; // class unified_out
#endif

/// 定义LOG 函数的宏
#if SCREEN_LOG
#define print_log( format, ... ) unified_out::info_out( format, ##  __VA_ARGS__ )
#else
#define print_log( format, ... ) do {} while (0)
#endif

#if 0
/// 无返回值的函数
#define TP_RETURN_IF_FAILED(p) if(!(p)) \
    {print_log("%s:%s:%d Warning: "#p" failed.\n", \
          __FILE__, __func__, __LINE__); return;}
            
#define TP_RETURN_VAL_IFFAILED(p, ret) if(!(p)) \
    {print_log("%s:%d Warning: "#p" failed.\n", \
          __func__, __LINE__); return (ret);}
#else
#define TP_RETURN_IF_FAILED(p)  do{}while(0);
#define TP_RETURN_VAL_IFFAILED(p, ret)  do{}while(0);
#endif


