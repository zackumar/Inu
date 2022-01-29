#ifndef KINEMATICS_H
#define KINEMATICS_H

/**
 * @brief Calculate the inverse kinematics of single leg
 *
 * @param leg_angles
 * @param leg_coordinates
 * @return Pointer of leg angles in degrees
 */
int* single_leg_ik(int leg_angles[], int leg_coordinates[]);

#endif