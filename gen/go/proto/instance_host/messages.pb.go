// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.36.4
// 	protoc        (unknown)
// source: proto/instance_host/messages.proto

package instance_host

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	_ "google.golang.org/protobuf/types/known/anypb"
	reflect "reflect"
	sync "sync"
	unsafe "unsafe"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type Action struct {
	state         protoimpl.MessageState `protogen:"open.v1"`
	ObjectId      uint64                 `protobuf:"varint,1,opt,name=object_id,json=objectId,proto3" json:"object_id,omitempty"`
	Action        string                 `protobuf:"bytes,2,opt,name=action,proto3" json:"action,omitempty"`
	Args          []uint64               `protobuf:"varint,3,rep,packed,name=args,proto3" json:"args,omitempty"`
	unknownFields protoimpl.UnknownFields
	sizeCache     protoimpl.SizeCache
}

func (x *Action) Reset() {
	*x = Action{}
	mi := &file_proto_instance_host_messages_proto_msgTypes[0]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *Action) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*Action) ProtoMessage() {}

func (x *Action) ProtoReflect() protoreflect.Message {
	mi := &file_proto_instance_host_messages_proto_msgTypes[0]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use Action.ProtoReflect.Descriptor instead.
func (*Action) Descriptor() ([]byte, []int) {
	return file_proto_instance_host_messages_proto_rawDescGZIP(), []int{0}
}

func (x *Action) GetObjectId() uint64 {
	if x != nil {
		return x.ObjectId
	}
	return 0
}

func (x *Action) GetAction() string {
	if x != nil {
		return x.Action
	}
	return ""
}

func (x *Action) GetArgs() []uint64 {
	if x != nil {
		return x.Args
	}
	return nil
}

type Actions struct {
	state         protoimpl.MessageState `protogen:"open.v1"`
	Actions       []*Action              `protobuf:"bytes,1,rep,name=actions,proto3" json:"actions,omitempty"`
	unknownFields protoimpl.UnknownFields
	sizeCache     protoimpl.SizeCache
}

func (x *Actions) Reset() {
	*x = Actions{}
	mi := &file_proto_instance_host_messages_proto_msgTypes[1]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *Actions) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*Actions) ProtoMessage() {}

