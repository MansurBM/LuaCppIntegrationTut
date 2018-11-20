//MIT License
//
//Copyright (c) 2018 Mansur BM
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <sol.hpp>
#include "ScriptObject.hpp"
#include "CppObject.hpp"

void test1()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.new_usertype<CppObject>("CppObject",
    "TestFunction1", &CppObject::TestFunction1
    );
  state.do_string("cppObj = CppObject:new() cppObj:TestFunction1()");
}
void test2()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  std::string package_path = state["package"]["path"];
  state["package"]["path"] = (package_path + ";scripts/middleclass.lua").c_str();
  state.do_file("scripts/TestClass.lua");
  state.do_string("testObject = TestClass:new() testObject.TestFunctionCall()");
}
void test3()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  std::string package_path = state["package"]["path"];
  state["package"]["path"] = (package_path + ";scripts/middleclass.lua").c_str();
  state.do_file("scripts/TestClass.lua");
  ScriptObject obj(&state, "TestClass");
  obj.CallFunction("TestFunctionCall");
}
int main()
{
  //Change value of testNum to change to the different test-cases
  int testNum = 1;
  switch (testNum)
  {
  case 1:
    test3();
    break;
  case 2:
    test2();
    break;
  case 3:
    test3();
    break;
  };
}