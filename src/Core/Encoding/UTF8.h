#pragma once

#include "Platform/Platform.h"
#include <algorithm>
#include <cstdint>

// UTF-8 leading byte masks
constexpr uint8_t UTF8_1BYTE_MASK = 0x80; // 10000000 - if below this, it's ASCII
constexpr uint8_t UTF8_2BYTE_MASK = 0xE0; // 11100000
constexpr uint8_t UTF8_3BYTE_MASK = 0xF0; // 11110000
constexpr uint8_t UTF8_4BYTE_MASK = 0xF8; // 11111000

// UTF-8 leading byte signatures (what the masked bits must equal)
constexpr uint8_t UTF8_2BYTE_SIG = 0xC0; // 11000000
constexpr uint8_t UTF8_3BYTE_SIG = 0xE0; // 11100000
constexpr uint8_t UTF8_4BYTE_SIG = 0xF0; // 11110000

// UTF-8 continuation byte
constexpr uint8_t UTF8_CONTINUATION_MASK = 0xC0; // 11000000
constexpr uint8_t UTF8_CONTINUATION_SIG = 0x80; // 10000000

// UTF-8 payload masks (bits that carry codepoint data)
constexpr uint8_t UTF8_1BYTE_PAYLOAD = 0x7F; // 01111111 - all 7 bits
constexpr uint8_t UTF8_2BYTE_PAYLOAD = 0x1F; // 00011111 - 5 bits
constexpr uint8_t UTF8_3BYTE_PAYLOAD = 0x0F; // 00001111 - 4 bits
constexpr uint8_t UTF8_4BYTE_PAYLOAD = 0x07; // 00000111 - 3 bits
constexpr uint8_t UTF8_CONTINUATION_PAYLOAD = 0x3F; // 00111111 - 6 bits

// Unicode illegals
constexpr uint8_t UTF8_ILLEGAL_C0 = 0xC0;
constexpr uint8_t UTF8_ILLEGAL_C1 = 0xC1;
constexpr uint8_t UTF8_ILLEGAL_F5 = 0xF5;

// Codepoint range boundaries
constexpr uint32_t UTF8_2BYTE_BOUNDARY = 0x80; // Above this needs 2 bytes
constexpr uint32_t UTF8_3BYTE_BOUNDARY = 0x800; // Above this needs 3 bytes
constexpr uint32_t UTF8_4BYTE_BOUNDARY = 0x10000; // Above this needs 4 bytes

// Codepoint surrogate range
constexpr uint32_t UNICODE_SURROGATE_MIN = 0xD800;
constexpr uint32_t UNICODE_SURROGATE_MAX = 0xDFFF;
constexpr uint32_t UNICODE_MAX = 0x10FFFF;

// Codepoint surrogate pairs
constexpr uint32_t SURROGATE_PAIR_THRESHOLD = 0x10000;
constexpr uint32_t SURROGATE_PAIR_OFFSET = 0x10000;
constexpr uint32_t HIGH_SURROGATE_BASE = 0xD800;
constexpr uint32_t LOW_SURROGATE_BASE = 0xDC00;
constexpr uint32_t SURROGATE_HIGH_SHIFT = 10;
constexpr uint32_t SURROGATE_LOW_MASK = 0x3FF;

// Unicode invalid
constexpr uint32_t UNICODE_INVALID = 0xFFFD;

// Continuation byte shift amount
constexpr int UTF8_CONTINUATION_SHIFT = 6;

// Source: https://stackoverflow.com/a/9356203
// Byte sequence starts with 10xxxxxx
inline bool IsContinuationByte(UANSICHAR b)
{
    return (b & UTF8_CONTINUATION_MASK) == UTF8_CONTINUATION_SIG;
}

inline bool IsValidCodepoint(uint32_t cp)
{
    if (cp >= UNICODE_SURROGATE_MIN && cp <= UNICODE_SURROGATE_MAX)
    {
        return false;
    }

    if (cp > UNICODE_MAX) 
    {
        return false;
    }

    return true;
}

inline uint32_t ReturnUnicodeInvalidAndAdvance(size_t& i)
{
    i++;
    return UNICODE_INVALID;
}

inline uint32_t ReturnUnicodeInvalidAndAdvanceTruncated(ANSICSTR buf, size_t len, size_t& i)
{
    UANSICHAR c = (UANSICHAR)buf[i];

    size_t sequenceLength;

    if ((c & UTF8_2BYTE_MASK) == UTF8_2BYTE_SIG)
    {
        sequenceLength = 2;
    }
    else if ((c & UTF8_3BYTE_MASK) == UTF8_3BYTE_SIG)
    {
        sequenceLength = 3;
    }
    else if ((c & UTF8_4BYTE_MASK) == UTF8_4BYTE_SIG)
    {
        sequenceLength = 4;
    }
    else
    {
        sequenceLength = 1;
    }

    i += std::min(sequenceLength, len - i);

    return UNICODE_INVALID;
}

