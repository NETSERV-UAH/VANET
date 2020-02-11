//
// Generated file, do not edit! Created by nedtool 5.0 from src/veins/modules/messages/HelloMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HelloMessage_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(HelloMessage);

HelloMessage::HelloMessage(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->vehicleId = 0;
    this->messageId = 0;
    this->idleTime = 0;
    this->degree = 0;
    this->role = 0;
    this->averageSpeed = 0;
    this->creationTime = 0;
    this->qosValue = 0;
    this->clusterHeadId = 0;
}

HelloMessage::HelloMessage(const HelloMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

HelloMessage::~HelloMessage()
{
}

HelloMessage& HelloMessage::operator=(const HelloMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HelloMessage::copy(const HelloMessage& other)
{
    this->vehicleId = other.vehicleId;
    this->messageId = other.messageId;
    this->idleTime = other.idleTime;
    this->degree = other.degree;
    this->role = other.role;
    this->averageSpeed = other.averageSpeed;
    this->gpsPosition = other.gpsPosition;
    this->creationTime = other.creationTime;
    this->qosValue = other.qosValue;
    this->clusterHeadId = other.clusterHeadId;
}

void HelloMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->vehicleId);
    doParsimPacking(b,this->messageId);
    doParsimPacking(b,this->idleTime);
    doParsimPacking(b,this->degree);
    doParsimPacking(b,this->role);
    doParsimPacking(b,this->averageSpeed);
    doParsimPacking(b,this->gpsPosition);
    doParsimPacking(b,this->creationTime);
    doParsimPacking(b,this->qosValue);
    doParsimPacking(b,this->clusterHeadId);
}

void HelloMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleId);
    doParsimUnpacking(b,this->messageId);
    doParsimUnpacking(b,this->idleTime);
    doParsimUnpacking(b,this->degree);
    doParsimUnpacking(b,this->role);
    doParsimUnpacking(b,this->averageSpeed);
    doParsimUnpacking(b,this->gpsPosition);
    doParsimUnpacking(b,this->creationTime);
    doParsimUnpacking(b,this->qosValue);
    doParsimUnpacking(b,this->clusterHeadId);
}

int HelloMessage::getVehicleId() const
{
    return this->vehicleId;
}

void HelloMessage::setVehicleId(int vehicleId)
{
    this->vehicleId = vehicleId;
}

int HelloMessage::getMessageId() const
{
    return this->messageId;
}

void HelloMessage::setMessageId(int messageId)
{
    this->messageId = messageId;
}

::omnetpp::simtime_t HelloMessage::getIdleTime() const
{
    return this->idleTime;
}

void HelloMessage::setIdleTime(::omnetpp::simtime_t idleTime)
{
    this->idleTime = idleTime;
}

double HelloMessage::getDegree() const
{
    return this->degree;
}

void HelloMessage::setDegree(double degree)
{
    this->degree = degree;
}

double HelloMessage::getRole() const
{
    return this->role;
}

void HelloMessage::setRole(double role)
{
    this->role = role;
}

double HelloMessage::getAverageSpeed() const
{
    return this->averageSpeed;
}

void HelloMessage::setAverageSpeed(double averageSpeed)
{
    this->averageSpeed = averageSpeed;
}

Coord& HelloMessage::getGpsPosition()
{
    return this->gpsPosition;
}

void HelloMessage::setGpsPosition(const Coord& gpsPosition)
{
    this->gpsPosition = gpsPosition;
}

::omnetpp::simtime_t HelloMessage::getCreationTime() const
{
    return this->creationTime;
}

void HelloMessage::setCreationTime(::omnetpp::simtime_t creationTime)
{
    this->creationTime = creationTime;
}

double HelloMessage::getQosValue() const
{
    return this->qosValue;
}

void HelloMessage::setQosValue(double qosValue)
{
    this->qosValue = qosValue;
}

int HelloMessage::getClusterHeadId() const
{
    return this->clusterHeadId;
}

void HelloMessage::setClusterHeadId(int clusterHeadId)
{
    this->clusterHeadId = clusterHeadId;
}

class HelloMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    HelloMessageDescriptor();
    virtual ~HelloMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(HelloMessageDescriptor);

HelloMessageDescriptor::HelloMessageDescriptor() : omnetpp::cClassDescriptor("HelloMessage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

HelloMessageDescriptor::~HelloMessageDescriptor()
{
    delete[] propertynames;
}

bool HelloMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HelloMessage *>(obj)!=nullptr;
}

const char **HelloMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *HelloMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int HelloMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount() : 10;
}

unsigned int HelloMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *HelloMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleId",
        "messageId",
        "idleTime",
        "degree",
        "role",
        "averageSpeed",
        "gpsPosition",
        "creationTime",
        "qosValue",
        "clusterHeadId",
    };
    return (field>=0 && field<10) ? fieldNames[field] : nullptr;
}

int HelloMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "vehicleId")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageId")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "idleTime")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "degree")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "role")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "averageSpeed")==0) return base+5;
    if (fieldName[0]=='g' && strcmp(fieldName, "gpsPosition")==0) return base+6;
    if (fieldName[0]=='c' && strcmp(fieldName, "creationTime")==0) return base+7;
    if (fieldName[0]=='q' && strcmp(fieldName, "qosValue")==0) return base+8;
    if (fieldName[0]=='c' && strcmp(fieldName, "clusterHeadId")==0) return base+9;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *HelloMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "simtime_t",
        "double",
        "double",
        "double",
        "Coord",
        "simtime_t",
        "double",
        "int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : nullptr;
}

const char **HelloMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *HelloMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int HelloMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    HelloMessage *pp = (HelloMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string HelloMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    HelloMessage *pp = (HelloMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVehicleId());
        case 1: return long2string(pp->getMessageId());
        case 2: return simtime2string(pp->getIdleTime());
        case 3: return double2string(pp->getDegree());
        case 4: return double2string(pp->getRole());
        case 5: return double2string(pp->getAverageSpeed());
        case 6: {std::stringstream out; out << pp->getGpsPosition(); return out.str();}
        case 7: return simtime2string(pp->getCreationTime());
        case 8: return double2string(pp->getQosValue());
        case 9: return long2string(pp->getClusterHeadId());
        default: return "";
    }
}

bool HelloMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    HelloMessage *pp = (HelloMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setVehicleId(string2long(value)); return true;
        case 1: pp->setMessageId(string2long(value)); return true;
        case 2: pp->setIdleTime(string2simtime(value)); return true;
        case 3: pp->setDegree(string2double(value)); return true;
        case 4: pp->setRole(string2double(value)); return true;
        case 5: pp->setAverageSpeed(string2double(value)); return true;
        case 7: pp->setCreationTime(string2simtime(value)); return true;
        case 8: pp->setQosValue(string2double(value)); return true;
        case 9: pp->setClusterHeadId(string2long(value)); return true;
        default: return false;
    }
}

const char *HelloMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 6: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *HelloMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    HelloMessage *pp = (HelloMessage *)object; (void)pp;
    switch (field) {
        case 6: return (void *)(&pp->getGpsPosition()); break;
        default: return nullptr;
    }
}


