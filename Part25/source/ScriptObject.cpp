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
ScriptObject::ScriptObject()
  :
  m_pLuaState(nullptr),
  m_initialized(false)
{
}
ScriptObject::~ScriptObject()
{
  if (m_initialized)
  {
    m_pLuaState->script(m_scriptVarName + " = nil");
  }
}
bool ScriptObject::HasFunction(const std::string &fnName)
{
  return m_initialized && (m_luaObjectData[fnName].valid());
}
const std::string& ScriptObject::GetScriptVarName()const
{
  return m_scriptVarName;
}
const std::string& ScriptObject::GetLuaClassName()const
{
  return m_luaClassName;
}
std::string ScriptObject::convertArgsToLuaArgs()
{
  return "";
}
std::string ScriptObject::convertArgsToLuaArgs(const std::string &str)
{
  return "\'" + str + "\'";
}
std::string ScriptObject::convertArgsToLuaArgs(const char *str)
{
  return convertArgsToLuaArgs(std::string(str));
}