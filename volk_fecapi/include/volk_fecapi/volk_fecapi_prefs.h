#ifndef INCLUDED_VOLK_PREFS_H
#define INCLUDED_VOLK_PREFS_H

#include <volk_fecapi/volk_fecapi_common.h>
#include <stdlib.h>

__VOLK_DECL_BEGIN

typedef struct volk_fecapi_arch_pref
{
    char name[128];   //name of the kernel
    char impl_a[128]; //best aligned impl
    char impl_u[128]; //best unaligned impl
} volk_fecapi_arch_pref_t;

////////////////////////////////////////////////////////////////////////
// get path to volk_fecapi_config profiling info
////////////////////////////////////////////////////////////////////////
VOLK_API void volk_fecapi_get_config_path(char *);

////////////////////////////////////////////////////////////////////////
// load prefs into global prefs struct
////////////////////////////////////////////////////////////////////////
VOLK_API size_t volk_fecapi_load_preferences(volk_fecapi_arch_pref_t **);

__VOLK_DECL_END

#endif //INCLUDED_VOLK_PREFS_H
