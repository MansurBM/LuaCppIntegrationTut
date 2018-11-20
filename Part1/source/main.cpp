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
#include <iostream>
void test1()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.do_string("print(\'Hello World!\')");
}
void test2()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.do_file("scripts/HelloWorld.lua");
}
void test3()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state["luaNum"] = 3;
  state.do_string("print(\'printing in Lua: \' .. luaNum)");
  int luaNumValue = state["luaNum"];
  std::cout << "printing in c++: " << luaNumValue << '\n';
}
int testCppFunction(int number)
{
  return number;
}
void test4()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.set_function("testCppFunction", testCppFunction);
  state.do_string("num = testCppFunction(1); print(\"Called testCppFunction with return value(\" .. num .. \")!\")");
}
void test5()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.do_file("scripts/testLuaFunction1.lua");
}
void test6()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.do_file("scripts/testLuaFunction2.lua");
  state.do_string("testLuaFunction2(1)");
}
void test7()
{
  sol::state state;
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.do_file("scripts/testLuaFunction2.lua");
  sol::function testLuaFunction2 = state["testLuaFunction2"];
  testLuaFunction2(2);
}
void test8()
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
int main()
{
  //Change value of testNum to change to the different test-cases
  int testNum = 1;
  switch(testNum)
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
  case 4:
    test4();
    break;
  case 5:
    test5();
    break;
  case 6:
    test6();
    break;
  case 7:
    test7();
    break;
  case 8:
    test8();
    break;
  };
}