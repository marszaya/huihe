// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mail.proto

#ifndef PROTOBUF_mail_2eproto__INCLUDED
#define PROTOBUF_mail_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include "common.pb.h"
#include "item.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_mail_2eproto();
void protobuf_AssignDesc_mail_2eproto();
void protobuf_ShutdownFile_mail_2eproto();

class MailItem;
class MailBox;

// ===================================================================

class MailItem : public ::google::protobuf::MessageLite {
 public:
  MailItem();
  virtual ~MailItem();

  MailItem(const MailItem& from);

  inline MailItem& operator=(const MailItem& from) {
    CopyFrom(from);
    return *this;
  }

  static const MailItem& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const MailItem* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(MailItem* other);

  // implements Message ----------------------------------------------

  MailItem* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const MailItem& from);
  void MergeFrom(const MailItem& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int64 time = 1;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 1;
  inline ::google::protobuf::int64 time() const;
  inline void set_time(::google::protobuf::int64 value);

  // optional int32 read = 2;
  inline bool has_read() const;
  inline void clear_read();
  static const int kReadFieldNumber = 2;
  inline ::google::protobuf::int32 read() const;
  inline void set_read(::google::protobuf::int32 value);

  // optional string title = 3;
  inline bool has_title() const;
  inline void clear_title();
  static const int kTitleFieldNumber = 3;
  inline const ::std::string& title() const;
  inline void set_title(const ::std::string& value);
  inline void set_title(const char* value);
  inline void set_title(const char* value, size_t size);
  inline ::std::string* mutable_title();
  inline ::std::string* release_title();
  inline void set_allocated_title(::std::string* title);

  // optional string src = 4;
  inline bool has_src() const;
  inline void clear_src();
  static const int kSrcFieldNumber = 4;
  inline const ::std::string& src() const;
  inline void set_src(const ::std::string& value);
  inline void set_src(const char* value);
  inline void set_src(const char* value, size_t size);
  inline ::std::string* mutable_src();
  inline ::std::string* release_src();
  inline void set_allocated_src(::std::string* src);

  // optional string dest = 5;
  inline bool has_dest() const;
  inline void clear_dest();
  static const int kDestFieldNumber = 5;
  inline const ::std::string& dest() const;
  inline void set_dest(const ::std::string& value);
  inline void set_dest(const char* value);
  inline void set_dest(const char* value, size_t size);
  inline ::std::string* mutable_dest();
  inline ::std::string* release_dest();
  inline void set_allocated_dest(::std::string* dest);

  // optional string text = 6;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 6;
  inline const ::std::string& text() const;
  inline void set_text(const ::std::string& value);
  inline void set_text(const char* value);
  inline void set_text(const char* value, size_t size);
  inline ::std::string* mutable_text();
  inline ::std::string* release_text();
  inline void set_allocated_text(::std::string* text);

  // repeated .Item attachments = 7;
  inline int attachments_size() const;
  inline void clear_attachments();
  static const int kAttachmentsFieldNumber = 7;
  inline const ::Item& attachments(int index) const;
  inline ::Item* mutable_attachments(int index);
  inline ::Item* add_attachments();
  inline const ::google::protobuf::RepeatedPtrField< ::Item >&
      attachments() const;
  inline ::google::protobuf::RepeatedPtrField< ::Item >*
      mutable_attachments();

  // @@protoc_insertion_point(class_scope:MailItem)
 private:
  inline void set_has_time();
  inline void clear_has_time();
  inline void set_has_read();
  inline void clear_has_read();
  inline void set_has_title();
  inline void clear_has_title();
  inline void set_has_src();
  inline void clear_has_src();
  inline void set_has_dest();
  inline void clear_has_dest();
  inline void set_has_text();
  inline void clear_has_text();

  ::google::protobuf::int64 time_;
  ::std::string* title_;
  ::std::string* src_;
  ::std::string* dest_;
  ::std::string* text_;
  ::google::protobuf::RepeatedPtrField< ::Item > attachments_;
  ::google::protobuf::int32 read_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_mail_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_mail_2eproto();
  #endif
  friend void protobuf_AssignDesc_mail_2eproto();
  friend void protobuf_ShutdownFile_mail_2eproto();

  void InitAsDefaultInstance();
  static MailItem* default_instance_;
};
// -------------------------------------------------------------------

