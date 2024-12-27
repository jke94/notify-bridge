#include <iostream>

#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiResultTypes.h"

std::ostream& operator<<(std::ostream& os, ApiResult result)
{
    switch (result)
    {
        case ApiResult::SUCCESS:
            os << "SUCCESS";
            break;
        case ApiResult::FAILURE:
            os << "FAILURE";
            break;
        case ApiResult::FAILURE_ELEMENT_NOT_FOUND:
            os << "FAILURE_ELEMENT_NOT_FOUND";
            break;
        case ApiResult::FAILURE_ELEMENT_IS_NULL:
            os << "FAILURE_ELEMENT_IS_NULL";
            break;                       
        default:
            os << "UNKNOWN_TYPE";
            break;
    }
    return os;
}