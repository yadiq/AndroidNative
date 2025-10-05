//
// 获取app包名、签名、应用属性
//

#include <malloc.h>

#include "ContextUtil.h"
#include "LogUtil.h"
#include "../utils/Util.h"

// http://blog.csdn.net/gaoshouxiaodi/article/details/37821659
jobject getApplication(JNIEnv *env) {
    //ActivityThread在源码的目录是在framework下： /frameworks/base/core/java/android/app/
    //在app无法直接访问，但是可以通过反射获取
    jclass localClass = env->FindClass("android/app/ActivityThread");
    if (localClass != NULL) {
        //获取当前应用
        jmethodID getapplication = env->GetStaticMethodID(localClass, "currentApplication","()Landroid/app/Application;");
        if (getapplication != NULL) {
            jobject application = env->CallStaticObjectMethod(localClass, getapplication);
            return application;
        }
        return NULL;
    }
    return NULL;
}

/**
 * 获取包名
 * @param env
 * @return
 */
string getPackageName(JNIEnv *env) {
    jobject context = getApplication(env);
    if (context == NULL) {
        LOGE("getPackageName: not found context");
        return NULL;//getDefaultSign();
    }
    jclass activity = env->GetObjectClass(context);
    // 得到 getPackageManager 方法的 ID
    jmethodID methodID_func = env->GetMethodID(activity, "getPackageManager","()Landroid/content/pm/PackageManager;");
    // 获得PackageManager对象
    jobject packageManager = env->CallObjectMethod(context, methodID_func);
    jclass packageManagerclass = env->GetObjectClass(packageManager);
    //得到 getPackageName 方法的 ID
    jmethodID methodID_pack = env->GetMethodID(activity, "getPackageName", "()Ljava/lang/String;");
    //获取包名
    jstring name_str = static_cast<jstring>(env->CallObjectMethod(context, methodID_pack));
    string packageName = JniUtil::jstringToString(env, name_str);
    return packageName;
}

/**
 * 获取签名
 * @param env
 * @return
 */
