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

#ifndef __GENERATED_cls_RecursiveDirectoryIterator_h__
#define __GENERATED_cls_RecursiveDirectoryIterator_h__

#include <cls/DirectoryIterator.h>
#include <cls/RecursiveIterator.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/iterator.php line 755 */
class c_RecursiveDirectoryIterator : public c_DirectoryIterator {
  public:

  // Properties

  // Class Map
  BEGIN_CLASS_MAP(RecursiveDirectoryIterator)
    PARENT_CLASS(DirectoryIterator)
    PARENT_CLASS(Iterator)
    PARENT_CLASS(RecursiveIterator)
    PARENT_CLASS(SeekableIterator)
    PARENT_CLASS(SplFileInfo)
    PARENT_CLASS(Traversable)
  END_CLASS_MAP(RecursiveDirectoryIterator)
  DECLARE_CLASS_COMMON(RecursiveDirectoryIterator, RecursiveDirectoryIterator)
  DECLARE_INVOKE_EX(RecursiveDirectoryIterator, RecursiveDirectoryIterator, DirectoryIterator)

  // DECLARE_STATIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_RecursiveDirectoryIterator 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_RecursiveDirectoryIterator 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_RecursiveDirectoryIterator 1
  static Variant os_constant(const char *s);

  // DECLARE_INSTANCE_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_GETARRAY_RecursiveDirectoryIterator 1
  #define OMIT_JUMP_TABLE_CLASS_SETARRAY_RecursiveDirectoryIterator 1
  #define OMIT_JUMP_TABLE_CLASS_realProp_RecursiveDirectoryIterator 1
  #define OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_RecursiveDirectoryIterator 1

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_RecursiveDirectoryIterator 1

  // DECLARE_COMMON_INVOKE
  #define OMIT_JUMP_TABLE_CLASS_STATIC_INVOKE_RecursiveDirectoryIterator 1
  virtual Variant o_invoke(MethodIndex methodIndex, const char *s, CArrRef ps,
                           int64 h, bool f = true);
  virtual Variant o_invoke_few_args(MethodIndex methodIndex, const char *s,
                                    int64 h, int count,
                                    INVOKE_FEW_ARGS_DECL_ARGS);

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
  public: void t___construct(Variant v_path, Variant v_flags = 16LL /* recursivedirectoryiterator::CURRENT_AS_FILEINFO */);
  public: c_RecursiveDirectoryIterator *create(Variant v_path, Variant v_flags = 16LL /* recursivedirectoryiterator::CURRENT_AS_FILEINFO */);
  public: ObjectData *dynCreate(CArrRef params, bool init = true);
  public: void dynConstruct(CArrRef params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: Variant t_current();
  public: Variant t_key();
  public: Variant t_next();
  public: Variant t_rewind();
  public: Variant t_seek(CVarRef v_position);
  public: String t___tostring();
  public: bool t_valid();
  public: bool t_haschildren();
  public: Object t_getchildren();
  public: String t_getsubpath();
  public: String t_getsubpathname();
};
extern struct ObjectStaticCallbacks cw_RecursiveDirectoryIterator;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_RecursiveDirectoryIterator_h__
