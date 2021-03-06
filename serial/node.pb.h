// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: node.proto

#ifndef PROTOBUF_node_2eproto__INCLUDED
#define PROTOBUF_node_2eproto__INCLUDED

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

namespace serial {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_node_2eproto();
void protobuf_AssignDesc_node_2eproto();
void protobuf_ShutdownFile_node_2eproto();

class Point;
class LineList;
class Boundary;
class ExitLine;
class NodeMeta;

// ===================================================================

class Point : public ::google::protobuf::Message {
 public:
  Point();
  virtual ~Point();

  Point(const Point& from);

  inline Point& operator=(const Point& from) {
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
  static const Point& default_instance();

  void Swap(Point* other);

  // implements Message ----------------------------------------------

  Point* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Point& from);
  void MergeFrom(const Point& from);
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

  // required float x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline float x() const;
  inline void set_x(float value);

  // required float y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline float y() const;
  inline void set_y(float value);

  // @@protoc_insertion_point(class_scope:serial.Point)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  float x_;
  float y_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_node_2eproto();
  friend void protobuf_AssignDesc_node_2eproto();
  friend void protobuf_ShutdownFile_node_2eproto();

  void InitAsDefaultInstance();
  static Point* default_instance_;
};
// -------------------------------------------------------------------

class LineList : public ::google::protobuf::Message {
 public:
  LineList();
  virtual ~LineList();

  LineList(const LineList& from);

  inline LineList& operator=(const LineList& from) {
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
  static const LineList& default_instance();

  void Swap(LineList* other);

  // implements Message ----------------------------------------------

  LineList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LineList& from);
  void MergeFrom(const LineList& from);
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

  // repeated .serial.Point points = 1;
  inline int points_size() const;
  inline void clear_points();
  static const int kPointsFieldNumber = 1;
  inline const ::serial::Point& points(int index) const;
  inline ::serial::Point* mutable_points(int index);
  inline ::serial::Point* add_points();
  inline const ::google::protobuf::RepeatedPtrField< ::serial::Point >&
      points() const;
  inline ::google::protobuf::RepeatedPtrField< ::serial::Point >*
      mutable_points();

  // @@protoc_insertion_point(class_scope:serial.LineList)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::serial::Point > points_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_node_2eproto();
  friend void protobuf_AssignDesc_node_2eproto();
  friend void protobuf_ShutdownFile_node_2eproto();

  void InitAsDefaultInstance();
  static LineList* default_instance_;
};
// -------------------------------------------------------------------

class Boundary : public ::google::protobuf::Message {
 public:
  Boundary();
  virtual ~Boundary();

  Boundary(const Boundary& from);

  inline Boundary& operator=(const Boundary& from) {
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
  static const Boundary& default_instance();

  void Swap(Boundary* other);

  // implements Message ----------------------------------------------

  Boundary* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Boundary& from);
  void MergeFrom(const Boundary& from);
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

  // repeated .serial.LineList line_list = 1;
  inline int line_list_size() const;
  inline void clear_line_list();
  static const int kLineListFieldNumber = 1;
  inline const ::serial::LineList& line_list(int index) const;
  inline ::serial::LineList* mutable_line_list(int index);
  inline ::serial::LineList* add_line_list();
  inline const ::google::protobuf::RepeatedPtrField< ::serial::LineList >&
      line_list() const;
  inline ::google::protobuf::RepeatedPtrField< ::serial::LineList >*
      mutable_line_list();

  // @@protoc_insertion_point(class_scope:serial.Boundary)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::serial::LineList > line_list_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_node_2eproto();
  friend void protobuf_AssignDesc_node_2eproto();
  friend void protobuf_ShutdownFile_node_2eproto();

  void InitAsDefaultInstance();
  static Boundary* default_instance_;
};
// -------------------------------------------------------------------

class ExitLine : public ::google::protobuf::Message {
 public:
  ExitLine();
  virtual ~ExitLine();

  ExitLine(const ExitLine& from);

  inline ExitLine& operator=(const ExitLine& from) {
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
  static const ExitLine& default_instance();

  void Swap(ExitLine* other);

  // implements Message ----------------------------------------------

  ExitLine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ExitLine& from);
  void MergeFrom(const ExitLine& from);
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

