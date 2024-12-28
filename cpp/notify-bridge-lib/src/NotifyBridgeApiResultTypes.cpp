#include <iostream>

#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiResultTypes.h"

std::ostream& operator<<(std::ostream& os, const LOGGER_INFRASTRUCTURE_RESULT& result) 
{
    switch (result) {
        case LOGGER_INFRASTRUCTURE_RESULT::WTF:
            os << "WTF";
            break;
        case LOGGER_INFRASTRUCTURE_RESULT::OK:
            os << "OK";
            break;
        case LOGGER_INFRASTRUCTURE_RESULT::FAILURE_HEY_YOU_HAVE_ALREADY_INITIALIZE_THE_LOGGER:
            os << "FAILURE_HEY_YOU_HAVE_ALREADY_INITIALIZE_THE_LOGGER";
            break;
        case LOGGER_INFRASTRUCTURE_RESULT::FAILURE_CALLBACK_LOGGER_IS_NULL:
            os << "FAILURE_CALLBACK_LOGGER_IS_NULL";
            break;
        case LOGGER_INFRASTRUCTURE_RESULT::FAILURE_CALLBACK_IS_NULL_PLEASE_INITIALIZE_FIRST_THE_CALLBACK_BEFORE_TO_SET_MIN_LOGGER_LEVEL:
            os << "FAILURE_CALLBACK_IS_NULL_PLEASE_INITIALIZE_FIRST_THE_CALLBACK_BEFORE_TO_SET_MIN_LOGGER_LEVEL";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const ApiResult& result)
{
    switch (result) 
    {
        case ApiResult::WTF:
            os << "WTF";
            break;
        case ApiResult::SUCCESS:
            os << "SUCCESS";
            break;
        case ApiResult::FAILURE:
            os << "FAILURE";
            break;
        case ApiResult::FAILURE_ELEMENT_NOT_FOUND:
            os << "FAILURE_ELEMENT_NOT_FOUND";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}