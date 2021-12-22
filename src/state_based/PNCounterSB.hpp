/*
    Copyright (c) 2021 [Tapasvi Patel, Rushab Roihan, Vishwa Gandhi, Winston Sun]

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __PNCOUNTERSB_H__
#define __PNCOUNTERSB_H__

#include "../CrdtHandle.hpp"
#include "../CrdtObject.hpp"

namespace crdt
{
namespace state
{

/*
* metadata template class for CRDT counter
*/
template<typename T=int32_t>
class PNCounterMetadata : CrdtMetaData
{
private:
    uint32_t id;
    T positivePayload;
    T negativePayload;
    T totalPayload;
public:
    PNCounterMetadata(uint32_t id) : CrdtMetaData(CrdtType::PNCounterSBType)
    {
        this->id = id;
        this->positivePayload = 0;
        this->negativePayload = 0;
    }
    PNCounterMetadata(uint32_t id, T positivePayload) : CrdtMetaData(CrdtType::PNCounterSBType)
    {
        this->id = id;
        this->positivePayload = positivePayload;
        this->totalPayload = positivePayload;
        this->negativePayload = 0;
    }
    ~PNCounterMetadata()
    {
        ;
    }
    void merge(T payload)
    {
        this->positivePayload = std::max(this->positivePayload, payload);
        this->negativePayload = std::max(this->negativePayload, payload);
    }

    const T& queryId() const
    {
        return this->id;
    }

    const T& queryPayload() const
    {
        return this->totalPayload;
    }

    void increasePayload(T positivePayload)
    {
        this->positivePayload += positivePayload;
        this->totalPayload = this->positivePayload - this->negativePayload;
    }

    void decreasePayload(T negativePayload)
    {
        this->negativePayload += negativePayload;
        this->totalPayload = this->positivePayload - this->negativePayload;
    }

};


/*
* template class for CRDT PNcounter
*/
template<typename T=int32_t>
class PNCounterSB : CrdtObject<T>
{
private:
    uint32_t id;
    T payload;
    std::unordered_map<uint32_t,PNCounterMetadata<T>> replica_metadata;
protected:
    bool merge(std::vector<uint32_t> replica_ids)
    {
        return false;
    }
    bool serialize(std::string& buffer)
    {
        return false;
    }

    bool deserialize(std::string& buffer)
    {
        return false;
    }

    bool exportDB()
    {
        return false;
    }

    bool importDB()
    {
        return false;
    }
public:
    PNCounterSB(uint32_t id, T payload)
    {
        this->id = id;
        this->payload = payload;
        this->replica_metadata.insert(std::pair<uint32_t, PNCounterMetadata<T>>(this->id, PNCounterMetadata<T>(this->id, this->payload)));
    }
    ~PNCounterSB()
    {
        ;
    }
    bool updateInternalPayload()
    {
        T curr = T();
        typename std::unordered_map<uint32_t,PNCounterMetadata<T>>::iterator metadata_it;

        for(metadata_it = this->replica_metadata.begin(); metadata_it != this->replica_metadata.end(); metadata_it++)
        {
            curr += metadata_it->second.queryPayload();
        }

        this->payload = curr;
        return true;
    }
    bool updateExternalPayload()
    {
        typename std::unordered_map<uint32_t,PNCounterMetadata<T>>::iterator metadata_it;
        metadata_it = this->replica_metadata.find(this->id);
        metadata_it->second.payload = this->payload;
        return true;
    }
#ifdef BUILD_TESTING
    const T& queryId() const
    {
        return this->id;
    }

    const T& queryPayload() const
    {
        return this->payload;
    }

    void setPayLoad(T payload)
    {
        this->payload = payload;
    }

    void addExternalReplica(std::vector<PNCounterMetadata<T>> external_replica_metadata)
    {
        for (auto &metadata: external_replica_metadata)
        {
            this->replica_metadata.insert(std::pair<uint32_t, PNCounterMetadata<T>>(metadata.queryId(), metadata));
        }
        
    }
    void updateLocalExternalPayload(std::vector<PNCounterSB> handlers)
    {
        T maxPayload;
        for (auto handler: handlers)
        {
            maxPayload = std::max(handler.queryPayload(), maxPayload);
        }
        setPayLoad(maxPayload);
    }
#endif
};

}   // namespace state
}   // namespace crdt

#endif  // __PNCOUNTERSB_H__
