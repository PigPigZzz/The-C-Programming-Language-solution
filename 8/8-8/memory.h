#pragma once
#define size_t long unsigned int
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void bfree(void *ptr, size_t size);