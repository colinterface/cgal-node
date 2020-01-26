#include <napi.h>
#include <iostream>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;

Napi::String Orientation(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 6)
  {
    Napi::TypeError::New(
        env,
        "Expected 6 numbers for 3 points in 2 dimensions")
        .ThrowAsJavaScriptException();
    return Napi::String::New(env, "ERROR");
  }

  for (int i = 0; i < info.Length(); i += 1)
  {
    if (!info[i].IsNumber())
    {
      Napi::TypeError::New(
          env,
          "Expected 6 numbers for 3 points in 2 dimensions")
          .ThrowAsJavaScriptException();
      return Napi::String::New(env, "ERROR");
    }
  }

  Point_2 a(
      info[0].As<Napi::Number>().DoubleValue(),
      info[1].As<Napi::Number>().DoubleValue());

  Point_2 b(
      info[2].As<Napi::Number>().DoubleValue(),
      info[3].As<Napi::Number>().DoubleValue());

  Point_2 c(
      info[4].As<Napi::Number>().DoubleValue(),
      info[5].As<Napi::Number>().DoubleValue());

  switch (CGAL::orientation(a, b, c))
  {
  case CGAL::COLLINEAR:
    return Napi::String::New(env, "COLLINEAR");
  case CGAL::LEFT_TURN:
    return Napi::String::New(env, "LEFT_TURN");
  case CGAL::RIGHT_TURN:
    return Napi::String::New(env, "RIGHT_TURN");
  }
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
      Napi::String::New(env, "orientation"),
      Napi::Function::New(env, Orientation));
  return exports;
}

NODE_API_MODULE(hello, Init)
