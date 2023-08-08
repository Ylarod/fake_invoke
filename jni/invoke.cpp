
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>


int main(int argc, char** argv){
    if (argc != 2) {
        printf("invoke xxx.so\n");
    }

    void * handle = dlopen(argv[1], RTLD_NOW);
    if (!handle){
        printf("dlopen failed, error %s", dlerror());
        return 0;
    }

    void * jni_load = dlsym(handle, "JNI_OnLoad");
    if (jni_load == NULL){
        printf("dlsym failed");
        return 0;
    }

    printf("begin to invoke jni_onload\n");
    ((void *(*)(unsigned int, unsigned int))jni_load)(0x12345678, 0x123456);
    printf("after jni_onload, exit\n");

    return 0;
}