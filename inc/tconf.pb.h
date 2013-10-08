// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tconf.proto

#ifndef PROTOBUF_tconf_2eproto__INCLUDED
#define PROTOBUF_tconf_2eproto__INCLUDED

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
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_tconf_2eproto();
void protobuf_AssignDesc_tconf_2eproto();
void protobuf_ShutdownFile_tconf_2eproto();

class TconfColDef;
class TconfRow;
class TconfTable;

// ===================================================================

class TconfColDef : public ::google::protobuf::Message {
 public:
  TconfColDef();
  virtual ~TconfColDef();

  TconfColDef(const TconfColDef& from);

  inline TconfColDef& operator=(const TconfColDef& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TconfColDef& default_instance();

  void Swap(TconfColDef* other);

  // implements Message ----------------------------------------------

  TconfColDef* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TconfColDef& from);
  void MergeFrom(const TconfColDef& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional string type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline const ::std::string& type() const;
  inline void set_type(const ::std::string& value);
  inline void set_type(const char* value);
  inline void set_type(const char* value, size_t size);
  inline ::std::string* mutable_type();
  inline ::std::string* release_type();
  inline void set_allocated_type(::std::string* type);

  // @@protoc_insertion_point(class_scope:TconfColDef)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_tconf_2eproto();
  friend void protobuf_AssignDesc_tconf_2eproto();
  friend void protobuf_ShutdownFile_tconf_2eproto();

  void InitAsDefaultInstance();
  static TconfColDef* default_instance_;
};
// -------------------------------------------------------------------

class TconfRow : public ::google::protobuf::Message {
 public:
  TconfRow();
  virtual ~TconfRow();

  TconfRow(const TconfRow& from);

