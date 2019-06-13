//
// Created by Deilson on 13/06/2019.
//

#ifndef SHORTBITE_CONVERTER_H
#define SHORTBITE_CONVERTER_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONVERSION_SUCCESS 1
#define CONVERSION_FAILURE -1

JNIEXPORT jint JNICALL Java_com_d_1peres_shortbite_ShortBite_byte_1short(
        JNIEnv* , jclass, jbyteArray, jshortArray);
JNIEXPORT jint JNICALL Java_com_d_1peres_shortbite_ShortBite_short_1byte(
        JNIEnv *, jclass, jshortArray, jbyteArray);

#ifdef __cplusplus
};
#endif

#endif //SHORTBITE_CONVERTER_H