  // required .serial.Point e1 = 1;
  inline bool has_e1() const;
  inline void clear_e1();
  static const int kE1FieldNumber = 1;
  inline const ::serial::Point& e1() const;
  inline ::serial::Point* mutable_e1();
  inline ::serial::Point* release_e1();
  inline void set_allocated_e1(::serial::Point* e1);

  // required .serial.Point e2 = 2;
  inline bool has_e2() const;
  inline void clear_e2();
  static const int kE2FieldNumber = 2;
  inline const ::serial::Point& e2() const;
  inline ::serial::Point* mutable_e2();
  inline ::serial::Point* release_e2();
  inline void set_allocated_e2(::serial::Point* e2);

  // optional uint32 exit_id = 3;
  inline bool has_exit_id() const;
  inline void clear_exit_id();
  static const int kExitIdFieldNumber = 3;
  inline ::google::protobuf::uint32 exit_id() const;
  inline void set_exit_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:serial.ExitLine)
 private:
  inline void set_has_e1();
  inline void clear_has_e1();
  inline void set_has_e2();
  inline void clear_has_e2();
  inline void set_has_exit_id();
  inline void clear_has_exit_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::serial::Point* e1_;
  ::serial::Point* e2_;
  ::google::protobuf::uint32 exit_id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_node_2eproto();
  friend void protobuf_AssignDesc_node_2eproto();
  friend void protobuf_ShutdownFile_node_2eproto();

  void InitAsDefaultInstance();
  static ExitLine* default_instance_;
};
// -------------------------------------------------------------------

class NodeMeta : public ::google::protobuf::Message {
 public:
  NodeMeta();
  virtual ~NodeMeta();

  NodeMeta(const NodeMeta& from);

  inline NodeMeta& operator=(const NodeMeta& from) {
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
  static const NodeMeta& default_instance();

  void Swap(NodeMeta* other);

  // implements Message ----------------------------------------------

  NodeMeta* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NodeMeta& from);
  void MergeFrom(const NodeMeta& from);
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

  // optional .serial.Boundary boundaries = 1;
  inline bool has_boundaries() const;
  inline void clear_boundaries();
  static const int kBoundariesFieldNumber = 1;
  inline const ::serial::Boundary& boundaries() const;
  inline ::serial::Boundary* mutable_boundaries();
  inline ::serial::Boundary* release_boundaries();
  inline void set_allocated_boundaries(::serial::Boundary* boundaries);

  // repeated .serial.ExitLine exit_lines = 2;
  inline int exit_lines_size() const;
  inline void clear_exit_lines();
  static const int kExitLinesFieldNumber = 2;
  inline const ::serial::ExitLine& exit_lines(int index) const;
  inline ::serial::ExitLine* mutable_exit_lines(int index);
  inline ::serial::ExitLine* add_exit_lines();
  inline const ::google::protobuf::RepeatedPtrField< ::serial::ExitLine >&
      exit_lines() const;
  inline ::google::protobuf::RepeatedPtrField< ::serial::ExitLine >*
      mutable_exit_lines();

  // optional string image_loc = 3;
  inline bool has_image_loc() const;
  inline void clear_image_loc();
  static const int kImageLocFieldNumber = 3;
  inline const ::std::string& image_loc() const;
  inline void set_image_loc(const ::std::string& value);
  inline void set_image_loc(const char* value);
  inline void set_image_loc(const char* value, size_t size);
  inline ::std::string* mutable_image_loc();
  inline ::std::string* release_image_loc();
  inline void set_allocated_image_loc(::std::string* image_loc);

  // @@protoc_insertion_point(class_scope:serial.NodeMeta)
 private:
  inline void set_has_boundaries();
  inline void clear_has_boundaries();
  inline void set_has_image_loc();
  inline void clear_has_image_loc();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::serial::Boundary* boundaries_;
  ::google::protobuf::RepeatedPtrField< ::serial::ExitLine > exit_lines_;
  ::std::string* image_loc_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_node_2eproto();
  friend void protobuf_AssignDesc_node_2eproto();
  friend void protobuf_ShutdownFile_node_2eproto();

  void InitAsDefaultInstance();
  static NodeMeta* default_instance_;
};
// ===================================================================


// ===================================================================

// Point

