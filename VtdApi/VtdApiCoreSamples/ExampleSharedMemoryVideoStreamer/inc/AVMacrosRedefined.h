#ifndef AVMACROSREDEFINED_H
#define AVMACROSREDEFINED_H

// Fixes for taking address of temporary arrays

#undef av_err2str
#define av_err2str(errnum)       av_make_error_string((char*) __builtin_alloca(AV_ERROR_MAX_STRING_SIZE), AV_ERROR_MAX_STRING_SIZE, errnum)

#undef av_ts2timestr
#define av_ts2timestr(ts, tb)    av_ts_make_time_string((char*) __builtin_alloca(AV_TS_MAX_STRING_SIZE), ts, tb)

#undef av_ts2str
#define av_ts2str(ts)            av_ts_make_string((char*) __builtin_alloca(AV_TS_MAX_STRING_SIZE), ts)

#endif
