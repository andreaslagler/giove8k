#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////
// Storage class for patch/scene objects
template <typename Item, typename Memory>
class Storage
{
    private:
    
    typedef typename Memory::Address Address;
    static constexpr Address s_itemSize = static_cast<Address>(sizeof(Item));
    
    public:

    static constexpr uint32_t capacity()
    {
        static_assert(Memory::capacity() >= sizeof(Item), "Memory has insufficient capacity");
        return Memory::capacity() / sizeof(Item);
    }
    
    template <typename Idx>
    static void load_name(const Idx& idx, char* const name)
    {
        if (idx < capacity())
        {
            const Address address = static_cast<Address>(idx) * s_itemSize;
            Memory::read(address, reinterpret_cast<uint8_t*>(name), Item::getNameSize());
        }
    }

    template <typename Idx>
    static void load(const Idx& idx, Item& item)
    {
        if (idx < capacity())
        {
            const Address address = static_cast<Address>(idx) * s_itemSize;
            Memory::read(address, reinterpret_cast<uint8_t*>(&item), s_itemSize);
        }
    }

    template <typename Idx>
    static void save(const Idx& idx, const Item& item)
    {
        if (idx < capacity())
        {
            const Address address = static_cast<Address>(idx) * s_itemSize;
            Memory::write(address, reinterpret_cast<const uint8_t*>(&item), s_itemSize);
        }
    }
};

# endif