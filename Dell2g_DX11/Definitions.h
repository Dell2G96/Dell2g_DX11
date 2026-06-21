#pragma once

#define MAX_KEY_COUNT 256
#define Check(x) { assert((x) >= 0);}

#define Delete(x)\
{\
    if ((x) != nullptr)\
    {\
        delete (x);\
        (x) = nullptr;\
    }\
}

#define DeleteArray(x)\
{\
if ((x) != nullptr)\
{\
delete[] (x);\
(x) = nullptr;\
}\
}

#define Release(x)\
{\
    if ((x) != nullptr)\
    {\
        (x)->Release();\
        (x) = nullptr;\
    }\
}

