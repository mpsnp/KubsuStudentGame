#include "Utils.h"
#include <string>

char *KSU::GetExtencion(char *Input)
{
    char *result = new char[3];
    for (int i = (int)strlen(Input) - 1; i >= strlen(Input) - 4; i--) {
        result[i - (strlen(Input) - 4)] = Input[i];
    }
    return result;
}
