//============================================================================
// Name        : logger.h
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdint.h>
#include <sstream>
#define __FILENAME__ __FILE__

//#define DZHANG_DEBUG 0

#ifdef DZHANG_DEBUG
#define LOGC(format, ...) printf("[%s+%d][%s]: " format "\n", __FILENAME__, __LINE__,\
                            __FUNCTION__, ##__VA_ARGS__)
#define LOGCE(format, ...) printf("[%s+%d][%s]: " format "\n", __FILENAME__, __LINE__,\
                            __FUNCTION__, ##__VA_ARGS__)
#else
#define LOGC(format, ...)
#define LOGCE(format, ...)
#endif


typedef enum log_rank {
    INFO,
    WARNING,
    ERROR,
    FATAL,
	NODEBUG
}log_rank_t;

void initLogger(const std::string&info_log_filename,
                const std::string&warn_log_filename,
                const std::string&error_log_filename);

class Logger {
    friend void initLogger(const std::string& info_log_filename,
                           const std::string& warn_log_filename,
                           const std::string& erro_log_filename);

public:
    Logger(log_rank_t log_rank) : m_log_rank(log_rank) {};

    ~Logger();

#ifdef DZHANG_DEBUG
    static std::ostream& start(log_rank_t log_rank,
    		const std::string& file_name,
			const int line,
			const std::string& function);
#else
    static std::stringstream& start(log_rank_t log_rank,
    		const std::string& file_name,
			const int line,
			const std::string& function);
#endif



private:

#ifdef DZHANG_DEBUG
    static std::ostream& getStream(log_rank_t log_rank);
#else
    static std::stringstream& getStream(log_rank_t log_rank);
#endif

    static std::stringstream nonDebugStr;

    static std::ofstream m_info_log_file;                   ///< 信息日子的输出流
    static std::ofstream m_warn_log_file;                  ///< 警告信息的输出流
    static std::ofstream m_error_log_file;                  ///< 错误信息的输出流
    log_rank_t m_log_rank;                             ///< 日志的信息的等级
};

//#define LOGCC(log_rank)   \
//Logger(log_rank).start(log_rank, __FILE__, __LINE__, __FUNCTION__)

#ifdef DZHANG_DEBUG
#define LOGCC   \
Logger(log_rank_t::INFO).start(log_rank_t::INFO, __FILE__, __LINE__, __FUNCTION__)
#else
#define LOGCC Logger(log_rank_t::WARNING).start(log_rank_t::WARNING, __FILE__, __LINE__, __FUNCTION__)
#endif

//
//#define CHECK(a)                                          \
//if(!(a)) {                                              \
//       LOGCC(ERROR) << " CHECK failed " << endl              \
//                   << #a << "= " << (a) << endl;          \
//       abort();                                            \
//   }                                                      \
//
//#define CHECK_NOTNULL(a)                                    \
//   if( NULL == (a)) {                                      \
//       LOGCC(ERROR) << " CHECK_NOTNULL failed "              \
//                   << #a << "== NULL " << endl;           \
//       abort();                                            \
//    }
//
//#define CHECK_NULL(a)                                       \
//   if( NULL != (a)) {                                      \
//       LOGCC(ERROR) << " CHECK_NULL failed " << endl         \
//                   << #a << "!= NULL " << endl;           \
//       abort();                                            \
//    }
//
//
//#define CHECK_EQ(a, b)                                      \
//   if(!((a) == (b))) {                                     \
//       LOGCC(ERROR) << " CHECK_EQ failed "  << endl          \
//                   << #a << "= " << (a) << endl           \
//                   << #b << "= " << (b) << endl;          \
//       abort();                                            \
//    }
//
//#define CHECK_NE(a, b)                                      \
//   if(!((a) != (b))) {                                     \
//       LOGCC(ERROR) << " CHECK_NE failed " << endl           \
//                   << #a << "= " << (a) << endl           \
//                   << #b << "= " << (b) << endl;          \
//       abort();                                            \
//    }
//
//#define CHECK_LT(a, b)                                      \
//   if(!((a) < (b))) {                                      \
//       LOGCC(ERROR) << " CHECK_LT failed "                   \
//                   << #a << "= " << (a) << endl           \
//                   << #b << "= " << (b) << endl;          \
//       abort();                                            \
//    }
//
//#define CHECK_GT(a, b)                                      \
//   if(!((a) > (b))) {                                      \
//       LOGCC(ERROR) << " CHECK_GT failed "  << endl          \
//                  << #a <<" = " << (a) << endl            \
//                   << #b << "= " << (b) << endl;          \
//       abort();                                            \
//    }
//
//#define CHECK_LE(a, b)                               \
//if(!((a) <= (b))) {                                  \
//       LOGCC(ERROR) << " CHECK_LE failed "  << endl    \
//                   << #a << "= " << (a) << endl      \
//                   << #b << "= " << (b) << endl;     \
//       abort();                                      \
//    }
//
//#define CHECK_GE(a, b)                                      \
//   if(!((a) >= (b))) {                                     \
//       LOGCC(ERROR) << " CHECK_GE failed "  << endl          \
//                   << #a << " = "<< (a) << endl            \
//                   << #b << "= " << (b) << endl;          \
//       abort();                                            \
//    }
//
//#define CHECK_DOUBLE_EQ(a, b)                               \
//   do {                                                    \
//       CHECK_LE((a), (b)+0.000000000000001L);              \
//       CHECK_GE((a), (b)-0.000000000000001L);              \
//    }while (0)




#endif //__LOGGER__

