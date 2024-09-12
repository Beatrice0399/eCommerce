#include "main.h"

redisReply* GetFirstEntryElements(redisReply *reply){
    return reply->element[0]->element[1]->element[0]->element[1];
}