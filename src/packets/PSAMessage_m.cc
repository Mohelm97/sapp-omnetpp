//
// Generated file, do not edit! Created by opp_msgtool 6.1 from packets/PSAMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "PSAMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Enum(PSAMessageType, (PSAMessageType::Subscription, PSAMessageType::Publication, PSAMessageType::Acking));

Register_Class(PSAMessage)

PSAMessage::PSAMessage() : ::inet::FieldsChunk()
{
    this->setChunkLength(inet::B(6));

}

PSAMessage::PSAMessage(const PSAMessage& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

PSAMessage::~PSAMessage()
{
    delete [] this->pathHops;
}

PSAMessage& PSAMessage::operator=(const PSAMessage& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void PSAMessage::copy(const PSAMessage& other)
{
    this->hopCount = other.hopCount;
    this->nonce = other.nonce;
    this->type = other.type;
    this->needAcking = other.needAcking;
    this->topic = other.topic;
    this->sourceNodeName = other.sourceNodeName;
    delete [] this->pathHops;
    this->pathHops = (other.pathHops_arraysize==0) ? nullptr : new inet::MacAddress[other.pathHops_arraysize];
    pathHops_arraysize = other.pathHops_arraysize;
    for (size_t i = 0; i < pathHops_arraysize; i++) {
        this->pathHops[i] = other.pathHops[i];
    }
}

void PSAMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->nonce);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->needAcking);
    doParsimPacking(b,this->topic);
    doParsimPacking(b,this->sourceNodeName);
    b->pack(pathHops_arraysize);
    doParsimArrayPacking(b,this->pathHops,pathHops_arraysize);
}

void PSAMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->nonce);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->needAcking);
    doParsimUnpacking(b,this->topic);
    doParsimUnpacking(b,this->sourceNodeName);
    delete [] this->pathHops;
    b->unpack(pathHops_arraysize);
    if (pathHops_arraysize == 0) {
        this->pathHops = nullptr;
    } else {
        this->pathHops = new inet::MacAddress[pathHops_arraysize];
        doParsimArrayUnpacking(b,this->pathHops,pathHops_arraysize);
    }
}

uint8_t PSAMessage::getHopCount() const
{
    return this->hopCount;
}

void PSAMessage::setHopCount(uint8_t hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

uint32_t PSAMessage::getNonce() const
{
    return this->nonce;
}

void PSAMessage::setNonce(uint32_t nonce)
{
    handleChange();
    this->nonce = nonce;
}

PSAMessageType PSAMessage::getType() const
{
    return this->type;
}

void PSAMessage::setType(PSAMessageType type)
{
    handleChange();
    this->type = type;
}

bool PSAMessage::getNeedAcking() const
{
    return this->needAcking;
}

void PSAMessage::setNeedAcking(bool needAcking)
{
    handleChange();
    this->needAcking = needAcking;
}

const char * PSAMessage::getTopic() const
{
    return this->topic.c_str();
}

void PSAMessage::setTopic(const char * topic)
{
    handleChange();
    this->topic = topic;
}

const char * PSAMessage::getSourceNodeName() const
{
    return this->sourceNodeName.c_str();
}

void PSAMessage::setSourceNodeName(const char * sourceNodeName)
{
    handleChange();
    this->sourceNodeName = sourceNodeName;
}

size_t PSAMessage::getPathHopsArraySize() const
{
    return pathHops_arraysize;
}

const inet::MacAddress& PSAMessage::getPathHops(size_t k) const
{
    if (k >= pathHops_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathHops_arraysize, (unsigned long)k);
    return this->pathHops[k];
}

void PSAMessage::setPathHopsArraySize(size_t newSize)
{
    handleChange();
    inet::MacAddress *pathHops2 = (newSize==0) ? nullptr : new inet::MacAddress[newSize];
    size_t minSize = pathHops_arraysize < newSize ? pathHops_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        pathHops2[i] = this->pathHops[i];
    delete [] this->pathHops;
    this->pathHops = pathHops2;
    pathHops_arraysize = newSize;
}

void PSAMessage::setPathHops(size_t k, const inet::MacAddress& pathHops)
{
    if (k >= pathHops_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathHops_arraysize, (unsigned long)k);
    handleChange();
    this->pathHops[k] = pathHops;
}

void PSAMessage::insertPathHops(size_t k, const inet::MacAddress& pathHops)
{
    if (k > pathHops_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathHops_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = pathHops_arraysize + 1;
    inet::MacAddress *pathHops2 = new inet::MacAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        pathHops2[i] = this->pathHops[i];
    pathHops2[k] = pathHops;
    for (i = k + 1; i < newSize; i++)
        pathHops2[i] = this->pathHops[i-1];
    delete [] this->pathHops;
    this->pathHops = pathHops2;
    pathHops_arraysize = newSize;
}

void PSAMessage::appendPathHops(const inet::MacAddress& pathHops)
{
    insertPathHops(pathHops_arraysize, pathHops);
}

void PSAMessage::erasePathHops(size_t k)
{
    if (k >= pathHops_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathHops_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = pathHops_arraysize - 1;
    inet::MacAddress *pathHops2 = (newSize == 0) ? nullptr : new inet::MacAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        pathHops2[i] = this->pathHops[i];
    for (i = k; i < newSize; i++)
        pathHops2[i] = this->pathHops[i+1];
    delete [] this->pathHops;
    this->pathHops = pathHops2;
    pathHops_arraysize = newSize;
}

class PSAMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_nonce,
        FIELD_type,
        FIELD_needAcking,
        FIELD_topic,
        FIELD_sourceNodeName,
        FIELD_pathHops,
    };
  public:
    PSAMessageDescriptor();
    virtual ~PSAMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PSAMessageDescriptor)

PSAMessageDescriptor::PSAMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PSAMessage)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

