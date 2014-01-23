/*
Copyright (c) 2011-2012, Quentin Cosendey
This code is part of universal speech which is under multiple licenses.
Please refer to the readme file provided with the package for more information.
*/
#include "../../include/UniversalSpeech.h"
#include<windows.h>
#include "disphelper.h"

static IDispatch* cbr = NULL;

void export cbrUnload () {
SAFE_RELEASE(cbr);
cbr = NULL;
}

BOOL export cbrIsAvailable (void) {
static int found=0, last = 0;
int z = GetTickCount();
if (z-last<60000) return found;
last=z;
found = FindProcess("cobra.exe", NULL, 0);
return found;
}

BOOL export cbrLoad (void) {
dhAutoInit();
if (cbr) return TRUE;
IDispatch *broker=NULL, *cobra=NULL, *procobj=NULL;
dhCreateObject(L"CBR_Broker.cBroker", NULL, &broker);
if (!broker) goto end;
dhGetValue(L"%o", &cobra, broker, L".GetCobra()");
if (!cobra) goto end;
dhGetValue(L"%o", &procobj, cobra, L".ProcObj()");
if (!procobj) goto end;
cbr = procobj;
end:
SAFE_RELEASE(cobra);
SAFE_RELEASE(broker);
return !!cbr;
}

BOOL export cbrStopSpeech (void) {
if (!cbr && !cbrLoad()) return FALSE;
dhCallMethod(cbr, L".speechStop()");
return TRUE;
}

BOOL export cbrSayA (const char* str) {
if (!cbr && !cbrLoad()) return FALSE;
dhCallMethod(cbr, L".speechout(%s)", str);
return TRUE;
}

BOOL export cbrSayW (const wchar_t* str) {
if (!cbr && !cbrLoad()) return FALSE;
dhCallMethod(cbr, L".speechout(%S)", str);
return TRUE;
}

BOOL export cbrBrailleA (const char* str) {
if (!cbr && !cbrLoad()) return FALSE;
dhCallMethod(cbr, L".brailleout(%s)", str);
return TRUE;
}

BOOL export cbrBrailleW (const wchar_t* str) {
if (!cbr && !cbrLoad()) return FALSE;
dhCallMethod(cbr, L".brailleout(%S)", str);
return TRUE;
}


