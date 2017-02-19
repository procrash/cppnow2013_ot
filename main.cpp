#pragma once

#include <boost/serialization/export.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/iostreams/stream.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include "container_device.hpp"


struct SerializableBaseClass
{
    virtual ~SerializableBaseClass() {}
    virtual void operator()() = 0;
    virtual SerializableBaseClass* clone() const = 0;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int) {}
};


struct SerializableSubClass : SerializableBaseClass
{
    int x{0};

    void operator()()
    {
        std::cout << "hello world " << x << "\n";

    }

    SerializableBaseClass* clone() const
    {
        return new SerializableSubClass;
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        // Without XML use next line instead of this one...
        //        ar & boost::serialization::base_object<action>(*this);

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SerializableBaseClass);
        ar & BOOST_SERIALIZATION_NVP(x);

    }
};

BOOST_CLASS_EXPORT_GUID(SerializableSubClass, "SerializableSubClass");
// BOOST_CLASS_TRACKING(SerializableSubClass, boost::serialization::track_never);



std::vector<char>* serializeObject(SerializableBaseClass const& act)
{
    std::vector<char>* raw_msg_ptr = new std::vector<char>();

    typedef container_device<std::vector<char> > io_device_type;
    boost::iostreams::stream<io_device_type> io(*raw_msg_ptr);

    SerializableBaseClass const* act_ptr = &act;

    {
        boost::archive::xml_oarchive archive(io);
        archive & BOOST_SERIALIZATION_NVP(act_ptr);
    }

    return raw_msg_ptr;
}

SerializableBaseClass* deserializeObject(std::vector<char>& raw_msg)
{
    typedef container_device<std::vector<char> > io_device_type;
    boost::iostreams::stream<io_device_type> io(raw_msg);

    SerializableBaseClass* act_ptr = 0;

    {
        boost::archive::xml_iarchive archive(io);
        archive & BOOST_SERIALIZATION_NVP(act_ptr);
    }



    return act_ptr;
}


void debugSerializedObject(std::vector<char>& serialized) {
    for (auto ch : serialized) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

int main(int, char**)
{

    std::vector<char>* serialized ;
    {
        SerializableSubClass hwa;
        hwa.x = 20;
        serialized = serializeObject(hwa);
    }

    debugSerializedObject(*serialized);


    SerializableBaseClass *hwaDeserialized = deserializeObject(*serialized);
    (*hwaDeserialized)();

    return 0;
}


