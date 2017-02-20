/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef TEA_H
#define TEA_H
#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif

void tea_encrypt (uint32_t* v, uint32_t* k);
void tea_decrypt (uint32_t* v, uint32_t* k);


#ifdef __cplusplus
}
#endif

#endif /* TEA_H */