inline uint32_t DecodeUTF8(ANSICSTR buf, size_t len, size_t& i)
{
    UANSICHAR c = (UANSICHAR)buf[i];

    // Reject illegal leading bytes explicitly
    if (c == UTF8_ILLEGAL_C0 || c == UTF8_ILLEGAL_C1 || c >= UTF8_ILLEGAL_F5)
    {
        return ReturnUnicodeInvalidAndAdvance(i);
    }

    if (c < UTF8_1BYTE_MASK) // 1 byte: 0xxxxxxx
    {
        i++;
        return c;
    }
    else if ((c & UTF8_2BYTE_MASK) == UTF8_2BYTE_SIG && i + 1 < len) // 2 bytes: 110xxxxx
    {
        if (!IsContinuationByte((UANSICHAR)buf[i + 1]))
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }

        uint32_t cp = (uint32_t)(c & UTF8_2BYTE_PAYLOAD) << UTF8_CONTINUATION_SHIFT;
        cp |= ((UANSICHAR)buf[i + 1] & UTF8_CONTINUATION_PAYLOAD);
        
        if (cp < UTF8_2BYTE_BOUNDARY) // Overlong
        { 
            return ReturnUnicodeInvalidAndAdvance(i);
        } 

        if (!IsValidCodepoint(cp)) 
        { 
            return ReturnUnicodeInvalidAndAdvance(i);
        }
        
        i += 2;

        return cp;
    }
    else if ((c & UTF8_3BYTE_MASK) == UTF8_3BYTE_SIG && i + 2 < len) // 3 bytes: 1110xxxx
    {
        if (!IsContinuationByte((UANSICHAR)buf[i + 1]) ||
            !IsContinuationByte((UANSICHAR)buf[i + 2]))
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }

        uint32_t cp = (uint32_t)(c & UTF8_3BYTE_PAYLOAD) << (UTF8_CONTINUATION_SHIFT * 2);
        cp |= ((UANSICHAR)buf[i + 1] & UTF8_CONTINUATION_PAYLOAD) << UTF8_CONTINUATION_SHIFT;
        cp |= ((UANSICHAR)buf[i + 2] & UTF8_CONTINUATION_PAYLOAD);

        if (cp < UTF8_3BYTE_BOUNDARY) // Overlong
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }

        if (!IsValidCodepoint(cp))
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }

        i += 3;

        return cp;
    }
    else if ((c & UTF8_4BYTE_MASK) == UTF8_4BYTE_SIG && i + 3 < len) // 4 bytes: 11110xxx
    {
        if (!IsContinuationByte((UANSICHAR)buf[i + 1]) ||
            !IsContinuationByte((UANSICHAR)buf[i + 2]) ||
            !IsContinuationByte((UANSICHAR)buf[i + 3]))
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }

        uint32_t cp = (uint32_t)(c & UTF8_4BYTE_PAYLOAD) << (UTF8_CONTINUATION_SHIFT * 3);
        cp |= ((UANSICHAR)buf[i + 1] & UTF8_CONTINUATION_PAYLOAD) << (UTF8_CONTINUATION_SHIFT * 2);
        cp |= ((UANSICHAR)buf[i + 2] & UTF8_CONTINUATION_PAYLOAD) << UTF8_CONTINUATION_SHIFT;
        cp |= ((UANSICHAR)buf[i + 3] & UTF8_CONTINUATION_PAYLOAD);
        
        if (cp < UTF8_4BYTE_BOUNDARY) // Overlong
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }

        if (!IsValidCodepoint(cp))
        {
            return ReturnUnicodeInvalidAndAdvance(i);
        }
        
        i += 4;

        return cp;
    }

    return ReturnUnicodeInvalidAndAdvanceTruncated(buf, len, i);
}

inline int EncodeUTF8(uint32_t cp, ANSICSTRMUT buf)
{
    if (!IsValidCodepoint(cp))
    {
        return EncodeUTF8(UNICODE_INVALID, buf);
    }

    if (cp < UTF8_2BYTE_BOUNDARY)
    {
        buf[0] = (ANSICHAR)cp;

        return 1;
    }
    else if (cp < UTF8_3BYTE_BOUNDARY)
    {
        buf[0] = (ANSICHAR)(UTF8_2BYTE_SIG | (cp >> UTF8_CONTINUATION_SHIFT));
        buf[1] = (ANSICHAR)(UTF8_CONTINUATION_SIG | (cp & UTF8_CONTINUATION_PAYLOAD));

        return 2;
    }
    else if (cp < UTF8_4BYTE_BOUNDARY)
    {
        buf[0] = (ANSICHAR)(UTF8_3BYTE_SIG | (cp >> (UTF8_CONTINUATION_SHIFT * 2)));
        buf[1] = (ANSICHAR)(UTF8_CONTINUATION_SIG | ((cp >> UTF8_CONTINUATION_SHIFT) & UTF8_CONTINUATION_PAYLOAD));
        buf[2] = (ANSICHAR)(UTF8_CONTINUATION_SIG | (cp & UTF8_CONTINUATION_PAYLOAD));

        return 3;
    }
    else
    {
        buf[0] = (ANSICHAR)(UTF8_4BYTE_SIG | (cp >> (UTF8_CONTINUATION_SHIFT * 3)));
        buf[1] = (ANSICHAR)(UTF8_CONTINUATION_SIG | ((cp >> (UTF8_CONTINUATION_SHIFT * 2)) & UTF8_CONTINUATION_PAYLOAD));
        buf[2] = (ANSICHAR)(UTF8_CONTINUATION_SIG | ((cp >> UTF8_CONTINUATION_SHIFT) & UTF8_CONTINUATION_PAYLOAD));
        buf[3] = (ANSICHAR)(UTF8_CONTINUATION_SIG | (cp & UTF8_CONTINUATION_PAYLOAD));

        return 4;
    }
}

inline GENCSTR CodepointToString(uint32_t cp)
{
    GENCHAR buf[3]{};

    if (cp >= SURROGATE_PAIR_THRESHOLD)
    {
        cp -= SURROGATE_PAIR_OFFSET;
        buf[0] = (GENCHAR)(HIGH_SURROGATE_BASE + (cp >> SURROGATE_HIGH_SHIFT)); // high surrogate
        buf[1] = (GENCHAR)(LOW_SURROGATE_BASE + (cp & SURROGATE_LOW_MASK)); // low surrogate
        buf[2] = L'\0';
    }
    else
    {
        buf[0] = (GENCHAR)cp;
        buf[1] = L'\0';
    }

    return buf;
}