  inline TconfRow& operator=(const TconfRow& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TconfRow& default_instance();

  void Swap(TconfRow* other);

  // implements Message ----------------------------------------------

  TconfRow* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TconfRow& from);
  void MergeFrom(const TconfRow& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated string values = 1;
  inline int values_size() const;
  inline void clear_values();
  static const int kValuesFieldNumber = 1;
  inline const ::std::string& values(int index) const;
  inline ::std::string* mutable_values(int index);
  inline void set_values(int index, const ::std::string& value);
  inline void set_values(int index, const char* value);
  inline void set_values(int index, const char* value, size_t size);
  inline ::std::string* add_values();
  inline void add_values(const ::std::string& value);
  inline void add_values(const char* value);
  inline void add_values(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& values() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_values();

  // @@protoc_insertion_point(class_scope:TconfRow)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::std::string> values_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_tconf_2eproto();
  friend void protobuf_AssignDesc_tconf_2eproto();
  friend void protobuf_ShutdownFile_tconf_2eproto();

  void InitAsDefaultInstance();
  static TconfRow* default_instance_;
};
// -------------------------------------------------------------------

class TconfTable : public ::google::protobuf::Message {
 public:
  TconfTable();
  virtual ~TconfTable();

  TconfTable(const TconfTable& from);

  inline TconfTable& operator=(const TconfTable& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TconfTable& default_instance();

  void Swap(TconfTable* other);

  // implements Message ----------------------------------------------

  TconfTable* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TconfTable& from);
  void MergeFrom(const TconfTable& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .TconfColDef colDefs = 1;
  inline int coldefs_size() const;
  inline void clear_coldefs();
  static const int kColDefsFieldNumber = 1;
  inline const ::TconfColDef& coldefs(int index) const;
  inline ::TconfColDef* mutable_coldefs(int index);
  inline ::TconfColDef* add_coldefs();
  inline const ::google::protobuf::RepeatedPtrField< ::TconfColDef >&
      coldefs() const;
  inline ::google::protobuf::RepeatedPtrField< ::TconfColDef >*
      mutable_coldefs();

  // repeated .TconfRow rows = 2;
  inline int rows_size() const;
  inline void clear_rows();
  static const int kRowsFieldNumber = 2;
  inline const ::TconfRow& rows(int index) const;
  inline ::TconfRow* mutable_rows(int index);
  inline ::TconfRow* add_rows();
  inline const ::google::protobuf::RepeatedPtrField< ::TconfRow >&
      rows() const;
  inline ::google::protobuf::RepeatedPtrField< ::TconfRow >*
      mutable_rows();

  // @@protoc_insertion_point(class_scope:TconfTable)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::TconfColDef > coldefs_;
  ::google::protobuf::RepeatedPtrField< ::TconfRow > rows_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_tconf_2eproto();
  friend void protobuf_AssignDesc_tconf_2eproto();
  friend void protobuf_ShutdownFile_tconf_2eproto();

  void InitAsDefaultInstance();
  static TconfTable* default_instance_;
};
// ===================================================================


// ===================================================================

// TconfColDef

// optional string name = 1;
inline bool TconfColDef::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TconfColDef::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TconfColDef::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TconfColDef::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& TconfColDef::name() const {
  return *name_;
}
inline void TconfColDef::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void TconfColDef::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void TconfColDef::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TconfColDef::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* TconfColDef::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TconfColDef::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string type = 2;
inline bool TconfColDef::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TconfColDef::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TconfColDef::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TconfColDef::clear_type() {
  if (type_ != &::google::protobuf::internal::kEmptyString) {
    type_->clear();
  }
  clear_has_type();
}
inline const ::std::string& TconfColDef::type() const {
  return *type_;
}
inline void TconfColDef::set_type(const ::std::string& value) {
  set_has_type();
  if (type_ == &::google::protobuf::internal::kEmptyString) {
    type_ = new ::std::string;
  }
  type_->assign(value);
}
inline void TconfColDef::set_type(const char* value) {
  set_has_type();
  if (type_ == &::google::protobuf::internal::kEmptyString) {
    type_ = new ::std::string;
  }
  type_->assign(value);
}
inline void TconfColDef::set_type(const char* value, size_t size) {
  set_has_type();
  if (type_ == &::google::protobuf::internal::kEmptyString) {
    type_ = new ::std::string;
  }
  type_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TconfColDef::mutable_type() {
  set_has_type();
  if (type_ == &::google::protobuf::internal::kEmptyString) {
    type_ = new ::std::string;
  }
  return type_;
}
inline ::std::string* TconfColDef::release_type() {
  clear_has_type();
  if (type_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = type_;
    type_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TconfColDef::set_allocated_type(::std::string* type) {
  if (type_ != &::google::protobuf::internal::kEmptyString) {
    delete type_;
  }
  if (type) {
    set_has_type();
    type_ = type;
  } else {
    clear_has_type();
    type_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// TconfRow

// repeated string values = 1;
inline int TconfRow::values_size() const {
  return values_.size();
}
inline void TconfRow::clear_values() {
  values_.Clear();
}
inline const ::std::string& TconfRow::values(int index) const {
  return values_.Get(index);
}
inline ::std::string* TconfRow::mutable_values(int index) {
  return values_.Mutable(index);
}
inline void TconfRow::set_values(int index, const ::std::string& value) {
  values_.Mutable(index)->assign(value);
}
inline void TconfRow::set_values(int index, const char* value) {
  values_.Mutable(index)->assign(value);
}
inline void TconfRow::set_values(int index, const char* value, size_t size) {
  values_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TconfRow::add_values() {
  return values_.Add();
}
inline void TconfRow::add_values(const ::std::string& value) {
  values_.Add()->assign(value);
}
inline void TconfRow::add_values(const char* value) {
  values_.Add()->assign(value);
}
inline void TconfRow::add_values(const char* value, size_t size) {
  values_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
TconfRow::values() const {
  return values_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
TconfRow::mutable_values() {
  return &values_;
}

// -------------------------------------------------------------------

// TconfTable

// repeated .TconfColDef colDefs = 1;
inline int TconfTable::coldefs_size() const {
  return coldefs_.size();
}
inline void TconfTable::clear_coldefs() {
  coldefs_.Clear();
}
inline const ::TconfColDef& TconfTable::coldefs(int index) const {
  return coldefs_.Get(index);
}
inline ::TconfColDef* TconfTable::mutable_coldefs(int index) {
  return coldefs_.Mutable(index);
}
inline ::TconfColDef* TconfTable::add_coldefs() {
  return coldefs_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::TconfColDef >&
TconfTable::coldefs() const {
  return coldefs_;
}
inline ::google::protobuf::RepeatedPtrField< ::TconfColDef >*
TconfTable::mutable_coldefs() {
  return &coldefs_;
}

// repeated .TconfRow rows = 2;
inline int TconfTable::rows_size() const {
  return rows_.size();
}
inline void TconfTable::clear_rows() {
  rows_.Clear();
}
inline const ::TconfRow& TconfTable::rows(int index) const {
  return rows_.Get(index);
}
inline ::TconfRow* TconfTable::mutable_rows(int index) {
  return rows_.Mutable(index);
}
inline ::TconfRow* TconfTable::add_rows() {
  return rows_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::TconfRow >&
TconfTable::rows() const {
  return rows_;
}
inline ::google::protobuf::RepeatedPtrField< ::TconfRow >*
TconfTable::mutable_rows() {
  return &rows_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_tconf_2eproto__INCLUDED