class MailBox : public ::google::protobuf::MessageLite {
 public:
  MailBox();
  virtual ~MailBox();

  MailBox(const MailBox& from);

  inline MailBox& operator=(const MailBox& from) {
    CopyFrom(from);
    return *this;
  }

  static const MailBox& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const MailBox* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(MailBox* other);

  // implements Message ----------------------------------------------

  MailBox* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const MailBox& from);
  void MergeFrom(const MailBox& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .MailItem mails = 1;
  inline int mails_size() const;
  inline void clear_mails();
  static const int kMailsFieldNumber = 1;
  inline const ::MailItem& mails(int index) const;
  inline ::MailItem* mutable_mails(int index);
  inline ::MailItem* add_mails();
  inline const ::google::protobuf::RepeatedPtrField< ::MailItem >&
      mails() const;
  inline ::google::protobuf::RepeatedPtrField< ::MailItem >*
      mutable_mails();

  // @@protoc_insertion_point(class_scope:MailBox)
 private:

  ::google::protobuf::RepeatedPtrField< ::MailItem > mails_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_mail_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_mail_2eproto();
  #endif
  friend void protobuf_AssignDesc_mail_2eproto();
  friend void protobuf_ShutdownFile_mail_2eproto();

  void InitAsDefaultInstance();
  static MailBox* default_instance_;
};
// ===================================================================


// ===================================================================

// MailItem

// optional int64 time = 1;
inline bool MailItem::has_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MailItem::set_has_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MailItem::clear_has_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MailItem::clear_time() {
  time_ = GOOGLE_LONGLONG(0);
  clear_has_time();
}
inline ::google::protobuf::int64 MailItem::time() const {
  return time_;
}
inline void MailItem::set_time(::google::protobuf::int64 value) {
  set_has_time();
  time_ = value;
}

// optional int32 read = 2;
inline bool MailItem::has_read() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MailItem::set_has_read() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MailItem::clear_has_read() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MailItem::clear_read() {
  read_ = 0;
  clear_has_read();
}
inline ::google::protobuf::int32 MailItem::read() const {
  return read_;
}
inline void MailItem::set_read(::google::protobuf::int32 value) {
  set_has_read();
  read_ = value;
}

