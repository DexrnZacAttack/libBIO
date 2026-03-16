/** @file Iterator.h
 *
 * @author DexrnZacAttack
 * @date 3/13/26
 * 
 * @device zPc-i2
 */
#ifndef BIO_ITERATOR_H
#define BIO_ITERATOR_H
#include <iterator>

namespace bio {
    namespace io {
        namespace iter {
            // TODO we should use this in SizedBinaryBuffer and maybe streams
            template <typename T>
            class Iterator {
            public:
                using iterator_category = std::random_access_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                explicit Iterator(const pointer ptr) : m_ptr(ptr) {}

                //get
                reference operator[](difference_type v) const { return *(this->m_ptr + v); }

                reference operator*() const { return *m_ptr; }
                pointer operator->() { return m_ptr; }

                //pos
                Iterator &operator++() { ++this->m_ptr; return *this; }
                Iterator &operator--() { --this->m_ptr; return *this; }
                Iterator operator++(int) { Iterator i = *this; ++(*this); return i; }
                Iterator operator--(int) { Iterator i = *this; --(*this); return i; }

                Iterator operator+(difference_type v) const { return Iterator(this->m_ptr + v); }
                Iterator operator-(difference_type v) const { return Iterator(this->m_ptr + v); }
                difference_type operator-(const Iterator &rhs) const { return this->m_ptr - rhs.m_ptr; }

                //compare
                bool operator==(Iterator &rhs) { return this->m_ptr == rhs.m_ptr; }
                bool operator!=(Iterator &rhs) { return this->m_ptr != rhs.m_ptr; }

                bool operator<(const Iterator& rhs) const { return this->m_ptr < rhs.m_ptr; }
                bool operator>(const Iterator& rhs) const { return this->m_ptr > rhs.m_ptr; }
                bool operator<=(const Iterator& rhs) const { return this->m_ptr <= rhs.m_ptr; }
                bool operator>=(const Iterator& rhs) const { return this->m_ptr >= rhs.m_ptr; }

            private:
                pointer m_ptr;
            };

            template <typename T>
            using ConstIterator = Iterator<const T>;

            template <typename T>
            using ReverseIterator = std::reverse_iterator<Iterator<T>>;

            template <typename T>
            using ConstReverseIterator = std::reverse_iterator<ConstIterator<T>>;
        }
    } // io
} // bio

#endif // BIO_ITERATOR_H