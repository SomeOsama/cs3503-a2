
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>


static void uint32_to_bin32(uint32_t value, char *out) {
    for (int i = 31; i >= 0; --i) {
        out[31 - i] = ((value >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}


static void append_str_at(char *out, size_t *pos, const char *s) {
    while (*s) {
        out[(*pos)++] = *s++;
    }
    out[*pos] = '\0';
}


void oct_to_bin(const char *oct, char *out) {
    size_t pos = 0;
    out[0] = '\0';
    if (oct == NULL) { out[0] = '\0'; return; }

    for (const char *p = oct; *p; ++p) {
        char c = *p;
        if (c < '0' || c > '7') {
          
            continue;
        }
        int digit = c - '0';
     
        out[pos++] = (digit & 0x4) ? '1' : '0';
        out[pos++] = (digit & 0x2) ? '1' : '0';
        out[pos++] = (digit & 0x1) ? '1' : '0';
    }
    out[pos] = '\0';
}


void hex_to_bin(const char *hex, char *out) {
    size_t pos = 0;
    out[0] = '\0';
    if (hex == NULL) return;

   
    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        hex += 2;
    }

    for (const char *p = hex; *p; ++p) {
        char c = *p;
        int val = -1;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'f') val = 10 + (c - 'a');
        else {
        
            continue;
        }
      
        out[pos++] = (val & 0x8) ? '1' : '0';
        out[pos++] = (val & 0x4) ? '1' : '0';
        out[pos++] = (val & 0x2) ? '1' : '0';
        out[pos++] = (val & 0x1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out) {
    if (oct == NULL) { out[0] = '\0'; return; }

   
    char bin[512];
    oct_to_bin(oct, bin);
    size_t bin_len = strlen(bin);
    if (bin_len == 0) {
      
        strcpy(out, "0");
        return;
    }

  
    size_t rem = bin_len % 4;
    size_t pad = (rem == 0) ? 0 : (4 - rem);

   
    char padded[520];
    size_t pos = 0;
    for (size_t i = 0; i < pad; ++i) padded[pos++] = '0';
    for (size_t i = 0; i < bin_len; ++i) padded[pos++] = bin[i];
    padded[pos] = '\0';

  
    size_t outpos = 0;
    for (size_t i = 0; i < pos; i += 4) {
        int v = 0;
        for (int j = 0; j < 4; ++j) {
            v = (v << 1) | (padded[i + j] == '1' ? 1 : 0);
        }
        if (v < 10) out[outpos++] = '0' + v;
        else out[outpos++] = 'A' + (v - 10);
    }
    out[outpos] = '\0';

  
    char *first_nonzero = out;
    while (*first_nonzero == '0' && *(first_nonzero + 1) != '\0') first_nonzero++;
    if (first_nonzero != out) memmove(out, first_nonzero, strlen(first_nonzero) + 1);
}


void to_sign_magnitude(int32_t n, char *out) {
    if (out == NULL) return;
    uint32_t sign = 0;
    uint64_t mag64 = 0;

    if (n < 0) {
        sign = 1;
      
        mag64 = (uint64_t)(- (int64_t)n);
    } else {
        sign = 0;
        mag64 = (uint64_t)n;
    }

    uint32_t mag31 = (uint32_t)(mag64 & 0x7FFFFFFF);

    
    out[0] = sign ? '1' : '0';
    for (int i = 30; i >= 0; --i) {
        out[31 - i] = ((mag31 >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_ones_complement(int32_t n, char *out) {
    if (out == NULL) return;
    if (n >= 0) {
        uint32_to_bin32((uint32_t)n, out);
    } else {
       
        uint32_t mag32 = (uint32_t)(- (int64_t)n); 
        uint32_t flipped = ~mag32;
        uint32_to_bin32(flipped, out);
    }
}


void to_twos_complement(int32_t n, char *out) {
    if (out == NULL) return;
    uint32_t pattern = (uint32_t)n; 
    uint32_to_bin32(pattern, out);
}


