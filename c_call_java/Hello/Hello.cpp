/*
 * =====================================================================================
 *
 *       Filename:  Hello.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/20/2014 02:32:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kevin (###), kevin101@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <jni.h>
#include <stdio.h>
#include "Hello.h"

JNIEXPORT void JNICALL	Java_Hello_print(JNIEnv *env, jobject obj)
{
	printf("Hello Everyday!\n");
}
