// Some macro's to help w/ debugging


#ifndef INCLUDED_FECAPI_DEBUG_MACROS_H
#define INCLUDED_FECAPI_DEBUG_MACROS_H

//#define DEBUG_OUTPUT          // TODO: need to move this define to the CMAKE level
//#define DEBUG_OUTPUT_F        // TODO: need to move this define to the CMAKE level

#include <stdio.h>

#ifdef DEBUG_OUTPUT
#define DEBUG_PRINT_UCHAR_ARRAY(a, n) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        printf("%u ", *(a+zzzzzzzz)); \
    } \
    printf("\n"); \
    fflush(stdout); \
} while(0)  
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR(a, n) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        printf("%u ", (unsigned char)*(a+zzzzzzzz)); \
    } \
    printf("\n"); \
    fflush(stdout); \
} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT(a, n) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        printf("%f ", *(a+zzzzzzzz)); \
    } \
    printf("\n"); \
    fflush(stdout); \
} while(0)
#define DEBUG_PRINT_UCHAR_ARRAY_SKIP(a, n, skip) { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        printf("%u ", *(a+skip*zzzzzzzz)); \
    } \
    printf("\n"); \
    fflush(stdout); \
} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR_SKIP(a, n, skip) { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        printf("%u ", (unsigned char)*(a+skip*zzzzzzzz)); \
    } \
    printf("\n"); \
    fflush(stdout); \
} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT_SKIP(a, n, skip) { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        printf("%f ", *(a+skip*zzzzzzzz)); \
    } \
    printf("\n"); \
    fflush(stdout); \
} while(0)
#define DEBUG_PRINT(format, ...) do { \
    printf(format, ##__VA_ARGS__); \
    fflush(stdout); \
} while(0)
#else
#define DEBUG_PRINT_UCHAR_ARRAY(a, n) do {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR(a, n) do {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT(a, n) do {} while(0)
#define DEBUG_PRINT_UCHAR_ARRAY_SKIP(a, n, skip) do {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR_SKIP(a, n, skip) dp {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT_SKIP(a, n) do {} while(0)
#define DEBUG_PRINT(format, ...) do {} while(0)
#endif

#ifdef DEBUG_OUTPUT_F
#define DEBUG_PRINT_UCHAR_ARRAY_F(f, a, n) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        fprintf(f, "%u ", *(a+zzzzzzzz)); \
    } \
    fprintf(f, "\n"); \
    fflush(f); \
} while(0)  
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR_F(f, a, n) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        fprintf(f, "%u ", (unsigned char)*(a+zzzzzzzz)); \
    } \
    fprintf(f, "\n"); \
    fflush(f); \
} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT_F(f, a, n) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        fprintf(f, "%f ", *(a+zzzzzzzz)); \
    } \
    fprintf(f, "\n"); \
    fflush(f); \
} while(0)
#define DEBUG_PRINT_UCHAR_ARRAY_SKIP_F(f, a, n, skip) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        fprintf(f, "%u ", *(a+skip*zzzzzzzz)); \
    } \
    fprintf(f, "\n"); \
    fflush(f); \
} while(0)  
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR_SKIP_F(f, a, n, skip) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        fprintf(f, "%u ", (unsigned char)*(a+skip*zzzzzzzz)); \
    } \
    fprintf(f, "\n"); \
    fflush(f); \
} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT_SKIP_F(f, a, n, skip) do { \
    for(int zzzzzzzz=0; zzzzzzzz<n; zzzzzzzz++) { \
        fprintf(f, "%f ", *(a+skip*zzzzzzzz)); \
    } \
    fprintf(f, "\n"); \
    fflush(f); \
} while(0)
#define DEBUG_PRINT_F(f, ...) do { \
    fprintf(f,##__VA_ARGS__); \
    fflush(f); \
} while(0)
#else
#define DEBUG_PRINT_UCHAR_ARRAY_F(f, a, n) do {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR_F(f, a, n) do {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT_F(f, a, n) do {} while(0)
#define DEBUG_PRINT_UCHAR_ARRAY_SKIP_F(f, a, n, skip) do {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_UCHAR_SKIP_F(f, a, n, skip) dp {} while(0)
#define DEBUG_PRINT_FLOAT_ARRAY_AS_FLOAT_SKIP_F(f, a, n, skip) dp {} while(0)
#define DEBUG_PRINT_F(f, ...) do {} while(0)
#endif

#endif // INCLUDED_FECAPI_DEBUG_MACROS_H
