#ifndef ZIPPER_HPP
#define ZIPPER_HPP

#include "ZipperIterator.hpp"

namespace containers
{
    /**
     * @brief Handles the creation of a single iterator from
     * multiple SparseArray. It must be noted that the produced
     * iterator only iterates over entities on which all the
     * components required by the Zipper are attached to.
     * It is mainly used for the implementation
     * of system function that iterates over.
     *
     * e.g:
     * ```cpp
     * SparseArray<Component::Position> positions;
     * SparseArray<Component::Velocity> velocities;
     *
     * for (auto &&[pos, vel] : containers::Zipper(positions, velocities))
     * {
     *     pos.x += vel.x;
     *     pos.y += vel.y
     * }
     *
     * ```
     *
     * @tparam Containers The SparseArray to iterates over.
     */
    template <class... Containers>
    class Zipper
    {
    public:
        using iterator = ZipperIterator<Containers...>;
        using iterator_tuple = typename iterator::iterator_tuple;

        Zipper(Containers &...cs)
        {
            _size = min_element(cs.size()...);
            _idx = 0;
            _begin = std::make_tuple(cs.begin()...);
            _end = std::make_tuple(cs.end()...);
        }

        /**
         * @brief Construct a new Zipper object
         * 
         * @param idx The starting position of the Zipper
         * iterator.
         * @param cs The Components SparseArrays.
         */
        Zipper(std::size_t idx, Containers &...cs)
        {
            _size = min_element(cs.size()...);
            _idx = (idx < _size ? idx : _size);
            _begin = compute_begin(std::index_sequence_for<Containers...>{}, _idx, cs...);
            _end = std::make_tuple(cs.end()...);
        }

        /**
         * @brief Return an iterator to the begining of the
         * SparseArray zipping.
         *
         * @return iterator An iterator to the begining of the
         * SparseArray zipping.
         */
        iterator begin()
        {
            return iterator(_begin, _size, 0);
        }

        /**
         * @brief Return an iterator to the end of the
         * SparseArray zipping.
         *
         * @return iterator An iterator to the end of the
         * SparseArray zipping.
         */
        iterator end()
        {
            return iterator(_end, _size, _size);
        }

    private:
        /**
         * @brief Return the minimum value from a
         * Parameter Pack.
         * 
         * @tparam T The type of the Parameter Pack.
         * @tparam Args The rest of the Parameter Pack.
         * @param first The first element.
         * @param args The rest of the Parameter Pack.
         * @return T The minimal value.
         */
        template <typename T, typename... Args>
        T min_element(T first, Args... args) {
            return std::min(first, min_element(args...));
        }

        /**
         * @brief Return the minimum value from a
         * Parameter Pack.
         *
         * 
         * @tparam T The type of the Parameter Pack.
         * @param first The first element.
         * @return T The minimal value.
         */
        template <typename T>
        T min_element(T t) {
            return t;
        }

        /**
         * @brief Compute the begin value
         * of the Zipper
         * 
         * @tparam Is The sequence of index
         * in the tuple.
        */
        template <size_t...  Is>
        iterator_tuple compute_begin(std::index_sequence<Is...>, const size_t idx, Containers &...cs)
        {
            iterator_tuple t = std::make_tuple(cs.begin()...);

            for (int i = 0; i < idx; i++) {
                (std::get<Is>(t)++, ...);
            }

            return t;
        }


        /**
         * @brief The maximum size of the SparseArray
         * Zipping. If SparseArray aren't of the same
         * size, it represents the minimum of all to
         * avoid errors. It don't represents the number
         * of entities that have all corresponding
         * components attached to.
         *
         */
        size_t _size;
        /**
         * @brief The starting index of the
         * ZipperIterator.
         * 
         */
        std::size_t _idx;
        /**
         * @brief A tuple of all SparseArray
         * legacy begin iterator.
         *
         */
        iterator_tuple _begin;
        /**
         * @brief A tuple of all SparseArray
         * legacy end iterator.
         *
         */
        iterator_tuple _end;
    };
}

#endif /* ZIPPER_HPP */
