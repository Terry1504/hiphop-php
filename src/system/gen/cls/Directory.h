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

#ifndef __GENERATED_cls_Directory_h__
#define __GENERATED_cls_Directory_h__


namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/directory.php line 3 */
class c_Directory : public ExtObjectData {
  public:

  // Properties
  Variant m_path;
  Variant m_handle;

  // Class Map
  BEGIN_CLASS_MAP(Directory)
  END_CLASS_MAP(Directory)
  DECLARE_CLASS_COMMON(Directory, Directory)
  DECLARE_INVOKE_EX(Directory, Directory, ObjectData)

  // DECLARE_STATIC_PROP_OPS
  public:
  static Variant os_getInit(CStrRef s);
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_Directory 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_Directory 1
  #define OMIT_JUMP_TABLE_CLASS_CONSTANT_Directory 1

  // DECLARE_INSTANCE_PROP_OPS
  public:
  virtual void o_getArray(Array &props) const;
  #define OMIT_JUMP_TABLE_CLASS_SETARRAY_Directory 1
  #define OMIT_JUMP_TABLE_CLASS_realProp_Directory 1
  #define OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_Directory 1

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  virtual Variant *o_realPropPublic(CStrRef s, int flags) const;

  // DECLARE_COMMON_INVOKE
  #define OMIT_JUMP_TABLE_CLASS_STATIC_INVOKE_Directory 1
  virtual Variant o_invoke(MethodIndex methodIndex, const char *s, CArrRef ps,
                           int64 h, bool f = true);
  virtual Variant o_invoke_few_args(MethodIndex methodIndex, const char *s,
                                    int64 h, int count,
                                    INVOKE_FEW_ARGS_DECL_ARGS);

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
  public: void t___construct(Variant v_path);
  public: c_Directory *create(Variant v_path);
  public: ObjectData *dynCreate(CArrRef params, bool init = true);
  public: void dynConstruct(CArrRef params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: Variant t_read();
  public: Variant t_rewind();
  public: Variant t_close();
};
extern struct ObjectStaticCallbacks cw_Directory;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_Directory_h__
