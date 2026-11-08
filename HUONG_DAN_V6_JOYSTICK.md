# Robot Arm V6 - Joystick SW1 without Serial configuration

Changes from V5: preconfigure CH0..CH4 min/max and reference angles in firmware; SW1 (GPIO25) toggles joystick; SW2 speed, SW3 voice preserved. ESP32 still sends ANG on updates and supports Web, Serial, Python/PyBullet. No SETALL/JLIMITALL required during normal boot after configuring V6 correctly.

## One-time mandatory configuration BEFORE uploading
At top of .ino find:
```
const bool JOY_PRESET_VERIFIED = false;
const float JOY_PRESET_MIN[5]  = { 0, 0, 0, 0, 0 };
const float JOY_PRESET_MAX[5]  = { 180, 180, 180, 180, 180 };
const float JOY_PRESET_REF[5]  = { 90, 90, 90, 90, 90 };
```
These are PLACEHOLDERS, not safe limits. Replace all 15 values with verified data from your arm. Only then change `JOY_PRESET_VERIFIED` to `true`. Otherwise SW1 will safely refuse to enable joystick.

## Start
1. Verify reference angles correspond to the actual physical pose and linkage constraints; do not assume motor position at boot (MG996R has no external angle telemetry). Clear space around robot.
2. Turn on ESP32 and external regulated servo supply. No PWM positioning command is sent at boot.
3. Center all joysticks; press SW1 once. Joystick ON, then JOYSTICK READY after neutral check. SW2 chooses SLOW/FAST; SW3 toggles Voice (when Python connected).
4. First joystick motion commands a servo toward the preset reference; if the mechanical pose is different, this can cause a sudden jump. Stop immediately if unexpected motion occurs.
5. `JLIMITALL`, `SET`, `SETALL` and other Serial commands are kept for manual service, but are no longer required to enable joystick after valid firmware preset.

IMPORTANT: Hardware lacks measured joint angles, so joystick reference uses the *assumed* starting position. The reference limits CH0/CH1 must reflect safe combined linkage motion; individual bounds alone do not prove collision-free movement. `SAVE 0` in existing firmware is not used as an automatic persistent startup preset.
