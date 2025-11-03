#include <napi.h>
#include "StreamCommon.hpp"

extern class StreamServerCore;
extern class StreamClientCore;

using namespace Napi;

class StreamServerWrapper : public ObjectWrap<StreamServerWrapper> {
public:
    static Object Init(Napi::Env env, Object exports) {
        Function func = DefineClass(env, "StreamServer", {
            InstanceMethod("start", &StreamServerWrapper::Start),
            InstanceMethod("broadcast", &StreamServerWrapper::Broadcast)
        });
        exports.Set("StreamServer", func);
        return exports;
    }

    StreamServerWrapper(const CallbackInfo& info)
        : ObjectWrap(info) {
        int port = info[0].As<Number>().Int32Value();
        core = std::make_shared<StreamServerCore>(port);
    }

    void Start(const CallbackInfo& info) {
        core->start();
    }

    void Broadcast(const CallbackInfo& info) {
        std::string msg = info[0].As<String>().Utf8Value();
        core->broadcast(msg);
    }

private:
    std::shared_ptr<StreamServerCore> core;
};

class StreamClientWrapper : public ObjectWrap<StreamClientWrapper> {
public:
    static Object Init(Napi::Env env, Object exports) {
        Function func = DefineClass(env, "StreamClient", {
            InstanceMethod("send", &StreamClientWrapper::Send),
            InstanceMethod("startReceiving", &StreamClientWrapper::StartReceiving)
        });
        exports.Set("StreamClient", func);
        return exports;
    }

    StreamClientWrapper(const CallbackInfo& info)
        : ObjectWrap(info) {
        std::string host = info[0].As<String>().Utf8Value();
        int port = info[1].As<Number>().Int32Value();
        core = std::make_shared<StreamClientCore>(host, port);
    }

    void Send(const CallbackInfo& info) {
        std::string msg = info[0].As<String>().Utf8Value();
        core->send(msg);
    }

    void StartReceiving(const CallbackInfo& info) {
        core->startReceiving();
    }

private:
    std::shared_ptr<StreamClientCore> core;
};

Object InitAll(Napi::Env env, Object exports) {
    StreamServerWrapper::Init(env, exports);
    StreamClientWrapper::Init(env, exports);
    return exports;
}

NODE_API_MODULE(streamx, InitAll)
