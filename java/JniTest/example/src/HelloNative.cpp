#include "HelloNative.h"
JNIEXPORT void JNICALL Java_HelloNativeTest_greeting
  (JNIEnv *, jclass)
{
	printf("Hello jni");
}
