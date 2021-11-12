#include <Windows.h>
#include <node.h>

namespace hello_world
{

  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void Hello(const FunctionCallbackInfo<Value> &args)
  {
    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Hello, World!").ToLocalChecked());
  }

  void ComputerName(const FunctionCallbackInfo<Value> &args)
  {
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    auto size = static_cast<DWORD>(std::size(buffer));
    auto *result = (GetComputerNameA(buffer, &size) ? buffer : "Error");

    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, result).ToLocalChecked());
  }

  void Initialize(Local<Object> exports)
  {
    NODE_SET_METHOD(exports, "hello", Hello);
    NODE_SET_METHOD(exports, "computerName", ComputerName);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}