func (x *Actions) ProtoReflect() protoreflect.Message {
	mi := &file_proto_instance_host_messages_proto_msgTypes[1]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use Actions.ProtoReflect.Descriptor instead.
func (*Actions) Descriptor() ([]byte, []int) {
	return file_proto_instance_host_messages_proto_rawDescGZIP(), []int{1}
}

func (x *Actions) GetActions() []*Action {
	if x != nil {
		return x.Actions
	}
	return nil
}

type CreateInstanceRequest struct {
	state         protoimpl.MessageState `protogen:"open.v1"`
	InstanceType  string                 `protobuf:"bytes,1,opt,name=instance_type,json=instanceType,proto3" json:"instance_type,omitempty"`
	UserIds       []string               `protobuf:"bytes,2,rep,name=user_ids,json=userIds,proto3" json:"user_ids,omitempty"`
	unknownFields protoimpl.UnknownFields
	sizeCache     protoimpl.SizeCache
}

func (x *CreateInstanceRequest) Reset() {
	*x = CreateInstanceRequest{}
	mi := &file_proto_instance_host_messages_proto_msgTypes[2]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *CreateInstanceRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*CreateInstanceRequest) ProtoMessage() {}

func (x *CreateInstanceRequest) ProtoReflect() protoreflect.Message {
	mi := &file_proto_instance_host_messages_proto_msgTypes[2]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use CreateInstanceRequest.ProtoReflect.Descriptor instead.
func (*CreateInstanceRequest) Descriptor() ([]byte, []int) {
	return file_proto_instance_host_messages_proto_rawDescGZIP(), []int{2}
}

func (x *CreateInstanceRequest) GetInstanceType() string {
	if x != nil {
		return x.InstanceType
	}
	return ""
}

func (x *CreateInstanceRequest) GetUserIds() []string {
	if x != nil {
		return x.UserIds
	}
	return nil
}

type CreateInstanceResponse struct {
	state         protoimpl.MessageState `protogen:"open.v1"`
	InstanceId    string                 `protobuf:"bytes,1,opt,name=instance_id,json=instanceId,proto3" json:"instance_id,omitempty"`
	Markup        map[string]string      `protobuf:"bytes,2,rep,name=markup,proto3" json:"markup,omitempty" protobuf_key:"bytes,1,opt,name=key" protobuf_val:"bytes,2,opt,name=value"`
	Actions       map[string]*Actions    `protobuf:"bytes,3,rep,name=actions,proto3" json:"actions,omitempty" protobuf_key:"bytes,1,opt,name=key" protobuf_val:"bytes,2,opt,name=value"`
	unknownFields protoimpl.UnknownFields
	sizeCache     protoimpl.SizeCache
}

func (x *CreateInstanceResponse) Reset() {
	*x = CreateInstanceResponse{}
	mi := &file_proto_instance_host_messages_proto_msgTypes[3]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *CreateInstanceResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*CreateInstanceResponse) ProtoMessage() {}

func (x *CreateInstanceResponse) ProtoReflect() protoreflect.Message {
	mi := &file_proto_instance_host_messages_proto_msgTypes[3]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use CreateInstanceResponse.ProtoReflect.Descriptor instead.
func (*CreateInstanceResponse) Descriptor() ([]byte, []int) {
	return file_proto_instance_host_messages_proto_rawDescGZIP(), []int{3}
}

func (x *CreateInstanceResponse) GetInstanceId() string {
	if x != nil {
		return x.InstanceId
	}
	return ""
}

func (x *CreateInstanceResponse) GetMarkup() map[string]string {
	if x != nil {
		return x.Markup
	}
	return nil
}

func (x *CreateInstanceResponse) GetActions() map[string]*Actions {
	if x != nil {
		return x.Actions
	}
	return nil
}

type PerformActionRequest struct {
	state         protoimpl.MessageState `protogen:"open.v1"`
	InstanceId    string                 `protobuf:"bytes,1,opt,name=instance_id,json=instanceId,proto3" json:"instance_id,omitempty"`
	UserId        string                 `protobuf:"bytes,2,opt,name=user_id,json=userId,proto3" json:"user_id,omitempty"`
	Action        *Action                `protobuf:"bytes,3,opt,name=action,proto3" json:"action,omitempty"`
	unknownFields protoimpl.UnknownFields
	sizeCache     protoimpl.SizeCache
}

func (x *PerformActionRequest) Reset() {
	*x = PerformActionRequest{}
	mi := &file_proto_instance_host_messages_proto_msgTypes[4]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *PerformActionRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PerformActionRequest) ProtoMessage() {}

func (x *PerformActionRequest) ProtoReflect() protoreflect.Message {
	mi := &file_proto_instance_host_messages_proto_msgTypes[4]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PerformActionRequest.ProtoReflect.Descriptor instead.
func (*PerformActionRequest) Descriptor() ([]byte, []int) {
	return file_proto_instance_host_messages_proto_rawDescGZIP(), []int{4}
}

func (x *PerformActionRequest) GetInstanceId() string {
	if x != nil {
		return x.InstanceId
	}
	return ""
}

func (x *PerformActionRequest) GetUserId() string {
	if x != nil {
		return x.UserId
	}
	return ""
}

func (x *PerformActionRequest) GetAction() *Action {
	if x != nil {
		return x.Action
	}
	return nil
}

type PerformActionResponse struct {
	state         protoimpl.MessageState `protogen:"open.v1"`
	Markup        map[string]string      `protobuf:"bytes,1,rep,name=markup,proto3" json:"markup,omitempty" protobuf_key:"bytes,1,opt,name=key" protobuf_val:"bytes,2,opt,name=value"`
	Actions       map[string]*Actions    `protobuf:"bytes,2,rep,name=actions,proto3" json:"actions,omitempty" protobuf_key:"bytes,1,opt,name=key" protobuf_val:"bytes,2,opt,name=value"`
	unknownFields protoimpl.UnknownFields
	sizeCache     protoimpl.SizeCache
}

func (x *PerformActionResponse) Reset() {
	*x = PerformActionResponse{}
	mi := &file_proto_instance_host_messages_proto_msgTypes[5]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *PerformActionResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PerformActionResponse) ProtoMessage() {}

func (x *PerformActionResponse) ProtoReflect() protoreflect.Message {
	mi := &file_proto_instance_host_messages_proto_msgTypes[5]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PerformActionResponse.ProtoReflect.Descriptor instead.
func (*PerformActionResponse) Descriptor() ([]byte, []int) {
	return file_proto_instance_host_messages_proto_rawDescGZIP(), []int{5}
}

func (x *PerformActionResponse) GetMarkup() map[string]string {
	if x != nil {
		return x.Markup
	}
	return nil
}

func (x *PerformActionResponse) GetActions() map[string]*Actions {
	if x != nil {
		return x.Actions
	}
	return nil
}

var File_proto_instance_host_messages_proto protoreflect.FileDescriptor

var file_proto_instance_host_messages_proto_rawDesc = string([]byte{
	0x0a, 0x22, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x2f, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65,
	0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2f, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x73, 0x2e, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x12, 0x1c, 0x73, 0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74,
	0x5f, 0x61, 0x70, 0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f,
	0x73, 0x74, 0x1a, 0x19, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x62, 0x75, 0x66, 0x2f, 0x61, 0x6e, 0x79, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x22, 0x51, 0x0a,
	0x06, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x12, 0x1b, 0x0a, 0x09, 0x6f, 0x62, 0x6a, 0x65, 0x63,
	0x74, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01, 0x28, 0x04, 0x52, 0x08, 0x6f, 0x62, 0x6a, 0x65,
	0x63, 0x74, 0x49, 0x64, 0x12, 0x16, 0x0a, 0x06, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x18, 0x02,
	0x20, 0x01, 0x28, 0x09, 0x52, 0x06, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x12, 0x12, 0x0a, 0x04,
	0x61, 0x72, 0x67, 0x73, 0x18, 0x03, 0x20, 0x03, 0x28, 0x04, 0x52, 0x04, 0x61, 0x72, 0x67, 0x73,
	0x22, 0x49, 0x0a, 0x07, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x12, 0x3e, 0x0a, 0x07, 0x61,
	0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x18, 0x01, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x24, 0x2e, 0x73,
	0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61, 0x70, 0x69, 0x2e, 0x69, 0x6e,
	0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2e, 0x41, 0x63, 0x74, 0x69,
	0x6f, 0x6e, 0x52, 0x07, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x22, 0x57, 0x0a, 0x15, 0x43,
	0x72, 0x65, 0x61, 0x74, 0x65, 0x49, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x52, 0x65, 0x71,
	0x75, 0x65, 0x73, 0x74, 0x12, 0x23, 0x0a, 0x0d, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65,
	0x5f, 0x74, 0x79, 0x70, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x0c, 0x69, 0x6e, 0x73,
	0x74, 0x61, 0x6e, 0x63, 0x65, 0x54, 0x79, 0x70, 0x65, 0x12, 0x19, 0x0a, 0x08, 0x75, 0x73, 0x65,
	0x72, 0x5f, 0x69, 0x64, 0x73, 0x18, 0x02, 0x20, 0x03, 0x28, 0x09, 0x52, 0x07, 0x75, 0x73, 0x65,
	0x72, 0x49, 0x64, 0x73, 0x22, 0x8e, 0x03, 0x0a, 0x16, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x49,
	0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x12,
	0x1f, 0x0a, 0x0b, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x69, 0x64, 0x18, 0x01,
	0x20, 0x01, 0x28, 0x09, 0x52, 0x0a, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x49, 0x64,
	0x12, 0x58, 0x0a, 0x06, 0x6d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x18, 0x02, 0x20, 0x03, 0x28, 0x0b,
	0x32, 0x40, 0x2e, 0x73, 0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61, 0x70,
	0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2e,
	0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x49, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x52, 0x65,
	0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x2e, 0x4d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x45, 0x6e, 0x74,
	0x72, 0x79, 0x52, 0x06, 0x6d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x12, 0x5b, 0x0a, 0x07, 0x61, 0x63,
	0x74, 0x69, 0x6f, 0x6e, 0x73, 0x18, 0x03, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x41, 0x2e, 0x73, 0x70,
	0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61, 0x70, 0x69, 0x2e, 0x69, 0x6e, 0x73,
	0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2e, 0x43, 0x72, 0x65, 0x61, 0x74,
	0x65, 0x49, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73,
	0x65, 0x2e, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x45, 0x6e, 0x74, 0x72, 0x79, 0x52, 0x07,
	0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x1a, 0x39, 0x0a, 0x0b, 0x4d, 0x61, 0x72, 0x6b, 0x75,
	0x70, 0x45, 0x6e, 0x74, 0x72, 0x79, 0x12, 0x10, 0x0a, 0x03, 0x6b, 0x65, 0x79, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x03, 0x6b, 0x65, 0x79, 0x12, 0x14, 0x0a, 0x05, 0x76, 0x61, 0x6c, 0x75,
	0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3a, 0x02,
	0x38, 0x01, 0x1a, 0x61, 0x0a, 0x0c, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x45, 0x6e, 0x74,
	0x72, 0x79, 0x12, 0x10, 0x0a, 0x03, 0x6b, 0x65, 0x79, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52,
	0x03, 0x6b, 0x65, 0x79, 0x12, 0x3b, 0x0a, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x18, 0x02, 0x20,
	0x01, 0x28, 0x0b, 0x32, 0x25, 0x2e, 0x73, 0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74,
	0x5f, 0x61, 0x70, 0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f,
	0x73, 0x74, 0x2e, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75,
	0x65, 0x3a, 0x02, 0x38, 0x01, 0x22, 0x8e, 0x01, 0x0a, 0x14, 0x50, 0x65, 0x72, 0x66, 0x6f, 0x72,
	0x6d, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x12, 0x1f,
	0x0a, 0x0b, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x0a, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x49, 0x64, 0x12,
	0x17, 0x0a, 0x07, 0x75, 0x73, 0x65, 0x72, 0x5f, 0x69, 0x64, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09,
	0x52, 0x06, 0x75, 0x73, 0x65, 0x72, 0x49, 0x64, 0x12, 0x3c, 0x0a, 0x06, 0x61, 0x63, 0x74, 0x69,
	0x6f, 0x6e, 0x18, 0x03, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x24, 0x2e, 0x73, 0x70, 0x69, 0x65, 0x6c,
	0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61, 0x70, 0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e,
	0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2e, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x52, 0x06,
	0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x22, 0xea, 0x02, 0x0a, 0x15, 0x50, 0x65, 0x72, 0x66, 0x6f,
	0x72, 0x6d, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65,
	0x12, 0x57, 0x0a, 0x06, 0x6d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x18, 0x01, 0x20, 0x03, 0x28, 0x0b,
	0x32, 0x3f, 0x2e, 0x73, 0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61, 0x70,
	0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2e,
	0x50, 0x65, 0x72, 0x66, 0x6f, 0x72, 0x6d, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x52, 0x65, 0x73,
	0x70, 0x6f, 0x6e, 0x73, 0x65, 0x2e, 0x4d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x45, 0x6e, 0x74, 0x72,
	0x79, 0x52, 0x06, 0x6d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x12, 0x5a, 0x0a, 0x07, 0x61, 0x63, 0x74,
	0x69, 0x6f, 0x6e, 0x73, 0x18, 0x02, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x40, 0x2e, 0x73, 0x70, 0x69,
	0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61, 0x70, 0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74,
	0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74, 0x2e, 0x50, 0x65, 0x72, 0x66, 0x6f, 0x72,
	0x6d, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x2e,
	0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x45, 0x6e, 0x74, 0x72, 0x79, 0x52, 0x07, 0x61, 0x63,
	0x74, 0x69, 0x6f, 0x6e, 0x73, 0x1a, 0x39, 0x0a, 0x0b, 0x4d, 0x61, 0x72, 0x6b, 0x75, 0x70, 0x45,
	0x6e, 0x74, 0x72, 0x79, 0x12, 0x10, 0x0a, 0x03, 0x6b, 0x65, 0x79, 0x18, 0x01, 0x20, 0x01, 0x28,
	0x09, 0x52, 0x03, 0x6b, 0x65, 0x79, 0x12, 0x14, 0x0a, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x18,
	0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3a, 0x02, 0x38, 0x01,
	0x1a, 0x61, 0x0a, 0x0c, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x45, 0x6e, 0x74, 0x72, 0x79,
	0x12, 0x10, 0x0a, 0x03, 0x6b, 0x65, 0x79, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x03, 0x6b,
	0x65, 0x79, 0x12, 0x3b, 0x0a, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28,
	0x0b, 0x32, 0x25, 0x2e, 0x73, 0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x5f, 0x61,
	0x70, 0x69, 0x2e, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f, 0x73, 0x74,
	0x2e, 0x41, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3a,
	0x02, 0x38, 0x01, 0x42, 0x3d, 0x5a, 0x3b, 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x2e, 0x63, 0x6f,
	0x6d, 0x2f, 0x73, 0x70, 0x69, 0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x2f, 0x73, 0x70, 0x69,
	0x65, 0x6c, 0x62, 0x72, 0x65, 0x74, 0x74, 0x2f, 0x67, 0x65, 0x6e, 0x2f, 0x67, 0x6f, 0x2f, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x2f, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x68, 0x6f,
	0x73, 0x74, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
})

var (
	file_proto_instance_host_messages_proto_rawDescOnce sync.Once
	file_proto_instance_host_messages_proto_rawDescData []byte
)

func file_proto_instance_host_messages_proto_rawDescGZIP() []byte {
	file_proto_instance_host_messages_proto_rawDescOnce.Do(func() {
		file_proto_instance_host_messages_proto_rawDescData = protoimpl.X.CompressGZIP(unsafe.Slice(unsafe.StringData(file_proto_instance_host_messages_proto_rawDesc), len(file_proto_instance_host_messages_proto_rawDesc)))
	})
	return file_proto_instance_host_messages_proto_rawDescData
}

var file_proto_instance_host_messages_proto_msgTypes = make([]protoimpl.MessageInfo, 10)
var file_proto_instance_host_messages_proto_goTypes = []any{
	(*Action)(nil),                 // 0: spielbrett_api.instance_host.Action
	(*Actions)(nil),                // 1: spielbrett_api.instance_host.Actions
	(*CreateInstanceRequest)(nil),  // 2: spielbrett_api.instance_host.CreateInstanceRequest
	(*CreateInstanceResponse)(nil), // 3: spielbrett_api.instance_host.CreateInstanceResponse
	(*PerformActionRequest)(nil),   // 4: spielbrett_api.instance_host.PerformActionRequest
	(*PerformActionResponse)(nil),  // 5: spielbrett_api.instance_host.PerformActionResponse
	nil,                            // 6: spielbrett_api.instance_host.CreateInstanceResponse.MarkupEntry
	nil,                            // 7: spielbrett_api.instance_host.CreateInstanceResponse.ActionsEntry
	nil,                            // 8: spielbrett_api.instance_host.PerformActionResponse.MarkupEntry
	nil,                            // 9: spielbrett_api.instance_host.PerformActionResponse.ActionsEntry
}
var file_proto_instance_host_messages_proto_depIdxs = []int32{
	0, // 0: spielbrett_api.instance_host.Actions.actions:type_name -> spielbrett_api.instance_host.Action
	6, // 1: spielbrett_api.instance_host.CreateInstanceResponse.markup:type_name -> spielbrett_api.instance_host.CreateInstanceResponse.MarkupEntry
	7, // 2: spielbrett_api.instance_host.CreateInstanceResponse.actions:type_name -> spielbrett_api.instance_host.CreateInstanceResponse.ActionsEntry
	0, // 3: spielbrett_api.instance_host.PerformActionRequest.action:type_name -> spielbrett_api.instance_host.Action
	8, // 4: spielbrett_api.instance_host.PerformActionResponse.markup:type_name -> spielbrett_api.instance_host.PerformActionResponse.MarkupEntry
	9, // 5: spielbrett_api.instance_host.PerformActionResponse.actions:type_name -> spielbrett_api.instance_host.PerformActionResponse.ActionsEntry
	1, // 6: spielbrett_api.instance_host.CreateInstanceResponse.ActionsEntry.value:type_name -> spielbrett_api.instance_host.Actions
	1, // 7: spielbrett_api.instance_host.PerformActionResponse.ActionsEntry.value:type_name -> spielbrett_api.instance_host.Actions
	8, // [8:8] is the sub-list for method output_type
	8, // [8:8] is the sub-list for method input_type
	8, // [8:8] is the sub-list for extension type_name
	8, // [8:8] is the sub-list for extension extendee
	0, // [0:8] is the sub-list for field type_name
}

func init() { file_proto_instance_host_messages_proto_init() }
func file_proto_instance_host_messages_proto_init() {
	if File_proto_instance_host_messages_proto != nil {
		return
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: unsafe.Slice(unsafe.StringData(file_proto_instance_host_messages_proto_rawDesc), len(file_proto_instance_host_messages_proto_rawDesc)),
			NumEnums:      0,
			NumMessages:   10,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_proto_instance_host_messages_proto_goTypes,
		DependencyIndexes: file_proto_instance_host_messages_proto_depIdxs,
		MessageInfos:      file_proto_instance_host_messages_proto_msgTypes,
	}.Build()
	File_proto_instance_host_messages_proto = out.File
	file_proto_instance_host_messages_proto_goTypes = nil
	file_proto_instance_host_messages_proto_depIdxs = nil
}
