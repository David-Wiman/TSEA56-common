#ifndef RASPICOMMON_H
#define RASPICOMMON_H

#include <string>

extern "C" {
    #include "i2c_common.h"
}

/* Drive modes for the car:
 * - manual: steer direct from user interface
 * - auto_nominal: use semi-auto or auto instructions to drive
 * - auto_critical: same as above, but in an intersection or when image
 *   processing gave unreliable data. */
namespace regulation_mode {
    enum DriveMode {
        manual = REGULATION_MODE_MANUAL,
        auto_nominal = REGULATION_MODE_AUTO_FORWARD,
        auto_critical = REGULATION_MODE_AUTO_TURN
    };
}

namespace instruction {
    enum InstructionNumber {
        left = 0, forward = 1, right = 2, stop = 3
    };
}

/* The simple instructions got from user interface in semi-auto mode
 * and generated from drive missions in auto mode. */
typedef struct DriveInstruction {
    enum instruction::InstructionNumber number = instruction::stop;
    std::string id = "none";
} drive_instruction_t;

/* The references generated by ControlModule */
typedef struct ReferenceStruct {
    int speed;
    int angle;
    enum regulation_mode::DriveMode regulation_mode;
} reference_t;

/* The data produced by ImageProcessingModule */
typedef struct image_proc_t {
    int status_code = 0;
    int lateral_position = 0;
    int stop_distance = 0;
    int angle_left = 0;
    int angle_right = 0;
} image_proc_t;

/* The data produced by sensor module */
typedef struct sensor_data_type {
    int obstacle_distance = 0;
    int driving_distance = 0;
    int speed = 0;
} sensor_data_t;

/* The data produced by steering module */
typedef struct steer_data_type {
    int gas = 0;
    int steer_angle = 0;
} steer_data_t;

#endif  // RASPICOMMON_H
