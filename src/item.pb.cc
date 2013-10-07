// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: item.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "item.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_item_2eproto() {
  delete Item::default_instance_;
  delete ItemSet::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_item_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_item_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::protobuf_AddDesc_common_2eproto();
  Item::default_instance_ = new Item();
  ItemSet::default_instance_ = new ItemSet();
  Item::default_instance_->InitAsDefaultInstance();
  ItemSet::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_item_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_item_2eproto_once_);
void protobuf_AddDesc_item_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_item_2eproto_once_,
                 &protobuf_AddDesc_item_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_item_2eproto {
  StaticDescriptorInitializer_item_2eproto() {
    protobuf_AddDesc_item_2eproto();
  }
} static_descriptor_initializer_item_2eproto_;
#endif

// ===================================================================

bool Item_MajorType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 999:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Item_MajorType Item::MAJOR_TYPE_NORMAL;
const Item_MajorType Item::MAJOR_TYPE_USABLE;
const Item_MajorType Item::MAJOR_TYPE_EQUIP;
const Item_MajorType Item::MAJOR_TYPE_VIRTUAL;
const Item_MajorType Item::MajorType_MIN;
const Item_MajorType Item::MajorType_MAX;
const int Item::MajorType_ARRAYSIZE;
#endif  // _MSC_VER
bool Item_EffectType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 11:
    case 12:
    case 13:
    case 14:
    case 999:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Item_EffectType Item::EFFECT_NONE;
const Item_EffectType Item::EFFECT_EXP;
const Item_EffectType Item::EFFECT_GOLD;
const Item_EffectType Item::EFFECT_MONEY;
const Item_EffectType Item::EFFECT_HP;
const Item_EffectType Item::EFFECT_ARMOR;
const Item_EffectType Item::EFFECT_AD;
const Item_EffectType Item::EFFECT_SPD;
const Item_EffectType Item::EFFECT_PACKED;
const Item_EffectType Item::EffectType_MIN;
const Item_EffectType Item::EffectType_MAX;
const int Item::EffectType_ARRAYSIZE;
#endif  // _MSC_VER
bool Item_PayType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Item_PayType Item::PAY_GOLD;
const Item_PayType Item::PAY_MOENY;
const Item_PayType Item::PayType_MIN;
const Item_PayType Item::PayType_MAX;
const int Item::PayType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Item::kIdFieldNumber;
const int Item::kNumFieldNumber;
const int Item::kExprFieldNumber;
const int Item::kTimelimitFieldNumber;
const int Item::kSubtypeFieldNumber;
const int Item::kCustomdataFieldNumber;
#endif  // !_MSC_VER

Item::Item()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void Item::InitAsDefaultInstance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  id_ = const_cast< ::Identity*>(
      ::Identity::internal_default_instance());
#else
  id_ = const_cast< ::Identity*>(&::Identity::default_instance());
#endif
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  expr_ = const_cast< ::Experience*>(
      ::Experience::internal_default_instance());
#else
  expr_ = const_cast< ::Experience*>(&::Experience::default_instance());
#endif
}

Item::Item(const Item& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void Item::SharedCtor() {
  _cached_size_ = 0;
  id_ = NULL;
  num_ = 0;
  expr_ = NULL;
  timelimit_ = GOOGLE_LONGLONG(0);
  subtype_ = 0;
  customdata_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Item::~Item() {
  SharedDtor();
}

void Item::SharedDtor() {
  if (customdata_ != &::google::protobuf::internal::kEmptyString) {
    delete customdata_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
    delete id_;
    delete expr_;
  }
}

void Item::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const Item& Item::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_item_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_item_2eproto();
#endif
  return *default_instance_;
}

Item* Item::default_instance_ = NULL;

Item* Item::New() const {
  return new Item;
}

void Item::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_id()) {
      if (id_ != NULL) id_->::Identity::Clear();
    }
    num_ = 0;
    if (has_expr()) {
      if (expr_ != NULL) expr_->::Experience::Clear();
    }
    timelimit_ = GOOGLE_LONGLONG(0);
    subtype_ = 0;
    if (has_customdata()) {
      if (customdata_ != &::google::protobuf::internal::kEmptyString) {
        customdata_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool Item::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .Identity id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_id()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_num;
        break;
      }

      // optional int32 num = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &num_)));
          set_has_num();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_expr;
        break;
      }

      // optional .Experience expr = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_expr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_expr()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_timelimit;
        break;
      }

      // optional int64 timelimit = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_timelimit:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &timelimit_)));
          set_has_timelimit();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_subtype;
        break;
      }

      // optional int32 subtype = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_subtype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &subtype_)));
          set_has_subtype();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(82)) goto parse_customdata;
        break;
      }

      // optional bytes customdata = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_customdata:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_customdata()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Item::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .Identity id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->id(), output);
  }

  // optional int32 num = 2;
  if (has_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->num(), output);
  }

  // optional .Experience expr = 3;
  if (has_expr()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      3, this->expr(), output);
  }

  // optional int64 timelimit = 4;
  if (has_timelimit()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->timelimit(), output);
  }

  // optional int32 subtype = 5;
  if (has_subtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->subtype(), output);
  }

  // optional bytes customdata = 10;
  if (has_customdata()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      10, this->customdata(), output);
  }

}

