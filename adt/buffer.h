#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "sv.h"

// Buffer is a mutable string buffer used to build new strings.
typedef struct Buffer Buffer;

// NewBuffer creates a new buffer.
Buffer* NewBuffer();

// BufferWriteChar writes a new character into the buffer.
void BufferWriteChar(Buffer* buff, char c);

// BufferMakeSV makes a new string view of the contents of the buffer.  This
// string view references a trimmed *copy* of the buffer's internal contents:
// the buffer can safely be resized after this operation.  However, the returned
// string view is the *owner* of the string.
SV BufferMakeSV(Buffer* buff);

// BufferReset resets the given buffer.
void BufferReset(Buffer* buff);

// BufferFree frees the given buffer.
void BufferFree(Buffer* buff);

#endif