// required float x = 1;
inline bool Point::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Point::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Point::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Point::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float Point::x() const {
  return x_;
}
inline void Point::set_x(float value) {
  set_has_x();
  x_ = value;
}

// required float y = 2;
inline bool Point::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Point::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Point::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Point::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float Point::y() const {
  return y_;
}
inline void Point::set_y(float value) {
  set_has_y();
  y_ = value;
}

// -------------------------------------------------------------------

// LineList

// repeated .serial.Point points = 1;
inline int LineList::points_size() const {
  return points_.size();
}
inline void LineList::clear_points() {
  points_.Clear();
}
inline const ::serial::Point& LineList::points(int index) const {
  return points_.Get(index);
}
inline ::serial::Point* LineList::mutable_points(int index) {
  return points_.Mutable(index);
}
inline ::serial::Point* LineList::add_points() {
  return points_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::serial::Point >&
LineList::points() const {
  return points_;
}
inline ::google::protobuf::RepeatedPtrField< ::serial::Point >*
LineList::mutable_points() {
  return &points_;
}

// -------------------------------------------------------------------

// Boundary

// repeated .serial.LineList line_list = 1;
inline int Boundary::line_list_size() const {
  return line_list_.size();
}
inline void Boundary::clear_line_list() {
  line_list_.Clear();
}
inline const ::serial::LineList& Boundary::line_list(int index) const {
  return line_list_.Get(index);
}
inline ::serial::LineList* Boundary::mutable_line_list(int index) {
  return line_list_.Mutable(index);
}
inline ::serial::LineList* Boundary::add_line_list() {
  return line_list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::serial::LineList >&
Boundary::line_list() const {
  return line_list_;
}
inline ::google::protobuf::RepeatedPtrField< ::serial::LineList >*
Boundary::mutable_line_list() {
  return &line_list_;
}

// -------------------------------------------------------------------

// ExitLine

// required .serial.Point e1 = 1;
inline bool ExitLine::has_e1() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ExitLine::set_has_e1() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ExitLine::clear_has_e1() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ExitLine::clear_e1() {
  if (e1_ != NULL) e1_->::serial::Point::Clear();
  clear_has_e1();
}
inline const ::serial::Point& ExitLine::e1() const {
  return e1_ != NULL ? *e1_ : *default_instance_->e1_;
}
inline ::serial::Point* ExitLine::mutable_e1() {
  set_has_e1();
  if (e1_ == NULL) e1_ = new ::serial::Point;
  return e1_;
}
inline ::serial::Point* ExitLine::release_e1() {
  clear_has_e1();
  ::serial::Point* temp = e1_;
  e1_ = NULL;
  return temp;
}
inline void ExitLine::set_allocated_e1(::serial::Point* e1) {
  delete e1_;
  e1_ = e1;
  if (e1) {
    set_has_e1();
  } else {
    clear_has_e1();
  }
}

// required .serial.Point e2 = 2;
inline bool ExitLine::has_e2() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ExitLine::set_has_e2() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ExitLine::clear_has_e2() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ExitLine::clear_e2() {
  if (e2_ != NULL) e2_->::serial::Point::Clear();
  clear_has_e2();
}
inline const ::serial::Point& ExitLine::e2() const {
  return e2_ != NULL ? *e2_ : *default_instance_->e2_;
}
inline ::serial::Point* ExitLine::mutable_e2() {
  set_has_e2();
  if (e2_ == NULL) e2_ = new ::serial::Point;
  return e2_;
}
inline ::serial::Point* ExitLine::release_e2() {
  clear_has_e2();
  ::serial::Point* temp = e2_;
  e2_ = NULL;
  return temp;
}
inline void ExitLine::set_allocated_e2(::serial::Point* e2) {
  delete e2_;
  e2_ = e2;
  if (e2) {
    set_has_e2();
  } else {
    clear_has_e2();
  }
}

// optional uint32 exit_id = 3;
inline bool ExitLine::has_exit_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ExitLine::set_has_exit_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ExitLine::clear_has_exit_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ExitLine::clear_exit_id() {
  exit_id_ = 0u;
  clear_has_exit_id();
}
inline ::google::protobuf::uint32 ExitLine::exit_id() const {
  return exit_id_;
}
inline void ExitLine::set_exit_id(::google::protobuf::uint32 value) {
  set_has_exit_id();
  exit_id_ = value;
}

// -------------------------------------------------------------------

// NodeMeta

// optional .serial.Boundary boundaries = 1;
inline bool NodeMeta::has_boundaries() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NodeMeta::set_has_boundaries() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NodeMeta::clear_has_boundaries() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NodeMeta::clear_boundaries() {
  if (boundaries_ != NULL) boundaries_->::serial::Boundary::Clear();
  clear_has_boundaries();
}
inline const ::serial::Boundary& NodeMeta::boundaries() const {
  return boundaries_ != NULL ? *boundaries_ : *default_instance_->boundaries_;
}
inline ::serial::Boundary* NodeMeta::mutable_boundaries() {
  set_has_boundaries();
  if (boundaries_ == NULL) boundaries_ = new ::serial::Boundary;
  return boundaries_;
}
inline ::serial::Boundary* NodeMeta::release_boundaries() {
  clear_has_boundaries();
  ::serial::Boundary* temp = boundaries_;
  boundaries_ = NULL;
  return temp;
}
inline void NodeMeta::set_allocated_boundaries(::serial::Boundary* boundaries) {
  delete boundaries_;
  boundaries_ = boundaries;
  if (boundaries) {
    set_has_boundaries();
  } else {
    clear_has_boundaries();
  }
}

// repeated .serial.ExitLine exit_lines = 2;
inline int NodeMeta::exit_lines_size() const {
  return exit_lines_.size();
}
inline void NodeMeta::clear_exit_lines() {
  exit_lines_.Clear();
}
inline const ::serial::ExitLine& NodeMeta::exit_lines(int index) const {
  return exit_lines_.Get(index);
}
inline ::serial::ExitLine* NodeMeta::mutable_exit_lines(int index) {
  return exit_lines_.Mutable(index);
}
inline ::serial::ExitLine* NodeMeta::add_exit_lines() {
  return exit_lines_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::serial::ExitLine >&
NodeMeta::exit_lines() const {
  return exit_lines_;
}
inline ::google::protobuf::RepeatedPtrField< ::serial::ExitLine >*
NodeMeta::mutable_exit_lines() {
  return &exit_lines_;
}

// optional string image_loc = 3;
inline bool NodeMeta::has_image_loc() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void NodeMeta::set_has_image_loc() {
  _has_bits_[0] |= 0x00000004u;
}
inline void NodeMeta::clear_has_image_loc() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void NodeMeta::clear_image_loc() {
  if (image_loc_ != &::google::protobuf::internal::kEmptyString) {
    image_loc_->clear();
  }
  clear_has_image_loc();
}
inline const ::std::string& NodeMeta::image_loc() const {
  return *image_loc_;
}
inline void NodeMeta::set_image_loc(const ::std::string& value) {
  set_has_image_loc();
  if (image_loc_ == &::google::protobuf::internal::kEmptyString) {
    image_loc_ = new ::std::string;
  }
  image_loc_->assign(value);
}
inline void NodeMeta::set_image_loc(const char* value) {
  set_has_image_loc();
  if (image_loc_ == &::google::protobuf::internal::kEmptyString) {
    image_loc_ = new ::std::string;
  }
  image_loc_->assign(value);
}
inline void NodeMeta::set_image_loc(const char* value, size_t size) {
  set_has_image_loc();
  if (image_loc_ == &::google::protobuf::internal::kEmptyString) {
    image_loc_ = new ::std::string;
  }
  image_loc_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* NodeMeta::mutable_image_loc() {
  set_has_image_loc();
  if (image_loc_ == &::google::protobuf::internal::kEmptyString) {
    image_loc_ = new ::std::string;
  }
  return image_loc_;
}
inline ::std::string* NodeMeta::release_image_loc() {
  clear_has_image_loc();
  if (image_loc_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = image_loc_;
    image_loc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void NodeMeta::set_allocated_image_loc(::std::string* image_loc) {
  if (image_loc_ != &::google::protobuf::internal::kEmptyString) {
    delete image_loc_;
  }
  if (image_loc) {
    set_has_image_loc();
    image_loc_ = image_loc;
  } else {
    clear_has_image_loc();
    image_loc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace serial

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_node_2eproto__INCLUDED