int Item::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .Identity id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->id());
    }

    // optional int32 num = 2;
    if (has_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->num());
    }

    // optional .Experience expr = 3;
    if (has_expr()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->expr());
    }

    // optional int64 timelimit = 4;
    if (has_timelimit()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->timelimit());
    }

    // optional int32 subtype = 5;
    if (has_subtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->subtype());
    }

    // optional bytes customdata = 10;
    if (has_customdata()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->customdata());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Item::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const Item*>(&from));
}

void Item::MergeFrom(const Item& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      mutable_id()->::Identity::MergeFrom(from.id());
    }
    if (from.has_num()) {
      set_num(from.num());
    }
    if (from.has_expr()) {
      mutable_expr()->::Experience::MergeFrom(from.expr());
    }
    if (from.has_timelimit()) {
      set_timelimit(from.timelimit());
    }
    if (from.has_subtype()) {
      set_subtype(from.subtype());
    }
    if (from.has_customdata()) {
      set_customdata(from.customdata());
    }
  }
}

void Item::CopyFrom(const Item& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Item::IsInitialized() const {

  return true;
}

void Item::Swap(Item* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(num_, other->num_);
    std::swap(expr_, other->expr_);
    std::swap(timelimit_, other->timelimit_);
    std::swap(subtype_, other->subtype_);
    std::swap(customdata_, other->customdata_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string Item::GetTypeName() const {
  return "Item";
}


// ===================================================================

#ifndef _MSC_VER
const int ItemSet::kItemsFieldNumber;
const int ItemSet::kMaxidFieldNumber;
#endif  // !_MSC_VER

ItemSet::ItemSet()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void ItemSet::InitAsDefaultInstance() {
}

ItemSet::ItemSet(const ItemSet& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void ItemSet::SharedCtor() {
  _cached_size_ = 0;
  maxid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ItemSet::~ItemSet() {
  SharedDtor();
}

void ItemSet::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ItemSet::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ItemSet& ItemSet::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_item_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_item_2eproto();
#endif
  return *default_instance_;
}

ItemSet* ItemSet::default_instance_ = NULL;

ItemSet* ItemSet::New() const {
  return new ItemSet;
}

void ItemSet::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    maxid_ = 0;
  }
  items_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool ItemSet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Item items = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_items:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_items()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_items;
        if (input->ExpectTag(800)) goto parse_maxid;
        break;
      }

      // optional int32 maxid = 100;
      case 100: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_maxid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &maxid_)));
          set_has_maxid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ItemSet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .Item items = 1;
  for (int i = 0; i < this->items_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->items(i), output);
  }

  // optional int32 maxid = 100;
  if (has_maxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(100, this->maxid(), output);
  }

}

int ItemSet::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // optional int32 maxid = 100;
    if (has_maxid()) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->maxid());
    }

  }
  // repeated .Item items = 1;
  total_size += 1 * this->items_size();
  for (int i = 0; i < this->items_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->items(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ItemSet::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ItemSet*>(&from));
}

void ItemSet::MergeFrom(const ItemSet& from) {
  GOOGLE_CHECK_NE(&from, this);
  items_.MergeFrom(from.items_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_maxid()) {
      set_maxid(from.maxid());
    }
  }
}

void ItemSet::CopyFrom(const ItemSet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ItemSet::IsInitialized() const {

  return true;
}

void ItemSet::Swap(ItemSet* other) {
  if (other != this) {
    items_.Swap(&other->items_);
    std::swap(maxid_, other->maxid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string ItemSet::GetTypeName() const {
  return "ItemSet";
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)