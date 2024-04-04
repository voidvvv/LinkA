#ifndef __LINKALOG_H__
#define __LINKALOG_H__
#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE//必须定义这个宏,才能输出文件名和行号


#define LinkALog spdlog::get("LinkALogger")  

#endif // __LINKALOG_H__