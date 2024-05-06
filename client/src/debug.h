#ifndef _DEBUG_
#define _DEBUG_

#define RED_COLOR "\x1B[31m"
#define GREEN_COLOR "\x1B[32m"
#define YELLOW_COLOR "\x1B[33m"
#define BLUE_COLOR "\x1B[34m"
#define WHITE_COLOR "\x1B[37m"

#ifdef DISABLE_DEBUGGING
#define DISABLE_ERRORS
#define DISABLE_DEBUG
#define DISABLE_WARN
#define DISABLE_INFO
#endif

#ifndef DISABLE_ERRORS
#define ERR(...) printf(RED_COLOR "[ERROR] " WHITE_COLOR __VA_ARGS__);
#else
#define ERR(...)
#endif

#ifndef DISABLE_DEBUG
#define DEBUG(...) printf(BLUE_COLOR "[DEBUG] " WHITE_COLOR __VA_ARGS__);
#else
#define DEBUG(...)
#endif

#ifndef DISABLE_WARN
#define WARN(...) printf(YELLOW_COLOR "[WARN] " WHITE_COLOR __VA_ARGS__);
#else
#define DEBUG(...)
#endif

#ifndef DISABLE_INFO
#define INFO(...) printf(GREEN_COLOR "[INFO] " WHITE_COLOR __VA_ARGS__);
#else
#define DEBUG(...)
#endif

#endif // !_DEBUG_