// optional string title = 3;
inline bool MailItem::has_title() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MailItem::set_has_title() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MailItem::clear_has_title() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MailItem::clear_title() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    title_->clear();
  }
  clear_has_title();
}
inline const ::std::string& MailItem::title() const {
  return *title_;
}
inline void MailItem::set_title(const ::std::string& value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void MailItem::set_title(const char* value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void MailItem::set_title(const char* value, size_t size) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MailItem::mutable_title() {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  return title_;
}
inline ::std::string* MailItem::release_title() {
  clear_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = title_;
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MailItem::set_allocated_title(::std::string* title) {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (title) {
    set_has_title();
    title_ = title;
  } else {
    clear_has_title();
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string src = 4;
inline bool MailItem::has_src() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MailItem::set_has_src() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MailItem::clear_has_src() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MailItem::clear_src() {
  if (src_ != &::google::protobuf::internal::kEmptyString) {
    src_->clear();
  }
  clear_has_src();
}
inline const ::std::string& MailItem::src() const {
  return *src_;
}
inline void MailItem::set_src(const ::std::string& value) {
  set_has_src();
  if (src_ == &::google::protobuf::internal::kEmptyString) {
    src_ = new ::std::string;
  }
  src_->assign(value);
}
inline void MailItem::set_src(const char* value) {
  set_has_src();
  if (src_ == &::google::protobuf::internal::kEmptyString) {
    src_ = new ::std::string;
  }
  src_->assign(value);
}
inline void MailItem::set_src(const char* value, size_t size) {
  set_has_src();
  if (src_ == &::google::protobuf::internal::kEmptyString) {
    src_ = new ::std::string;
  }
  src_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MailItem::mutable_src() {
  set_has_src();
  if (src_ == &::google::protobuf::internal::kEmptyString) {
    src_ = new ::std::string;
  }
  return src_;
}
inline ::std::string* MailItem::release_src() {
  clear_has_src();
  if (src_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = src_;
    src_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MailItem::set_allocated_src(::std::string* src) {
  if (src_ != &::google::protobuf::internal::kEmptyString) {
    delete src_;
  }
  if (src) {
    set_has_src();
    src_ = src;
  } else {
    clear_has_src();
    src_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string dest = 5;
inline bool MailItem::has_dest() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void MailItem::set_has_dest() {
  _has_bits_[0] |= 0x00000010u;
}
inline void MailItem::clear_has_dest() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void MailItem::clear_dest() {
  if (dest_ != &::google::protobuf::internal::kEmptyString) {
    dest_->clear();
  }
  clear_has_dest();
}
inline const ::std::string& MailItem::dest() const {
  return *dest_;
}
inline void MailItem::set_dest(const ::std::string& value) {
  set_has_dest();
  if (dest_ == &::google::protobuf::internal::kEmptyString) {
    dest_ = new ::std::string;
  }
  dest_->assign(value);
}
inline void MailItem::set_dest(const char* value) {
  set_has_dest();
  if (dest_ == &::google::protobuf::internal::kEmptyString) {
    dest_ = new ::std::string;
  }
  dest_->assign(value);
}
inline void MailItem::set_dest(const char* value, size_t size) {
  set_has_dest();
  if (dest_ == &::google::protobuf::internal::kEmptyString) {
    dest_ = new ::std::string;
  }
  dest_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MailItem::mutable_dest() {
  set_has_dest();
  if (dest_ == &::google::protobuf::internal::kEmptyString) {
    dest_ = new ::std::string;
  }
  return dest_;
}
inline ::std::string* MailItem::release_dest() {
  clear_has_dest();
  if (dest_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = dest_;
    dest_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MailItem::set_allocated_dest(::std::string* dest) {
  if (dest_ != &::google::protobuf::internal::kEmptyString) {
    delete dest_;
  }
  if (dest) {
    set_has_dest();
    dest_ = dest;
  } else {
    clear_has_dest();
    dest_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string text = 6;
inline bool MailItem::has_text() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void MailItem::set_has_text() {
  _has_bits_[0] |= 0x00000020u;
}
inline void MailItem::clear_has_text() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void MailItem::clear_text() {
  if (text_ != &::google::protobuf::internal::kEmptyString) {
    text_->clear();
  }
  clear_has_text();
}
inline const ::std::string& MailItem::text() const {
  return *text_;
}
inline void MailItem::set_text(const ::std::string& value) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void MailItem::set_text(const char* value) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void MailItem::set_text(const char* value, size_t size) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MailItem::mutable_text() {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  return text_;
}
inline ::std::string* MailItem::release_text() {
  clear_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = text_;
    text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MailItem::set_allocated_text(::std::string* text) {
  if (text_ != &::google::protobuf::internal::kEmptyString) {
    delete text_;
  }
  if (text) {
    set_has_text();
    text_ = text;
  } else {
    clear_has_text();
    text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated .Item attachments = 7;
inline int MailItem::attachments_size() const {
  return attachments_.size();
}
inline void MailItem::clear_attachments() {
  attachments_.Clear();
}
inline const ::Item& MailItem::attachments(int index) const {
  return attachments_.Get(index);
}
inline ::Item* MailItem::mutable_attachments(int index) {
  return attachments_.Mutable(index);
}
inline ::Item* MailItem::add_attachments() {
  return attachments_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Item >&
MailItem::attachments() const {
  return attachments_;
}
inline ::google::protobuf::RepeatedPtrField< ::Item >*
MailItem::mutable_attachments() {
  return &attachments_;
}

// -------------------------------------------------------------------

// MailBox

// repeated .MailItem mails = 1;
inline int MailBox::mails_size() const {
  return mails_.size();
}
inline void MailBox::clear_mails() {
  mails_.Clear();
}
inline const ::MailItem& MailBox::mails(int index) const {
  return mails_.Get(index);
}
inline ::MailItem* MailBox::mutable_mails(int index) {
  return mails_.Mutable(index);
}
inline ::MailItem* MailBox::add_mails() {
  return mails_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::MailItem >&
MailBox::mails() const {
  return mails_;
}
inline ::google::protobuf::RepeatedPtrField< ::MailItem >*
MailBox::mutable_mails() {
  return &mails_;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_mail_2eproto__INCLUDED
