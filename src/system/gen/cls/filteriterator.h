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

#ifndef __GENERATED_cls_filteriterator_h__
#define __GENERATED_cls_filteriterator_h__

#include <cls/outeriterator.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/iterator.php line 272 */
class c_filteriterator : public ExtObjectData {
  BEGIN_CLASS_MAP(filteriterator)
    PARENT_CLASS(iterator)
    PARENT_CLASS(outeriterator)
    PARENT_CLASS(traversable)
  END_CLASS_MAP(filteriterator)
  DECLARE_CLASS_COMMON(filteriterator, FilterIterator)
  DECLARE_INVOKE_EX(filteriterator, FilterIterator, ObjectData)

  // DECLARE_STATIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_CONSTANT_filteriterator 1

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
  #define OMIT_JUMP_TABLE_CLASS_exists_PUBLIC_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_get_PUBLIC_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_set_PUBLIC_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_lval_PUBLIC_filteriterator 1

  // DECLARE_COMMON_INVOKE
  #define OMIT_JUMP_TABLE_CLASS_STATIC_INVOKE_filteriterator 1
  #define OMIT_JUMP_TABLE_CLASS_INVOKE_filteriterator 1

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
};
extern struct ObjectStaticCallbacks cw_filteriterator;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_filteriterator_h__
