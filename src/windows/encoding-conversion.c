/*
Copyright (c) 2011-2012, Quentin Cosendey
This code is part of universal speech which is under multiple licenses.
Please refer to the readme file provided with the package for more information.
*/
#include<stdio.h>
#include<string.h>
#include<wchar.h>

static void* strptr = NULL;

const wchar_t* mb2wc (const char* str, int inCP) {
int len = MultiByteToWideChar(inCP, 0, str, -1, NULL, 0);
wchar_t* wstr = malloc(sizeof(wchar_t) * (len+1));
MultiByteToWideChar(inCP, 0, str, -1, wstr, len);
wstr[len]=0;
return wstr;
}

const char* wc2mb (const wchar_t* wstr, int outCP) {
int len = WideCharToMultiByte(outCP, 0, wstr, -1, NULL, 0, NULL, NULL);
char* str = malloc(len+1);
WideCharToMultiByte(outCP, 0, wstr, -1, str, len, NULL, NULL);
str[len]=0;
return str;
}

const char* toEncoding (const wchar_t* unicode, int targetEncoding) {
if (!unicode) return NULL;
if (strptr) free(strptr);
strptr = wc2mb(unicode, targetEncoding);
return strptr;
}

const wchar_t* fromEncoding (const char* str, int encoding) {
if (!str) return NULL;
if (strptr) free(strptr);
strptr = mb2wc(str, encoding);
return strptr;
}

