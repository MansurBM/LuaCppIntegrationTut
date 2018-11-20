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

#include "ScriptObject.hpp"
#include "ConvertArgsToLuaArgs.hpp"
#include <iostream>
void test1()
{
  std::cout << "Value: " + convertArgsToLuaArgs(3, "test", 5.4) << std::endl;
}
void test2()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.do_file("scripts/testLuaFunction2.lua");
  int ret = state.do_string("return testLuaFunction2(1)");
  std::cout << "Return value: " + std::to_string(ret) << std::endl;
  sol::function testLuaFunction2 = state["testLuaFunction2"];
  ret = testLuaFunction2(2);
  std::cout << "Return value: " + std::to_string(ret) << std::endl;
}
void test3()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  std::string package_path = state["package"]["path"];
  state["package"]["path"] = (package_path + ";scripts/middleclass.lua").c_str();
  state.do_file("scripts/TestClass.lua");
  ScriptObject obj(&state, "TestClass2", 5, "test");
  int retVal = obj.CallFunction<int>("TestFunction", 3, 7);
  std::cout << "Return Value: " << retVal << std::endl;
  std::cout << "numValue: " << obj.Get<int>("numValue") << std::endl;
  std::cout << "strValue: " << obj.Get<std::string>("strValue") << std::endl;
}
int main()
{
  //Change value of testNum to change to the different test-cases
  int testNum = 1;
  switch (testNum)
  {
  case 1:
    test1();
    break;
  case 2:
    test2();
    break;
  case 3:
    test3();
    break;
  };
}