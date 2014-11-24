/*
 * =====================================================================================
 *
 *       Filename:  call.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/20/2014 11:45:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kevin (###), kevin101@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <jni.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	jint (*createJavaVM) (JavaVM **, void **, void *);

	void *libHandle;

	JavaVMOption options[3];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;

	jint status;
	jclass cls;
	jobject obj;
	jmethodID mid;

	jstring msg;
	char *tmp = NULL;

	options[0].optionString = "-Djava.compiler=NONE";
	options[1].optionString = "-Djava.class.path=.";//;/home/kevin/work/jni/c_call_java/Demo
	options[2].optionString = "-verbose:NONE";

	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 3;
	vm_args.options = options;

	vm_args.ignoreUnrecognized = JNI_TRUE;

	libHandle = dlopen("/home/intel/work/jdk1.6.0_38/jre/lib/amd64/server/libjvm.so", RTLD_NOW);
	if (libHandle == NULL){
		printf("dlopen: %s\n", dlerror());
		return JNI_FALSE;
	}

	(void) dlerror();

	// status = JNI_GetDefaultJavaVMInitArgs(&vm_args);

	if (status == JNI_ERR)
	{
		return JNI_FALSE;
	}

	printf("--1-- %d\n", status);
	// 初始化虚拟机
	*(void **) (&createJavaVM) = dlsym(libHandle, "JNI_CreateJavaVM");
	status = (*createJavaVM) (&jvm, (void **)&env, &vm_args);

	printf("--2-- %d\n", status);
	if (status != JNI_ERR)
	{
		// 获取类
		cls = (*env)->FindClass(env, "Demo");
		if (cls == NULL)
		{
			return JNI_FALSE;
		}

		// 获取对象
		obj = (*env)->AllocObject(env, cls);

///////////// append //////////////////
		// 获取类的方法
		mid = (*env)->GetMethodID(env, cls, "append", "(Ljava/lang/String;I)Ljava/lang/String;");

		jstring str = (*env)->NewStringUTF(env, "Num: ");

		// 调用对象
		msg = (jstring) (*env)->CallObjectMethod(env, obj, mid, str, 121);
		tmp = (*env)->GetStringUTFChars(env, msg, 0);
		printf("%s\n", tmp);

/////////////// 修改属性 ///////////////////
		// 获取Java的构造方法
		mid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
		jstring strinit = (*env)->NewStringUTF(env, "Hello");
		jvalue val[1];
		val[0].l = strinit;
	
		// 创建类的对象
		jobject obj = (*env)->NewObjectA(env, cls, mid, val);
		if (obj == NULL)
		{
			printf("Create object failed!\n");
		}

		jfieldID fid = (*env)->GetFieldID(env, cls, "msg", "Ljava/lang/String;");
		if (fid == NULL)
		{
			return JNI_FALSE;
		}

		const char *msg_t = "yxyxy";
		jstring arg_t = (*env)->NewStringUTF(env, msg_t);
		(*env)->SetObjectField(env, obj, fid, arg_t);		// 修改属性

///////////////// getMessage /////////////////	
		mid = (*env)->GetMethodID(env, cls, "getMessage", "()Ljava/lang/String;");
		msg = (jstring) (*env)->CallObjectMethod(env, obj, mid);
		
		tmp = (*env)->GetStringUTFChars(env, msg, 0);
		printf("%s\n", tmp);

//////////////////// setCounts //////////////
		mid = (*env)->GetMethodID(env, cls, "setCounts", "([I)V");

		int arr_size = 5;
		jint sSession[5] = {1, 2, 3, 4, 5};
		jintArray sJSession;
		sJSession = (*env)->NewIntArray(env, arr_size);
		(*env)->SetIntArrayRegion(env, sJSession, 0, arr_size, sSession);
		// jint *nSession = (jint *) (*env)->GetPrimitiveArrayCritival(env, jSession, NULL);
		(*env)->CallVoidMethod(env, obj, mid, sJSession);
		
		(*env)->DeleteLocalRef(env, sJSession);
		printf("--------------------\n");

/////////////////// getCounts ////////////////
		mid = (*env)->GetMethodID(env, cls, "getCounts", "()[I");

		// jint gSession[5];
		jintArray gJSession;
		gJSession = (*env)->CallObjectMethod(env, obj, mid);
		assert(gJSession);
		// (*env)->GetIntArrayRegion(env, gJSession, 0, arr_size, gSession);
		jsize len = (*env)->GetArrayLength(env, gJSession);
		assert(len);

		printf("%d\n", len);
		(*env)->DeleteLocalRef(env, gJSession);

//////////////////////////////////////////////
		// 释放资源
		(*env)->ReleaseStringUTFChars(env, msg, 0);
		(*jvm)->DestroyJavaVM(jvm);
		dlclose(libHandle);

		printf("Finished...\n");
	}
	else
		return -1;
}
