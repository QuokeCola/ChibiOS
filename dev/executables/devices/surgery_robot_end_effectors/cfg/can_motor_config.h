//
// Created by 钱晨 on 10/29/21.
//

#ifndef META_INFANTRY_CANBUS_MOTOR_CFG_H
#define META_INFANTRY_CANBUS_MOTOR_CFG_H

#include "can_motor_feedback.h"

class CANMotorCFG {
public:
    enum motor_id_t {
        MOTOR_1,
        MOTOR_2,
        MOTOR_COUNT
    };
    static CANMotorBase CANMotorProfile[MOTOR_COUNT];
};

#endif //META_INFANTRY_CANBUS_MOTOR_CFG_H