//
// Created by Deilson on 13/06/2019.
//

#include "converter.h"
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_com_d_1peres_shortbite_ShortBite_byte_1short(
        JNIEnv* env, jclass cls, jbyteArray jbytes, jshortArray jshorts)
{
    // the short array must have at-least half the size of the byte array
    jint bytes_len = env->GetArrayLength(jbytes);
    jint shorts_len = env->GetArrayLength(jshorts);

    int8_t *bytes = env->GetByteArrayElements(jbytes, JNI_FALSE);
    short *shorts = env->GetShortArrayElements(jshorts, JNI_FALSE);

    if(shorts_len < (bytes_len / 2))
    {
        // array size too small
        loge("Array size too small");
        return -1;
    }

    // convert
    logi("Starting");
    for (int i = 0; i < bytes_len / 2; i++)
    {
        // for each short index...
        // index    |      0      |      1      |      2      |      3      |
        // byt arr  | 0xff | 0x00 | 0xab | 0xcd | 0x7f | 0x71 | 0xf0 | 0xda |
        // sht arr  |    0xff00   |    0xabcd   |    0x7f71   |    0xf0da   |
        shorts[i] = (bytes[i * 2] << 8) | (0x00ff & bytes[i * 2 + 1]);
    }

    env->ReleaseByteArrayElements(jbytes, bytes, 0);
    env->ReleaseShortArrayElements(jshorts, shorts, 0);

    return 0;
}

JNIEXPORT jint JNICALL Java_com_d_1peres_shortbite_ShortBite_short_1byte(
        JNIEnv* env, jclass cls, jshortArray jshorts, jbyteArray jbytes)
{
    jshort* shorts = env->GetShortArrayElements(jshorts, JNI_FALSE);
    jbyte*  bytes  = env->GetByteArrayElements(jbytes, JNI_FALSE);

    jint shorts_len = env->GetArrayLength(jshorts);
    jint bytes_len = env->GetArrayLength(jbytes);

    // the destination byte array must be at least double the size of the short array
    if (bytes_len < shorts_len * 2)
    {
        loge("Array size too small");
        return CONVERSION_FAILURE;
    }

    for (int i = 0; i < bytes_len; i++)
    {
        // for each short index...
        // index    |      0      |      1      |      2      |      3      |
        // sht arr  |    0xff00   |    0xabcd   |    0x7f71   |    0xf0da   |
        // byt arr  | 0xff | 0x00 | 0xab | 0xcd | 0x7f | 0x71 | 0xf0 | 0xda |
        //              |     |-> *
        //              |-> 0xff >> 8
        // Insert the bytes one by one

        // MSB
        bytes[i * 2]     = static_cast<jbyte>(shorts[i] >> 8);
        // LSB
        bytes[i * 2 + 1] = static_cast<jbyte>(shorts[i] & 0xffff);
    }

    env->ReleaseByteArrayElements(jbytes, bytes, 0);
    env->ReleaseShortArrayElements(jshorts, shorts, 0);

    return CONVERSION_SUCCESS;
}

#ifdef __cplusplus
};
#endif

#pragma clang diagnostic pop