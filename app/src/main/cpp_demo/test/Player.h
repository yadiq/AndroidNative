//
// Created by gyd on 2026/2/25.
//

#ifndef ANDROIDNATIVE_PLAYER_H
#define ANDROIDNATIVE_PLAYER_H

#include <android/native_window_jni.h>
#include <thread>

class Player {
public:
    void start(const char *url);
    void stop();
    void setSurface(JNIEnv *env, jobject surface);

private:
    ANativeWindow *window = nullptr;
    std::thread decodeThread;
    bool isPlaying = false;
};


#endif //ANDROIDNATIVE_PLAYER_H
