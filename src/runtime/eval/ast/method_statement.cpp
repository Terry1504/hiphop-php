/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/
#include <runtime/eval/ast/expression.h>
#include <runtime/eval/ast/method_statement.h>
#include <runtime/eval/ast/statement_list_statement.h>
#include <runtime/eval/runtime/variable_environment.h>
#include <runtime/eval/ast/class_statement.h>
#include <runtime/eval/runtime/eval_state.h>
#include <runtime/eval/ast/function_call_expression.h>

namespace HPHP {
namespace Eval {
using namespace std;
///////////////////////////////////////////////////////////////////////////////

MethodStatement::MethodStatement(STATEMENT_ARGS, const string &name,
                                 const ClassStatement *cls, int modifiers,
                                 const string &doc)
  : FunctionStatement(STATEMENT_PASS, name, doc), m_class(cls),
    m_modifiers(modifiers),
    m_fullName(StringData::GetStaticString(
               string(cls->name().c_str()) + "::" + name)) {
  if ((m_modifiers & (ClassStatement::Public | ClassStatement::Protected |
                      ClassStatement::Private)) == 0) {
    m_modifiers |= ClassStatement::Public;
  }
  m_callInfo.m_invoker = (void*)MethInvoker;
  m_callInfo.m_invokerFewArgs = (void*)MethInvokerFewArgs;
  if (m_modifiers & ClassStatement::Static) {
    m_callInfo.m_flags |= CallInfo::StaticMethod;
  } else {
    m_callInfo.m_flags |= CallInfo::Method;
  }
  if (m_modifiers & ClassStatement::Protected) {
    m_callInfo.m_flags |= CallInfo::Protected;
  } else if (m_modifiers & ClassStatement::Private) {
    m_callInfo.m_flags |= CallInfo::Private;
  }
}

void MethodStatement::setPublic() {
  m_modifiers = ClassStatement::Public;
}

String MethodStatement::fullName() const {
  return m_fullName;
}

void MethodStatement::eval(VariableEnvironment &env) const {
  if (env.isGotoing()) return;
  ENTER_STMT;
  // register with reflection, invoke, etc.
}

LVariableTable *MethodStatement::getStaticVars(VariableEnvironment &env)
  const {
  return &RequestEvalState::getMethodStatics(this, env.currentClass());
}

Variant MethodStatement::invokeInstance(CObjRef obj, CArrRef params,
    bool check /* = true */) const {
  if (getModifiers() & ClassStatement::Static) {
    return invokeStatic(obj->o_getClassName(), params, check);
  }
  if (check) attemptAccess(FrameInjection::GetClassName(false));
  // The debug frame should have been pushed at ObjectMethodExpression
  DECLARE_THREAD_INFO_NOINIT
  MethScopeVariableEnvironment env(this);
  env.setCurrentObject(obj);
  String clsName(m_class->name());
  EvalFrameInjection fi(clsName, m_fullName->data(), env,
                        loc()->file, obj.get(), FrameInjection::ObjectMethod);
  if (m_ref) {
    return strongBind(invokeImpl(env, params));
  }
  return invokeImpl(env, params);
}

Variant MethodStatement::invokeInstanceFewArgs(CObjRef obj, int count,
  INVOKE_FEW_ARGS_IMPL_ARGS, bool check) const {
  if (getModifiers() & ClassStatement::Static) {
    return invokeStaticFewArgs(obj->o_getClassName(), count,
                               INVOKE_FEW_ARGS_PASS_ARGS, check);
  }
  if (check) attemptAccess(FrameInjection::GetClassName(false));
  // The debug frame should have been pushed at ObjectMethodExpression
  DECLARE_THREAD_INFO_NOINIT
  MethScopeVariableEnvironment env(this);
  env.setCurrentObject(obj);
  String clsName(m_class->name());
  EvalFrameInjection fi(clsName, m_fullName->data(), env,
                        loc()->file, obj.get(), FrameInjection::ObjectMethod);
  if (m_ref) {
    return strongBind(invokeImplFewArgs(env, count, INVOKE_FEW_ARGS_PASS_ARGS));
  }
  return invokeImplFewArgs(env, count, INVOKE_FEW_ARGS_PASS_ARGS);
}

Variant MethodStatement::
invokeInstanceDirect(CObjRef obj, VariableEnvironment &env,
                     const FunctionCallExpression *caller,
                     bool check /* = true */) const {
  if (getModifiers() & ClassStatement::Static) {
    return invokeStaticDirect(obj->o_getClassName(), env,
                              caller, false, check);
  }
  if (check) attemptAccess(FrameInjection::GetClassName(false));
  DECLARE_THREAD_INFO_NOINIT
  MethScopeVariableEnvironment fenv(this);
  directBind(env, caller, fenv);
  fenv.setCurrentObject(obj);
  String clsName(m_class->name());
  EvalFrameInjection fi(clsName, m_fullName->data(), fenv,
                        loc()->file, obj.get(), FrameInjection::ObjectMethod);
  if (m_ref) {
    return strongBind(evalBody(fenv));
  }
  return evalBody(fenv);
}

Variant MethodStatement::invokeStatic(const char* cls, CArrRef params,
    bool check /* = true */) const {
  if (check) attemptAccess(FrameInjection::GetClassName(false));
  DECLARE_THREAD_INFO_NOINIT
  MethScopeVariableEnvironment env(this);
  env.setCurrentClass(cls);
  String clsName(m_class->name());
  EvalFrameInjection fi(clsName, m_fullName->data(), env, loc()->file,
                        NULL, FrameInjection::StaticMethod);
  if (m_ref) {
    return strongBind(invokeImpl(env, params));
  }
  return invokeImpl(env, params);
}

Variant MethodStatement::invokeStaticFewArgs(const char* cls, int count,
  INVOKE_FEW_ARGS_IMPL_ARGS, bool check) const {
  if (check) attemptAccess(FrameInjection::GetClassName(false));
  DECLARE_THREAD_INFO_NOINIT
  MethScopeVariableEnvironment env(this);
  env.setCurrentClass(cls);
  String clsName(m_class->name());
  EvalFrameInjection fi(clsName, m_fullName->data(), env, loc()->file,
                        NULL, FrameInjection::StaticMethod);
  if (m_ref) {
    return strongBind(invokeImplFewArgs(env, count, INVOKE_FEW_ARGS_PASS_ARGS));
  }
  return invokeImplFewArgs(env, count, INVOKE_FEW_ARGS_PASS_ARGS);
}

Variant MethodStatement::
invokeStaticDirect(CStrRef cls, VariableEnvironment &env,
                   const FunctionCallExpression *caller, bool sp,
                   bool check /* = true */)
  const {
  if (check) attemptAccess(FrameInjection::GetClassName(false));
  MethScopeVariableEnvironment fenv(this);
  directBind(env, caller, fenv);
  fenv.setCurrentClass(cls.data());
  CStrRef name = m_class->name()->isame(cls.get()) ? m_class->name() : cls;
  EvalFrameInjection::EvalStaticClassNameHelper helper(name, sp);
  DECLARE_THREAD_INFO_NOINIT
  String clsName(m_class->name());
  EvalFrameInjection fi(clsName, m_fullName->data(), fenv,
                        loc()->file, NULL, FrameInjection::StaticMethod);
  if (m_ref) {
    return strongBind(evalBody(fenv));
  }
  return evalBody(fenv);
}

Variant MethodStatement::evalBody(VariableEnvironment &env) const {
  if (isAbstract()) {
    raise_error("Cannot call abstract method %s()", m_fullName->data());
  }
  if (m_ref) {
    return strongBind(FunctionStatement::evalBody(env));
  } else {
    return FunctionStatement::evalBody(env);
  }
}

void MethodStatement::getInfo(ClassInfo::MethodInfo &info) const {
  FunctionStatement::getInfo(info);
  int attr = info.attribute == ClassInfo::IsNothing ? 0 : info.attribute;
  if (m_modifiers & ClassStatement::Abstract) attr |= ClassInfo::IsAbstract;
  if (m_modifiers & ClassStatement::Final) attr |= ClassInfo::IsFinal;
  if (m_modifiers & ClassStatement::Protected) attr |= ClassInfo::IsProtected;
  if (m_modifiers & ClassStatement::Private) attr |= ClassInfo::IsPrivate;
  if (m_modifiers & ClassStatement::Static) attr |= ClassInfo::IsStatic;
  if (!(attr & ClassInfo::IsProtected || attr & ClassInfo::IsPrivate)) {
    attr |= ClassInfo::IsPublic;
  }
  info.attribute = (ClassInfo::Attribute)attr;
}

void MethodStatement::attemptAccess(const char *context) const {
  if (g_context->getDebuggerBypassCheck()) {
    return;
  }
  int mods = getModifiers();
  const ClassStatement *cs = m_class;
  ClassStatement::Modifier level = ClassStatement::Public;
  if (mods & ClassStatement::Private) level = ClassStatement::Private;
  else if (mods & ClassStatement::Protected) level = ClassStatement::Protected;
  bool access = true;
  if (level == ClassStatement::Protected) {
    while (!cs->hasAccess(context, level)) {
      while ((cs = cs->parentStatement())) {
        if (cs->findMethod(m_name->data())) {
          break;
        }
      }
      if (!cs) {
        access = false;
        break;
      }
    }
  } else {
    access = cs->hasAccess(context, level);
  }

  // special case when handling parent's private constructors that are allowed
  if (!access) {
    if (level == ClassStatement::Private &&
        (strcasecmp(m_name->data(), "__construct") == 0 ||
         strcasecmp(m_name->data(), getClass()->name().c_str()) == 0)) {
      access = cs->hasAccess(context, ClassStatement::Protected);
    }
  }

  if (!access) {
    const char *mod = "protected";
    if (level == ClassStatement::Private) mod = "private";
    throw FatalErrorException(0, "Attempt to call %s %s::%s()%s%s",
                              mod, getClass()->name().c_str(), m_name->data(),
                              context[0] ? " from " : "",
                              context[0] ? context : "");
  }
}

bool MethodStatement::isAbstract() const {
  return getModifiers() & ClassStatement::Abstract ||
    m_class->getModifiers() & ClassStatement::Interface;
}

Variant MethodStatement::MethInvoker(MethodCallPackage &mcp, CArrRef params) {
  const MethodStatement *ms = (const MethodStatement*)mcp.extra;
  bool check = strcasecmp(ms->m_name->data(), "__invoke") != 0;
  bool isStatic = ms->getModifiers() & ClassStatement::Static;
  if (isStatic || !mcp.obj) {
    String cn;
    if (UNLIKELY(!isStatic && mcp.isObj && mcp.obj == NULL)) {
      // this is needed for continuations where
      // we are passed the dummy object
      cn = ms->getClass()->name();
    } else {
      cn = mcp.getClassName();
    }
    if (ms->refReturn()) {
      return strongBind(ms->invokeStatic(cn.c_str(), params, check));
    } else {
      return ms->invokeStatic(cn.c_str(), params, check);
    }
  } else {
    if (ms->refReturn()) {
      return strongBind(ms->invokeInstance(mcp.rootObj, params, check));
    } else {
      return ms->invokeInstance(mcp.rootObj, params, check);
    }
  }
}

Variant MethodStatement::MethInvokerFewArgs(MethodCallPackage &mcp,
    int count, INVOKE_FEW_ARGS_IMPL_ARGS) {
  const MethodStatement *ms = (const MethodStatement*)mcp.extra;
  bool check = strcasecmp(ms->m_name->data(), "__invoke") != 0;
  bool isStatic = ms->getModifiers() & ClassStatement::Static;
  if (isStatic || !mcp.obj) {
    String cn;
    if (UNLIKELY(!isStatic && mcp.isObj && mcp.obj == NULL)) {
      // this is needed for continuations where
      // we are passed the dummy object
      cn = ms->getClass()->name();
    } else {
      cn = mcp.getClassName();
    }
    if (ms->refReturn()) {
      return strongBind(ms->invokeStaticFewArgs(cn.c_str(), count,
        INVOKE_FEW_ARGS_PASS_ARGS, check));
    } else {
      return ms->invokeStaticFewArgs(cn.c_str(), count,
        INVOKE_FEW_ARGS_PASS_ARGS, check);
    }
  } else {
    if (ms->refReturn()) {
      return strongBind(ms->invokeInstanceFewArgs(mcp.rootObj, count,
        INVOKE_FEW_ARGS_PASS_ARGS, check));
    } else {
      return ms->invokeInstanceFewArgs(mcp.rootObj, count,
        INVOKE_FEW_ARGS_PASS_ARGS, check);
    }
  }
}

void MethodStatement::dump(std::ostream &out) const {
  ClassStatement::dumpModifiers(out, m_modifiers, false);
  FunctionStatement::dump(out);
}

///////////////////////////////////////////////////////////////////////////////
}
}

