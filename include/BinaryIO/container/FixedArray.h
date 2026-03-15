/** @file FixedArray.h
 *
 * @author DexrnZacAttack
 * @date 3/13/26
 *
 * @device zPc-i2
 */
#ifndef BIO_FIXEDARRAY_H
#define BIO_FIXEDARRAY_H
#include "BinaryIO/io/interface/IAccessible.h"
#include "BinaryIO/io/iter/Iterator.h"

#include <algorithm>
#include <cstdint>

namespace bio {
    namespace container {
        /** Simple heap allocated alternative to std::array, which allows for size to be passed at runtime.
         * I don't like to use std::vector unless I specifically want my array to be dynamic.
         *
         * Just wraps a start and end pointer with an iterator and provides other useful methods.
         */
        template <typename T> class FixedArray : public io::interface::IAccessible<T> {
          public:
            /** Creates a FixedArray with given size */
            explicit FixedArray(const std::size_t size) {
                this->m_begin = new T[size];
                this->m_end = this->m_begin + size;
            }

            /** Creates a FixedArray with the given size, then fills the array with the given value */
            FixedArray(const std::size_t size, const T &filler) : FixedArray(size) {
                std::fill(this->m_begin, this->m_end, filler);
            }

            /** Creates an owning FixedArray with the given size and pointer
             *
             * The pointer will be destroyed at the end of the array's lifetime
             */
            FixedArray(const std::size_t size, const T *ptr) {
                this->m_begin = ptr;
                this->m_end = this->m_begin + size;
            }

            ~FixedArray() override {
                delete[] this->m_begin;

                this->m_begin = nullptr;
                this->m_end = nullptr;
            };

            /** Returns the start pointer */
            T *startPtr() { return this->m_begin; }

            T *endPtr() { return this->m_end; }

            T &operator[](std::size_t p) override { return *(this->m_begin + p); }

            const T &operator[](std::size_t p) const override { return *(this->m_begin + p); }

            T &operator*() override { return *this->m_begin; }

            const T &operator*() const override { return *this->m_begin; }

            T *operator->() override { return this->m_begin; }

            const T *operator->() const override { return this->m_begin; }

            io::iter::Iterator<T> begin() { return io::iter::Iterator<T>(this->m_begin); }

            io::iter::Iterator<T> end() { return io::iter::Iterator<T>(this->m_end); }

            io::iter::ConstIterator<T> begin() const { return io::iter::ConstIterator<T>(this->m_begin); }

            io::iter::ConstIterator<T> end() const { return io::iter::ConstIterator<T>(this->m_end); }

            std::reverse_iterator<io::iter::Iterator<T>> rbegin() {
                return std::reverse_iterator<io::iter::Iterator<T>>(this->m_end);
            }

            std::reverse_iterator<io::iter::Iterator<T>> rend() {
                return std::reverse_iterator<io::iter::Iterator<T>>(this->m_begin);
            }

            std::reverse_iterator<io::iter::ConstIterator<T>> rbegin() const {
                return std::reverse_iterator<io::iter::ConstIterator<T>>(this->m_end);
            }

            std::reverse_iterator<io::iter::ConstIterator<T>> rend() const {
                return std::reverse_iterator<io::iter::ConstIterator<T>>(this->m_begin);
            }

          private:
            T *m_begin;
            T *m_end;
        };
    } // namespace container
} // namespace bio

#endif // BIO_FIXEDARRAY_H