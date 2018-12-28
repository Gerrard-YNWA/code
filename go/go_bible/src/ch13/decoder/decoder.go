package decoder

import (
	"unsafe"
)

/*
#cgo CFLAGS: -I./include
#cgo LDFLAGS: -L./lib -ldecoder

#include "decoder.h"
*/
import "C"

type Decoder struct {
	dec *C.decoder_t
}

func New(rate int) Decoder {
	var decoder Decoder
	decoder.dec = C.new_decoder(C.int(rate))
	return decoder
}

func (decoder Decoder) Decode(opcode string, payload []byte) []byte {
	size := 0
	if opcode == "binary" && len(payload) > 0 {
		size = len(payload)
	}
	if payload != nil {
		C.decode(decoder.dec, C.CString(opcode), (*C.char)(unsafe.Pointer(&payload[0])), C.int(size))
	} else {
		C.decode(decoder.dec, C.CString(opcode), nil, C.int(size))
	}
	if size > 0 {
		buf := make([]byte, int(decoder.dec.len))
		buf = C.GoBytes(unsafe.Pointer(decoder.dec.data), C.int(decoder.dec.len))
		return buf
	}
	return nil
}

func (decoder Decoder) Delete() {
	C.delete_decoder(decoder.dec)
}