PSAMessageDescriptor::~PSAMessageDescriptor()
{
    delete[] propertyNames;
}

bool PSAMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PSAMessage *>(obj)!=nullptr;
}

const char **PSAMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PSAMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PSAMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int PSAMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_nonce
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_needAcking
        FD_ISEDITABLE,    // FIELD_topic
        FD_ISEDITABLE,    // FIELD_sourceNodeName
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_pathHops
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *PSAMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "nonce",
        "type",
        "needAcking",
        "topic",
        "sourceNodeName",
        "pathHops",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int PSAMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "nonce") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "needAcking") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "topic") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "sourceNodeName") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "pathHops") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *PSAMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_hopCount
        "uint32_t",    // FIELD_nonce
        "PSAMessageType",    // FIELD_type
        "bool",    // FIELD_needAcking
        "string",    // FIELD_topic
        "string",    // FIELD_sourceNodeName
        "inet::MacAddress",    // FIELD_pathHops
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **PSAMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PSAMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "PSAMessageType";
            return nullptr;
        default: return nullptr;
    }
}

int PSAMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_pathHops: return pp->getPathHopsArraySize();
        default: return 0;
    }
}

void PSAMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_pathHops: pp->setPathHopsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PSAMessage'", field);
    }
}

const char *PSAMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PSAMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_nonce: return ulong2string(pp->getNonce());
        case FIELD_type: return enum2string(pp->getType(), "PSAMessageType");
        case FIELD_needAcking: return bool2string(pp->getNeedAcking());
        case FIELD_topic: return oppstring2string(pp->getTopic());
        case FIELD_sourceNodeName: return oppstring2string(pp->getSourceNodeName());
        case FIELD_pathHops: return pp->getPathHops(i).str();
        default: return "";
    }
}

void PSAMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); break;
        case FIELD_nonce: pp->setNonce(string2ulong(value)); break;
        case FIELD_needAcking: pp->setNeedAcking(string2bool(value)); break;
        case FIELD_topic: pp->setTopic((value)); break;
        case FIELD_sourceNodeName: pp->setSourceNodeName((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PSAMessage'", field);
    }
}

omnetpp::cValue PSAMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: return (omnetpp::intval_t)(pp->getHopCount());
        case FIELD_nonce: return (omnetpp::intval_t)(pp->getNonce());
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_needAcking: return pp->getNeedAcking();
        case FIELD_topic: return pp->getTopic();
        case FIELD_sourceNodeName: return pp->getSourceNodeName();
        case FIELD_pathHops: return omnetpp::toAnyPtr(&pp->getPathHops(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PSAMessage' as cValue -- field index out of range?", field);
    }
}

void PSAMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_nonce: pp->setNonce(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_needAcking: pp->setNeedAcking(value.boolValue()); break;
        case FIELD_topic: pp->setTopic(value.stringValue()); break;
        case FIELD_sourceNodeName: pp->setSourceNodeName(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PSAMessage'", field);
    }
}

const char *PSAMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PSAMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        case FIELD_pathHops: return omnetpp::toAnyPtr(&pp->getPathHops(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PSAMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PSAMessage *pp = omnetpp::fromAnyPtr<PSAMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PSAMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

