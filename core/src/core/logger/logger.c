#include "core/core.h"

#include <stdarg.h>

typedef enum CLoggerType
{
    LoggerType_Info,
    LoggerType_Debug,
    LoggerType_Warning,
    LoggerType_Error,
    LoggerType_Count,
} CLoggerType;

const char *logger_types_string[LoggerType_Count] = {
    "INFO",
    "DEBUG",
    "WARNING",
    "ERROR",
};

void
log_message(CLoggerType type, const char *format, va_list args)
{
    char       *buffer       = NULL;
    FILE       *stream       = NULL;
    const char *prefix       = "";
    const u32   prefix_width = 8;

    stream = stdout;
    prefix = logger_types_string[type];

    va_list args_copy;
    va_copy(args_copy, args);
    int32_t buffer_size = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    buffer = alloca(buffer_size + 1);
    vsnprintf(buffer, buffer_size + 1, format, args);

    const u32 padding = prefix_width - (u32)strlen(prefix);
    fprintf(stream, " - %s:", prefix);
    fprintf(stream, "%*s %s", padding, "", buffer);
}

void
log_info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log_message(LoggerType_Info, format, args);
    va_end(args);
}

void
log_debug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log_message(LoggerType_Debug, format, args);
    va_end(args);
}

void
log_warning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log_message(LoggerType_Warning, format, args);
    va_end(args);
}

void
log_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log_message(LoggerType_Error, format, args);
    va_end(args);
}
