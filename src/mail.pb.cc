// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mail.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "mail.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_mail_2eproto() {
  delete MailItem::default_instance_;
  delete MailBox::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_mail_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_mail_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::protobuf_AddDesc_common_2eproto();
  ::protobuf_AddDesc_item_2eproto();
  MailItem::default_instance_ = new MailItem();
  MailBox::default_instance_ = new MailBox();
  MailItem::default_instance_->InitAsDefaultInstance();
  MailBox::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_mail_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_mail_2eproto_once_);
void protobuf_AddDesc_mail_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_mail_2eproto_once_,
                 &protobuf_AddDesc_mail_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_mail_2eproto {
  StaticDescriptorInitializer_mail_2eproto() {
    protobuf_AddDesc_mail_2eproto();
  }
} static_descriptor_initializer_mail_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int MailItem::kTimeFieldNumber;
const int MailItem::kReadFieldNumber;
const int MailItem::kTitleFieldNumber;
const int MailItem::kSrcFieldNumber;
const int MailItem::kDestFieldNumber;
const int MailItem::kTextFieldNumber;
const int MailItem::kAttachmentsFieldNumber;
#endif  // !_MSC_VER

MailItem::MailItem()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void MailItem::InitAsDefaultInstance() {
}

MailItem::MailItem(const MailItem& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void MailItem::SharedCtor() {
  _cached_size_ = 0;
  time_ = GOOGLE_LONGLONG(0);
  read_ = 0;
  title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  src_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  dest_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MailItem::~MailItem() {
  SharedDtor();
}

void MailItem::SharedDtor() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (src_ != &::google::protobuf::internal::kEmptyString) {
    delete src_;
  }
  if (dest_ != &::google::protobuf::internal::kEmptyString) {
    delete dest_;
  }
  if (text_ != &::google::protobuf::internal::kEmptyString) {
    delete text_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void MailItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const MailItem& MailItem::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_mail_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_mail_2eproto();
#endif
  return *default_instance_;
}

MailItem* MailItem::default_instance_ = NULL;

MailItem* MailItem::New() const {
  return new MailItem;
}

void MailItem::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    time_ = GOOGLE_LONGLONG(0);
    read_ = 0;
    if (has_title()) {
      if (title_ != &::google::protobuf::internal::kEmptyString) {
        title_->clear();
      }
    }
    if (has_src()) {
      if (src_ != &::google::protobuf::internal::kEmptyString) {
        src_->clear();
      }
    }
    if (has_dest()) {
      if (dest_ != &::google::protobuf::internal::kEmptyString) {
        dest_->clear();
      }
    }
    if (has_text()) {
      if (text_ != &::google::protobuf::internal::kEmptyString) {
        text_->clear();
      }
    }
  }
  attachments_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool MailItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 time = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &time_)));
          set_has_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_read;
        break;
      }

      // optional int32 read = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_read:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &read_)));
          set_has_read();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_title;
        break;
      }

      // optional string title = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_title:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_title()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_src;
        break;
      }

      // optional string src = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_src:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_src()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_dest;
        break;
      }

      // optional string dest = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dest:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_dest()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_text;
        break;
      }

      // optional string text = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_text:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_text()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_attachments;
        break;
      }

      // repeated .Item attachments = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_attachments:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_attachments()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_attachments;
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

void MailItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int64 time = 1;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->time(), output);
  }

  // optional int32 read = 2;
  if (has_read()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->read(), output);
  }

  // optional string title = 3;
  if (has_title()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->title(), output);
  }

  // optional string src = 4;
  if (has_src()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->src(), output);
  }

  // optional string dest = 5;
  if (has_dest()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->dest(), output);
  }

  // optional string text = 6;
  if (has_text()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->text(), output);
  }

  // repeated .Item attachments = 7;
  for (int i = 0; i < this->attachments_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      7, this->attachments(i), output);
  }

}

int MailItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int64 time = 1;
    if (has_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->time());
    }

    // optional int32 read = 2;
    if (has_read()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->read());
    }

    // optional string title = 3;
    if (has_title()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->title());
    }

    // optional string src = 4;
    if (has_src()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->src());
    }

    // optional string dest = 5;
    if (has_dest()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->dest());
    }

    // optional string text = 6;
    if (has_text()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->text());
    }

  }
  // repeated .Item attachments = 7;
  total_size += 1 * this->attachments_size();
  for (int i = 0; i < this->attachments_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->attachments(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MailItem::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const MailItem*>(&from));
}

void MailItem::MergeFrom(const MailItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  attachments_.MergeFrom(from.attachments_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_time()) {
      set_time(from.time());
    }
    if (from.has_read()) {
      set_read(from.read());
    }
    if (from.has_title()) {
      set_title(from.title());
    }
    if (from.has_src()) {
      set_src(from.src());
    }
    if (from.has_dest()) {
      set_dest(from.dest());
    }
    if (from.has_text()) {
      set_text(from.text());
    }
  }
}

void MailItem::CopyFrom(const MailItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MailItem::IsInitialized() const {

  return true;
}

void MailItem::Swap(MailItem* other) {
  if (other != this) {
    std::swap(time_, other->time_);
    std::swap(read_, other->read_);
    std::swap(title_, other->title_);
    std::swap(src_, other->src_);
    std::swap(dest_, other->dest_);
    std::swap(text_, other->text_);
    attachments_.Swap(&other->attachments_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string MailItem::GetTypeName() const {
  return "MailItem";
}


// ===================================================================

#ifndef _MSC_VER
const int MailBox::kMailsFieldNumber;
#endif  // !_MSC_VER

MailBox::MailBox()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void MailBox::InitAsDefaultInstance() {
}

MailBox::MailBox(const MailBox& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void MailBox::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MailBox::~MailBox() {
  SharedDtor();
}

void MailBox::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void MailBox::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const MailBox& MailBox::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_mail_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_mail_2eproto();
#endif
  return *default_instance_;
}

MailBox* MailBox::default_instance_ = NULL;

MailBox* MailBox::New() const {
  return new MailBox;
}

void MailBox::Clear() {
  mails_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool MailBox::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .MailItem mails = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_mails:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_mails()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_mails;
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

void MailBox::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .MailItem mails = 1;
  for (int i = 0; i < this->mails_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->mails(i), output);
  }

}

int MailBox::ByteSize() const {
  int total_size = 0;

  // repeated .MailItem mails = 1;
  total_size += 1 * this->mails_size();
  for (int i = 0; i < this->mails_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->mails(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MailBox::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const MailBox*>(&from));
}

void MailBox::MergeFrom(const MailBox& from) {
  GOOGLE_CHECK_NE(&from, this);
  mails_.MergeFrom(from.mails_);
}

void MailBox::CopyFrom(const MailBox& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MailBox::IsInitialized() const {

  return true;
}

void MailBox::Swap(MailBox* other) {
  if (other != this) {
    mails_.Swap(&other->mails_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string MailBox::GetTypeName() const {
  return "MailBox";
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