string getSign(JNIEnv *env) {
    jobject context = getApplication(env);
    if (context == NULL) {
        LOGE("getSign: not found context");
        return NULL;//getDefaultSign();
    }
    jclass activity = env->GetObjectClass(context);
    // 得到 getPackageManager 方法的 ID
    jmethodID methodID_func = env->GetMethodID(activity, "getPackageManager","()Landroid/content/pm/PackageManager;");
    // 获得PackageManager对象
    jobject packageManager = env->CallObjectMethod(context, methodID_func);
    jclass packageManagerclass = env->GetObjectClass(packageManager);
    //得到 getPackageName 方法的 ID
    jmethodID methodID_pack = env->GetMethodID(activity, "getPackageName", "()Ljava/lang/String;");
    //获取包名
    jstring name_str = static_cast<jstring>(env->CallObjectMethod(context, methodID_pack));
    // 得到 getPackageInfo 方法的 ID
    jmethodID methodID_pm = env->GetMethodID(packageManagerclass, "getPackageInfo","(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    // 获得应用包的信息
    jobject package_info = env->CallObjectMethod(packageManager, methodID_pm, name_str, 64);
    // 获得 PackageInfo 类
    jclass package_infoclass = env->GetObjectClass(package_info);
    // 获得签名数组属性的 ID
    jfieldID fieldID_signatures = env->GetFieldID(package_infoclass, "signatures","[Landroid/content/pm/Signature;");
    // 得到签名数组，待修改
    jobject signatur = env->GetObjectField(package_info, fieldID_signatures);
    jobjectArray signatures = reinterpret_cast<jobjectArray>(signatur);
    // 得到签名
    jobject signature = env->GetObjectArrayElement(signatures, 0);
    // 获得 Signature 类，待修改
    jclass signature_clazz = env->GetObjectClass(signature);
    // 获取toByteArray方法ID
    jmethodID signature_method_toByteArray = env->GetMethodID(signature_clazz, "toByteArray","()[B");
    jobject signatureBytes = env->CallObjectMethod(signature, signature_method_toByteArray);
    // 获取InputStream对象
    jclass inputStreamClass = env->FindClass("java/io/ByteArrayInputStream");
    jobject inputStreamObj = env->NewObject(
            inputStreamClass,
            env->GetMethodID(inputStreamClass, "<init>", "([B)V"),
            signatureBytes
    );
    // 获取CertificateFactory对象
    jclass certificateClass = env->FindClass("java/security/cert/CertificateFactory");
    jmethodID certificateClass_getInstance = env->GetStaticMethodID(certificateClass, "getInstance",
                                                                    "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jobject certificateFactoryObj = env->CallStaticObjectMethod(certificateClass,
                                                                certificateClass_getInstance,
                                                                env->NewStringUTF("X509"));

    // 生成X509Certificate对象
    jmethodID certificateFactoryClass_method_generateCertificate = env->GetMethodID(
            certificateClass, "generateCertificate",
            "(Ljava/io/InputStream;)Ljava/security/cert/Certificate;");
    jobject x509CertificateObj = env->CallObjectMethod(certificateFactoryObj,
                                                       certificateFactoryClass_method_generateCertificate,
                                                       inputStreamObj);
    // 获取X509Certificate的c.getEncoded数据
    jmethodID X509Certificate_method_getEncoded = env->GetMethodID(
            env->FindClass("java/security/cert/Certificate"),
            "getEncoded", "()[B");
    jobject x509CertificateObj_encoded = env->CallObjectMethod(x509CertificateObj,
                                                               X509Certificate_method_getEncoded);
    // 生成MessageDigest
    jclass MessageDigestClass = env->FindClass("java/security/MessageDigest");
    jmethodID MessageDigestClass_getInstance = env->GetStaticMethodID(MessageDigestClass, "getInstance",
                                                                      "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jobject MessageDigestObj = env->CallStaticObjectMethod(MessageDigestClass, MessageDigestClass_getInstance,
                                                           env->NewStringUTF("MD5"));//签名类型 MD5 SHA1 SHA256

    // 获取MessageDigestObj.digest
    jmethodID MessageDigestClass_method_digest = env->GetMethodID(MessageDigestClass, "digest",
                                                                  "([B)[B");
    jobject publicKey = env->CallObjectMethod(MessageDigestObj, MessageDigestClass_method_digest,
                                              x509CertificateObj_encoded);
    jbyteArray publicKeyArr = reinterpret_cast<jbyteArray>(publicKey);
    //LOGI("getSign convert to 0x");
    //转为bytes
    int length = env->GetArrayLength(publicKeyArr);
    jbyte *bytes = env->GetByteArrayElements(publicKeyArr, 0);
    //转换为16进制
    string signHex = Util::bytesToHex(reinterpret_cast<char *>(bytes), length);
    //释放内存
    env->ReleaseByteArrayElements(publicKeyArr, bytes, 0);
    //LOGI("getSign: %s", hexStr);
    return signHex;
}

/**
 * 获取应用的属性
 * @param env
 * @return
 */
int getFlags(JNIEnv *env) {
    jobject application = getApplication(env);
    if (application == NULL) {
        LOGE("getFlags: not found context");
        return 0;//getDefaultSign();
    }
    jclass jApplication = env->GetObjectClass(application);
    jmethodID getApplicationInfo = env->GetMethodID(jApplication, "getApplicationInfo","()Landroid/content/pm/ApplicationInfo;");
    jobject applicationInfo = env->CallObjectMethod(application, getApplicationInfo);
    jclass jApplicationInfo = env->GetObjectClass(applicationInfo);
    jfieldID getFlags = env->GetFieldID(jApplicationInfo, "flags", "I");
    int flags = env->GetIntField(applicationInfo, getFlags);
    //释放
    env->DeleteLocalRef(jApplicationInfo);
    env->DeleteLocalRef(jApplication);
    return flags;
}