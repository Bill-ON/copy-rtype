#ifndef ZIPPERITERATOR_HPP
#define ZIPPERITERATOR_HPP

#include <iterator>
#include <utility>
#include <tuple>

#include <iostream>

#include "SparseArray.hpp"

namespace containers
{
    template <class... Containers>
    class Zipper;

    /**
     * @brief An iterator to multiple SparseArray. It only iterates over
     * entites that are valid, meaning that they have all the components
     * regrouped in the ZipperIterator.
     * Warning: It was meant to be constructed by the Zipper class only.
     * 
     * @tparam Containers The SparseArray that regroups the ZipperIterator.
     */
    template <class... Containers>
    class ZipperIterator
    {
        template <class Container>
        using iterator_t = typename Container::iterator;
        template <class Container>
        using it_reference_t = typename iterator_t<Container>::reference;

    public:
        using value_type = std::tuple<typename Containers::value_type::value_type &...>; // std:: tuple of references to components
        using reference = value_type;
        using pointer = void;
        using difference_type = size_t;
        using iterator_category = std::forward_iterator_tag;
        using iterator_tuple = std::tuple<iterator_t<Containers>...>;
        friend containers::Zipper<Containers...>;

        /**
         * @brief Construct a new Zipper Iterator object. This constructor
         * was meant to be used by the Zipper class only.
         * 
         * @param it_tuple A tuple of iterators on each of the
         * SparseArray that will regroups the ZipperIterator.
         * @param max The expected maximum size of the ZipperIterator.
         * @param idx The starting position of the index.
         */
        ZipperIterator(iterator_tuple const &it_tuple, size_t max, size_t idx) : _current(it_tuple), _max(max), _idx(idx)
        {
            if (_idx != max && !all_set(_seq))
            {
                incr_all(_seq);
            }
        }

    public:
        ZipperIterator(ZipperIterator const &z) : _current(z._current), _max(z._max), _idx(z._idx) {}

        ZipperIterator operator++()
        {
            ZipperIterator tmp = *this;
            incr_all(_seq);

            return tmp;
        }

        ZipperIterator &operator++(int)
        {
            incr_all(_seq);
            return _current;
        }

        value_type operator*()
        {
            return to_value(_seq);
        }

        value_type operator->()
        {
            return to_value(_seq);
        }

        /**
         * @brief Compare if two iterators are on the same index.
         * 
         * @param lhs The left ZipperIterator.
         * @param rhs The right ZipperIterator.
         * @return true The two iterators are on the same index.
         * @return false The two iterators aren't on the same index.
         */
        friend bool operator==(ZipperIterator const &lhs, ZipperIterator const
                                                              &rhs)
        {
            return (lhs._idx == rhs._idx);
        }
        /**
         * @brief Compare if two iterators aren't on the same index.
         * 
         * @param lhs The left ZipperIterator.
         * @param rhs The right ZipperIterator.
         * @return true The two iterators aren't on the same index.
         * @return false The two iterators are on the same index.
         */
        friend bool operator!=(ZipperIterator const &lhs, ZipperIterator const
                                                              &rhs)
        {
            return (lhs._idx != rhs._idx);
        }

    private:
        /**
         * @brief Increment every iterator at the same time.
         * It also skips to the next value if one of the pointed
         * to std::optional does not contains a value.
         * 
         * @tparam Is The index sequence that represents the number
         * of SparseArray that are zipped in the ZipperIterator.
         * The value corresponding value can be found in the static
         * member "_seq".
         */
        template <size_t... Is>
        void incr_all(std::index_sequence<Is...>)
        {
            do
            {
                (std::get<Is>(_current)++, ...);
                ++_idx;
            } while ((_idx != _max) && !all_set(_seq));
        }

        /**
         * @brief Check if every SparseArray iterators point
         * to a set std::optional. Meaning that the entity for this
         * index have all of the components of the ZipperIterator type
         * attached to itself.
         * 
         * @tparam Is The index sequence that represents the number
         * of SparseArray that are zipped in the ZipperIterator.
         * The value corresponding value can be found in the static
         * member "_seq".
         * @return true Every std::optional are set.
         * @return false One or more std::optional isn't set.
         */
        template <size_t... Is>
        bool all_set(std::index_sequence<Is...>)
        {
            return ((*std::get<Is>(_current)) && ... && true);
        }

        /**
         * @brief Return a tuple of reference to components.
         * 
         * @tparam Is The index sequence that represents the number
         * of SparseArray that are zipped in the ZipperIterator.
         * The value corresponding value can be found in the static
         * member "_seq".
         * @return value_type A tuple of reference to components.
         */
        template <size_t... Is>
        value_type to_value(std::index_sequence<Is...>)
        {
            return std::tie((**(std::get<Is>(_current)))...);
        }

    private:
        /**
         * @brief A tuple of iterators to each SparseArray
         * that regroups the ZipperIterator.
         * 
         */
        iterator_tuple _current;
        /**
         * @brief A maximum that is used to prevent infinite loop.
         * It is computed from the minimum of each SparseArrays size.
         * 
         */
        size_t _max;
        /**
         * @brief The index of the current position of each iterators
         * int theirs SparseArrays.
         * 
         */
        size_t _idx;

        static constexpr std::index_sequence_for<Containers...> _seq{};
    };
}

#endif /* ZIPPERITERATOR_HPP */
