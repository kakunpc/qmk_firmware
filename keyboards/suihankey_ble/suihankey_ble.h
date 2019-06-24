#ifndef SUIHANKEY_BLE_H_
#define SUIHANKEY_BLE_H_

#include "quantum.h"

#define LAYOUT( \
    L00, L01, L02, L03, L04, \
    L10, L11, L12, L13, L14, \
    L20, L21, L22, L23, L24, \
    L30, L31, L32   \
) \
{ \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { L30, L31, L32  }, \
}

#endif /* SUIHANKEY_BLE_H_ */
