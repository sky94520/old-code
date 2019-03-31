#include <stdio.h>

#include "HelloNative.h"

JNIEXPORT void JNICALL Java_HelloNative_greeting(JNIEnv *, jclass)
{
	printf("Hello Native World\n");
}