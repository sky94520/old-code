#include "HelloNative.h"
#include <stdio.h>
#include <string.h>

JNIEXPORT void JNICALL Java_HelloNative_greeting(JNIEnv * env, jclass cl)
{
	printf("Hello Native World\n");
}

JNIEXPORT jint JNICALL Java_HelloNative_print(JNIEnv * env, jclass cl, jint width, jint precision, jdouble x)
{
	char fmt[30];
	int ret = JNI_FALSE;

	memset(fmt, '\0', sizeof(fmt));
	//"%width.precision f"
	sprintf(fmt, "%%%d.%df", width, precision);
	ret = printf(fmt, x);

	fflush(stdout);
	return ret;
}
