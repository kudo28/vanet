//
// Generated file, do not edit! Created by nedtool 5.0 from messages/Car2XMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Car2XMessage_m.h"

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

Register_Class(Car2XMessage);

Car2XMessage::Car2XMessage(const char *name, int kind) : ::WaveShortMessage(name,kind)
{
    this->creationTime = 0;
    this->hops = 0;
    this->unique_id = 0;
    this->monitorMsg = false;
    this->maxTravelledDistance = 0;
    this->virus = false;
}

Car2XMessage::Car2XMessage(const Car2XMessage& other) : ::WaveShortMessage(other)
{
    copy(other);
}

Car2XMessage::~Car2XMessage()
{
}

Car2XMessage& Car2XMessage::operator=(const Car2XMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void Car2XMessage::copy(const Car2XMessage& other)
{
    this->creationTime = other.creationTime;
    this->originPosition = other.originPosition;
    this->hops = other.hops;
    this->unique_id = other.unique_id;
    this->monitorMsg = other.monitorMsg;
    this->maxTravelledDistance = other.maxTravelledDistance;
    this->virus = other.virus;
}

void Car2XMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->creationTime);
    doParsimPacking(b,this->originPosition);
    doParsimPacking(b,this->hops);
    doParsimPacking(b,this->unique_id);
    doParsimPacking(b,this->monitorMsg);
    doParsimPacking(b,this->maxTravelledDistance);
    doParsimPacking(b,this->virus);
}

void Car2XMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->creationTime);
    doParsimUnpacking(b,this->originPosition);
    doParsimUnpacking(b,this->hops);
    doParsimUnpacking(b,this->unique_id);
    doParsimUnpacking(b,this->monitorMsg);
    doParsimUnpacking(b,this->maxTravelledDistance);
    doParsimUnpacking(b,this->virus);
}

::omnetpp::simtime_t Car2XMessage::getCreationTime() const
{
    return this->creationTime;
}

void Car2XMessage::setCreationTime(::omnetpp::simtime_t creationTime)
{
    this->creationTime = creationTime;
}

Coord& Car2XMessage::getOriginPosition()
{
    return this->originPosition;
}

void Car2XMessage::setOriginPosition(const Coord& originPosition)
{
    this->originPosition = originPosition;
}

int Car2XMessage::getHops() const
{
    return this->hops;
}

void Car2XMessage::setHops(int hops)
{
    this->hops = hops;
}

unsigned long Car2XMessage::getUnique_id() const
{
    return this->unique_id;
}

void Car2XMessage::setUnique_id(unsigned long unique_id)
{
    this->unique_id = unique_id;
}

bool Car2XMessage::getMonitorMsg() const
{
    return this->monitorMsg;
}

void Car2XMessage::setMonitorMsg(bool monitorMsg)
{
    this->monitorMsg = monitorMsg;
}

double Car2XMessage::getMaxTravelledDistance() const
{
    return this->maxTravelledDistance;
}

void Car2XMessage::setMaxTravelledDistance(double maxTravelledDistance)
{
    this->maxTravelledDistance = maxTravelledDistance;
}

bool Car2XMessage::getVirus() const
{
    return this->virus;
}

void Car2XMessage::setVirus(bool virus)
{
    this->virus = virus;
}

class Car2XMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Car2XMessageDescriptor();
    virtual ~Car2XMessageDescriptor();

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

Register_ClassDescriptor(Car2XMessageDescriptor);

Car2XMessageDescriptor::Car2XMessageDescriptor() : omnetpp::cClassDescriptor("Car2XMessage", "WaveShortMessage")
{
    propertynames = nullptr;
}

Car2XMessageDescriptor::~Car2XMessageDescriptor()
{
    delete[] propertynames;
}

bool Car2XMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Car2XMessage *>(obj)!=nullptr;
}

const char **Car2XMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Car2XMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Car2XMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int Car2XMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *Car2XMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "creationTime",
        "originPosition",
        "hops",
        "unique_id",
        "monitorMsg",
        "maxTravelledDistance",
        "virus",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int Car2XMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "creationTime")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originPosition")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+2;
    if (fieldName[0]=='u' && strcmp(fieldName, "unique_id")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "monitorMsg")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "maxTravelledDistance")==0) return base+5;
    if (fieldName[0]=='v' && strcmp(fieldName, "virus")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Car2XMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
        "Coord",
        "int",
        "unsigned long",
        "bool",
        "double",
        "bool",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **Car2XMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *Car2XMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Car2XMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Car2XMessage *pp = (Car2XMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Car2XMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Car2XMessage *pp = (Car2XMessage *)object; (void)pp;
    switch (field) {
        case 0: return simtime2string(pp->getCreationTime());
        case 1: {std::stringstream out; out << pp->getOriginPosition(); return out.str();}
        case 2: return long2string(pp->getHops());
        case 3: return ulong2string(pp->getUnique_id());
        case 4: return bool2string(pp->getMonitorMsg());
        case 5: return double2string(pp->getMaxTravelledDistance());
        case 6: return bool2string(pp->getVirus());
        default: return "";
    }
}

bool Car2XMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Car2XMessage *pp = (Car2XMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCreationTime(string2simtime(value)); return true;
        case 2: pp->setHops(string2long(value)); return true;
        case 3: pp->setUnique_id(string2ulong(value)); return true;
        case 4: pp->setMonitorMsg(string2bool(value)); return true;
        case 5: pp->setMaxTravelledDistance(string2double(value)); return true;
        case 6: pp->setVirus(string2bool(value)); return true;
        default: return false;
    }
}

const char *Car2XMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *Car2XMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Car2XMessage *pp = (Car2XMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getOriginPosition()); break;
        default: return nullptr;
    }
}


