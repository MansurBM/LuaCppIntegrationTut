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

#include <string>
#include <sol.hpp>
class ScriptObject
{
public:
  ScriptObject();
  template <typename...Args>
  explicit ScriptObject(sol::state *pLuaState, const std::string &luaClassName, const Args&...args);
  ScriptObject(const ScriptObject&other) = delete;
  ScriptObject& operator=(const ScriptObject&other) = delete;
  ~ScriptObject();
  template <typename...Args>
  bool Init(sol::state *pLuaState, const std::string &scriptName, const Args&...args);
  bool HasFunction(const std::string &fnName);
  const std::string& GetScriptVarName()const;
  const std::string& GetLuaClassName()const;
  template <typename RetType = void, typename...Args>
  RetType CallFunction(const std::string &fnName, const Args&...args);
  template <typename RetType = void, typename...Args>
  RetType UnsafeCallFunction(const std::string &fnName, const Args&...args);
private:
  template <typename T, typename...Args>
  static std::string convertArgsToLuaArgs(const T& t, const Args&...args);
  template <typename T>
  static std::string convertArgsToLuaArgs(const T& t);
  static std::string convertArgsToLuaArgs(const std::string &str);
  static std::string convertArgsToLuaArgs(const char* str);
  static std::string convertArgsToLuaArgs();
private:
  std::string m_luaClassName;
  std::string m_scriptVarName;
  sol::table m_luaObjectData;
  sol::state *m_pLuaState;
  bool m_initialized;
};
template <typename...Args>
ScriptObject::ScriptObject(sol::state *pLuaState, const std::string &luaClassName, const Args&...args)
  :
  m_pLuaState(nullptr),
  m_initialized(false)
{
  Init(pLuaState, luaClassName, args...);
}
template <typename...Args>
bool ScriptObject::Init(sol::state *pLuaState, const std::string &luaClassName, const Args&...args)
{
  if (!pLuaState) return false;
  m_pLuaState = pLuaState;
  m_initialized = true;
  m_luaClassName = luaClassName;
  static std::size_t scriptID = 0;
  m_scriptVarName = m_luaClassName + "_" + std::to_string(scriptID++).c_str();
  bool isValidCreation = true;
  std::string script = m_scriptVarName + " = " + m_luaClassName + ":new(" + convertArgsToLuaArgs(args...) + ")";
  m_pLuaState->script(script,
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
template <typename T, typename...Args>
std::string ScriptObject::convertArgsToLuaArgs(const T& t, const Args&...args)
{
  return convertArgsToLuaArgs(t) + "," + convertArgsToLuaArgs(args...);
}
template <typename T>
std::string ScriptObject::convertArgsToLuaArgs(const T& t)
{
  return std::to_string(t);
}
template <typename RetType, typename...Args>
RetType ScriptObject::CallFunction(const std::string &fnName, const Args&...args)
{
  if (m_initialized && m_pLuaState)
  {
    if (HasFunction(fnName))
      return UnsafeCallFunction<RetType, Args...>(fnName, args...);
  }
}
template <typename RetType, typename...Args>
RetType ScriptObject::UnsafeCallFunction(const std::string &fnName, const Args&...args)
{
  std::string scriptStr = std::string("return ") + m_scriptVarName + ":" + fnName + "(" + convertArgsToLuaArgs(args...) + ")";
  return static_cast<RetType>(m_pLuaState->script(scriptStr));
}
template <typename T>
T ScriptObject::Get(const std::string& name) const
{
  return m_luaObjectData[name];
}
template <typename T>
bool ScriptObject::TryGet(const std::string& name, T* pValue) const
{
  bool valid = m_luaObjectData[name].valid();
  if (valid && pValue)
  {
    *pValue = m_luaObjectData[name];
  }
  return valid && pValue;
}
template <typename T>
void ScriptObject::Set(const std::string& name, const T& value)
{
  m_luaObjectData[name] = value;
}