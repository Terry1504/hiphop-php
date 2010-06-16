/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
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
// @generated by HipHop Compiler

#ifndef __GENERATED_cls_reflectionextension_h__
#define __GENERATED_cls_reflectionextension_h__

#include <cls/reflector.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/reflection.php line 740 */
class c_reflectionextension : public ExtObjectData {
  BEGIN_CLASS_MAP(reflectionextension)
    PARENT_CLASS(reflector)
  END_CLASS_MAP(reflectionextension)
  DECLARE_CLASS_COMMON(reflectionextension, ReflectionExtension, ObjectData)
  DECLARE_INVOKE_EX(reflectionextension, ObjectData)

  // DECLARE_STATIC_PROP_OPS
  public:
  static Variant os_getInit(const char *s, int64 hash);
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_reflectionextension 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_reflectionextension 1
  #define OMIT_JUMP_TABLE_CLASS_CONSTANT_reflectionextension 1

  // DECLARE_INSTANCE_PROP_OPS
  public:
  virtual bool o_exists(CStrRef s, int64 hash,
                        const char *context = NULL) const;
  bool o_existsPrivate(CStrRef s, int64 hash) const;
  virtual void o_get(Array &props) const;
  virtual Variant o_get(CStrRef s, int64 hash, bool error = true,
                        const char *context = NULL);
  Variant o_getPrivate(CStrRef s, int64 hash, bool error = true);
  virtual Variant o_set(CStrRef s, int64 hash, CVarRef v,
                        bool forInit = false,
                        const char *context = NULL);
  Variant o_setPrivate(CStrRef s, int64 hash, CVarRef v, bool forInit);
  virtual Variant &o_lval(CStrRef s, int64 hash,
                          const char *context = NULL);
  Variant &o_lvalPrivate(CStrRef s, int64 hash);

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_exists_PUBLIC_reflectionextension 1
  #define OMIT_JUMP_TABLE_CLASS_get_PUBLIC_reflectionextension 1
  #define OMIT_JUMP_TABLE_CLASS_set_PUBLIC_reflectionextension 1
  #define OMIT_JUMP_TABLE_CLASS_lval_PUBLIC_reflectionextension 1

  // DECLARE_COMMON_INVOKE
  static Variant os_invoke(const char *c, const char *s,
                           CArrRef ps, int64 h, bool f = true);
  virtual Variant o_invoke(const char *s, CArrRef ps, int64 h,
                           bool f = true);
  virtual Variant o_invoke_few_args(const char *s, int64 h,
                                    int count,
                                    INVOKE_FEW_ARGS_DECL_ARGS);

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
  public: Variant m_name;
  public: Variant m_info;
  public: void t___construct(Variant v_name);
  public: c_reflectionextension *create(Variant v_name);
  public: ObjectData *dynCreate(CArrRef params, bool init = true);
  public: void dynConstruct(CArrRef params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: String t___tostring();
  public: static Variant ti_export(const char* cls, CVarRef v_name, CVarRef v_ret);
  public: Variant t_getname();
  public: Variant t_getversion();
  public: Variant t_getfunctions();
  public: Variant t_getconstants();
  public: Variant t_getinientries();
  public: Variant t_getclasses();
  public: Array t_getclassnames();
  public: Variant t_info();
  public: static Variant t_export(CVarRef v_name, CVarRef v_ret) { return ti_export("reflectionextension", v_name, v_ret); }
};
extern struct ObjectStaticCallbacks cw_reflectionextension;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_reflectionextension_h__
