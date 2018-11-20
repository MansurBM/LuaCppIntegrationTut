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

std::size_t ScriptObject::ms_scriptNum = 0;

ScriptObject::ScriptObject(sol::state *pLuaState, const std::string &luaClassName)
  :
  m_pLuaState(nullptr),
  m_initialized(false)
{
  Init(pLuaState, luaClassName);
}
ScriptObject::~ScriptObject()
{
  if (m_pLuaState)
    m_pLuaState->script(m_scriptVarName + " = nil");
}
bool ScriptObject::Init(sol::state *pLuaState, const std::string &luaClassName)
{
  m_pLuaState = pLuaState;
  m_initialized = true;
  m_luaClassName = luaClassName;
  m_scriptVarName = luaClassName + "_" + std::to_string(ms_scriptNum++);
  bool isValidCreation = true;
  std::string script = m_scriptVarName + " = " + m_luaClassName + ":new()";
  m_pLuaState->script(script.c_str(),
    [&isValidCreation](lua_State* state, sol::protected_function_result res) { isValidCreation = false; return res; });
  if (isValidCreation)
  {
    m_luaObjectData = (*m_pLuaState)[m_scriptVarName];
  }
  bool success = isValidCreation && m_luaObjectData.valid();
  if (!success)
  {
    m_initialized = false;
    m_luaClassName = "";
    m_scriptVarName = "";
    m_luaObjectData = sol::userdata();
  }
  return success;
}
bool ScriptObject::HasFunction(const std::string &fnName)
{
  return (m_luaObjectData[fnName].valid());
}
void ScriptObject::CallFunction(const std::string &fnName)
{
  if (m_pLuaState)
    m_pLuaState->script(m_scriptVarName + ":" + fnName + "()");
}