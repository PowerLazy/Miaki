
#include <stdio.h>
#include <stdarg.h>

#include <vitasdk.h>
#include <taihen.h>

static int hook = -1;
static tai_hook_ref_t ref_hook;

static int returntrue() {
    return 1;
}	
void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
        
       hook = taiHookFunctionExportForKernel(KERNEL_PID,
		&ref_hook, 
		"SceVshBridge",
		0x35C5ACD4, //SceVshBridge
		0x641890D8, //vshSblSsIsDevelopmentMode
		returntrue);
       
       
       
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	if (hook >= 0) taiHookReleaseForKernel(hook, ref_hook);   
	return SCE_KERNEL_STOP_SUCCESS;
}
