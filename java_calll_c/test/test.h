/*
 * jni.h
 *
 *  Created on: 2014-11-19
 *      Author: kevin
 */

#ifndef JNI_H_
#define JNI_H_

#include <jni.h>

typedef struct
{
	char *name;			// Java本地方法名称
	char *signature;	// Java本地方法签名
	void *fnPtr;		// C函数指针
} gJNINativeMethod;

// 该方法在JVM加载完JNI动态库时紧接着被调用，所以可以在这个函数里进行动态注册
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved);

jint (JNICALL *RegisterNatives) (JNIEnv *env, jclass clazz, const JNINativeMethod *method, jint nMethods);

#endif /* JNI_H_ */
