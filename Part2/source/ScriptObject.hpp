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

#pragma once
#include <string>
#include <sol.hpp>

class ScriptObject
{
public:
  ScriptObject() = default;
  explicit ScriptObject(sol::state *pLuaState, const std::string &luaClassName);
  ScriptObject(const ScriptObject&other) = delete;
  ScriptObject& operator=(const ScriptObject&other) = delete;
  ~ScriptObject();
  bool Init(sol::state *pLuaState, const std::string &luaClassName);
  bool HasFunction(const std::string &fnName);
  void CallFunction(const std::string &fnName);
private:
  std::string m_luaClassName;
  std::string m_scriptVarName;
  sol::table m_luaObjectData;
  sol::state *m_pLuaState;
  static std::size_t ms_scriptNum;
  bool m_initialized;
};