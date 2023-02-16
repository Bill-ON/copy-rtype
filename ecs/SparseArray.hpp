#ifndef SPARSE_ARRAY_HPP
#define SPARSE_ARRAY_HPP

#include <algorithm>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

/**
 * @brief The array that regroups all the components
 * of a specific type. In the sparse array the index
 * of a component is the id of the entity it is
 * attached to. As the sparse array is composed of
 * std::optional, if no component of the sparse array
 * type is attached to an entity, the component is
 * represented in the sparse array by an empty
 * std::optional.
 * 
 * 
 * @tparam Component The type of component contained
 * in the sparse array.
 */
template <typename Component>
class SparseArray
{
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;

    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

public:
    SparseArray();

    SparseArray(SparseArray const &);
    SparseArray(SparseArray &&) noexcept;
    ~SparseArray();

    SparseArray &operator=(SparseArray const &);
    SparseArray &operator=(SparseArray &&) noexcept;

    reference_type operator[](size_t);
    const_reference_type operator[](size_t) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    size_type size() const;

    reference_type insert_at(size_type, Component const &);
    reference_type insert_at(size_type, Component &&);

    template <class... Params>
    reference_type emplace_at(size_type, Params &&...);

    void erase(size_type);

    size_type get_index(value_type const &) const;

    bool doesContain(size_t) const;
private:
    /**
     * @brief the vector of optional components.
     * 
     */
    container_t _data;
};

template <typename Component>
inline SparseArray<Component>::SparseArray()
    : _data()
{
}

template <typename Component>
inline SparseArray<Component>::SparseArray(SparseArray const &other)
{
    _data = other._data;
}

template <typename Component>
inline SparseArray<Component>::SparseArray(SparseArray &&other) noexcept
{
    _data = std::move(other._data);
}

template <typename Component>
inline SparseArray<Component>::~SparseArray()
{
}

template <typename Component>
inline SparseArray<Component> &SparseArray<Component>::operator=(SparseArray const &other)
{
    _data = other._data;
    return *this;
};

template <typename Component>
inline SparseArray<Component> &SparseArray<Component>::operator=(SparseArray &&other) noexcept
{
    _data = std::move(other._data);
    return *this;
};

template <typename Component>
inline typename SparseArray<Component>::reference_type SparseArray<Component>::operator[](size_t idx)
{
    return _data[idx];
};

template <typename Component>
inline typename SparseArray<Component>::const_reference_type SparseArray<Component>::operator[](size_t idx) const
{
    return _data.at(idx);
};

template <typename Component>
inline typename SparseArray<Component>::iterator SparseArray<Component>::begin()
{
    return _data.begin();
}

template <typename Component>
inline typename SparseArray<Component>::const_iterator SparseArray<Component>::begin() const
{
    return _data.begin();
}

template <typename Component>
inline typename SparseArray<Component>::const_iterator SparseArray<Component>::cbegin() const
{
    return _data.cbegin();
}

template <typename Component>
inline typename SparseArray<Component>::iterator SparseArray<Component>::end()
{
    return _data.end();
}

template <typename Component>
inline typename SparseArray<Component>::const_iterator SparseArray<Component>::end() const
{
    return _data.end();
}

template <typename Component>
inline typename SparseArray<Component>::const_iterator SparseArray<Component>::cend() const
{
    return _data.cend();
}

template <typename Component>
inline typename SparseArray<Component>::size_type SparseArray<Component>::size() const
{
    return _data.size();
}

template <typename Component>
inline typename SparseArray<Component>::reference_type SparseArray<Component>::insert_at(size_type pos, Component const &component)
{
    if (pos >= _data.size())
        _data.resize(pos + 1);
    _data[pos] = component;
    return _data[pos];
}

template <typename Component>
inline typename SparseArray<Component>::reference_type SparseArray<Component>::insert_at(size_type pos, Component &&component)
{
    if (pos >= _data.size())
        _data.resize(pos + 1);
    _data[pos] = std::move(component);
    return _data[pos];
}

template <typename Component>
template <class... Params>
inline typename SparseArray<Component>::reference_type SparseArray<Component>::emplace_at(size_type pos, Params &&...params)
{
    if (pos >= _data.size())
        _data.resize(pos + 1);
    else if (_data[pos].has_value())
        std::allocator_traits<decltype(_data.get_allocator())>::destroy(_data.get_allocator(), std::addressof(_data[pos]));
    _data[pos] = Component(std::forward<Params>(params)...);
    return _data[pos];
}

template <typename Component>
inline void SparseArray<Component>::erase(size_type pos)
{
    if (pos < _data.size())
        _data[pos].reset();
}

template <typename Component>
inline typename SparseArray<Component>::size_type SparseArray<Component>::get_index(value_type const &value) const
{
    return std::distance(_data.begin(), std::find_if(_data.begin(), _data.end(), [&value](auto &elem)
                                                     { return std::addressof(elem) == std::addressof(value); }));
}

template <typename Component>
inline bool SparseArray<Component>::doesContain(size_t idx) const
{
    if (idx >= _data.size()) {
        return false;
    } else {
        return _data[idx].has_value();
    }
}

#endif /* SPARSE_ARRAY_HPP */
