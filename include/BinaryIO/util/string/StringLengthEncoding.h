/** @file StringLengthEncoding.h
 *
 * @author DexrnZacAttack
 * @date 3/14/26
 *
 * @device zPc-i2
 */
#ifndef BIO_STRINGLENGTHENCODING_H
#define BIO_STRINGLENGTHENCODING_H

namespace bio {
    namespace util {
        namespace string {
            enum class StringLengthEncoding {
                NULL_TERMINATE, /**< Null terminate the string */
                LENGTH_PREFIX,  /**< Prefixes the string with a uint16_t containing the length */
                NONE            /**< Do not add length */
            };
        }
    } // namespace util
} // namespace bio

#endif // BIO_STRINGLENGTHENCODING_H