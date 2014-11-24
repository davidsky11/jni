/*
 * test.c
 *
 *  Created on: 2014-11-19
 *      Author: kevin
 */

#include <stdio.h>
#include <string.h>
#include <jni.h>
#include "test.h"

jstring native_function(JNIEnv *env, jclass cls, jstring msg);

// 定义Java本地方法与JNI动态库中方法的映射关系
static JNINativeMethod gMethods[] = {
		{"nativeFunc", "(Ljava/lang/String;)Ljava/lang/String;", (void *)native_function}
};

// 注册本地方法
static int register_native_methods(JNIEnv *env, const char *clsname, const JNINativeMethod *gMethods, int nums)
{
	jclass clazz = (*env)->FindClass(env, clsname);
	if (NULL == clazz)
		return JNI_FALSE;
	if ((*env)->RegisterNatives(env, clazz, gMethods, nums) < 0)
		return JNI_FALSE;
	return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
	JNIEnv *env = NULL;
	jint result = -1;

	// 获得JNIEnv
	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_4) != JNI_OK)
		return JNI_FALSE;

	// 注册本地方法
	if (register_native_methods(env, "test", gMethods, sizeof(gMethods)/sizeof(gMethods[0])) != JNI_TRUE)
		return JNI_FALSE;

	result = JNI_VERSION_1_4;
	return result;
}

// 自定义方法，将msg加上"(Solved)"并返回
jstring native_function(JNIEnv *env, jclass cls, jstring msg)
{
	const char *cmsg;
	char cres[1024];
	jstring res;

	cmsg = (*env)->GetStringUTFChars(env, msg, JNI_FALSE);

	memset(cres, '\0', 1024);
	strcat(cres, cmsg);
	strcat(cres, " (Solved)");
	res = (*env)->NewStringUTF(env, cres);

	(*env)->ReleaseStringUTFChars(env, msg, cmsg);

	return res;
}

int main()
{
	return 0;
}
