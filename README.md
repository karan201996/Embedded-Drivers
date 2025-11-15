# EK-TM4C123GXL DC-DC Converter Controller

This repository contains a bare-metal firmware project for the Texas Instruments EK-TM4C123GXL LaunchPad. The code configures the microcontroller as a digital controller for a synchronous buck (DC-DC) converter by generating a high-frequency PWM signal, sampling the scaled output voltage, and closing the loop with a discrete PI compensator.

## Project highlights

- **80&nbsp;MHz system clock** configuration from the main crystal using the PLL.
- **200&nbsp;kHz PWM carrier** generated on `PB6` (`M0PWM0`) with hardware duty-cycle updates.
- **Analog feedback** read from ADC0 sequencer 3 (default channel AIN0 on `PE3`).
- **Timer-driven control loop** executing at 40&nbsp;kHz with tunable PI gains and duty clamps.
- **Portable build system** powered by `make` and the `arm-none-eabi` GCC toolchain.

## Repository layout

```
├── Makefile              # Build rules for GCC + OpenOCD
├── include/              # Public headers
│   ├── adc.h             # ADC abstraction
│   ├── control_loop.h    # PI controller interface
│   ├── pwm.h             # PWM driver interface
│   ├── system.h          # Clock and peripheral setup
│   └── tm4c123gh6pm.h    # Minimal register map for the MCU
├── linker/
│   └── tm4c123g.ld       # Linker script for EK-TM4C123GXL
└── src/
    ├── adc.c             # ADC driver implementation
    ├── control_loop.c    # Timer ISR and PI control logic
    ├── main.c            # Application entry point
    ├── pwm.c             # PWM configuration helpers
    ├── startup_gcc.c     # Vector table and reset handler
    └── system.c          # Clock tree and peripheral gates
```

## Building the firmware

1. Install the GNU Arm Embedded toolchain (`arm-none-eabi-gcc`) and OpenOCD.
2. From the repository root, run:

   ```bash
   make
   ```

   The compiled artifacts are placed in `build/`, including an ELF for debugging and a binary image for flashing.

## Flashing to the LaunchPad

Connect the EK-TM4C123GXL over USB and invoke:

```bash
make flash
```

This uses the OpenOCD board configuration (`board/ek-tm4c123gxl.cfg`) to program, verify, and reset the device.

## Control loop tuning

The default PI parameters target a 12&nbsp;V output scaled to a 3.3&nbsp;V ADC range. Adjust the `control_loop_config_t` structure in `src/main.c` to match your converter's power stage and feedback network:

- `target_voltage`: Desired sensed voltage (volts at the ADC pin).
- `kp` / `ki`: Proportional and integral gains for the digital compensator.
- `sample_rate_hz`: Control loop update rate (must divide the system clock).
- `min_duty` / `max_duty`: Hardware duty clamp to prevent over/under-drive.

Further calibration (e.g., slope compensation, current limiting) can be added inside `ControlLoop_TimerTick`.

## License

This project is provided as-is for educational and prototyping use. Review the EK-TM4C123GXL datasheet and safety requirements before operating high-power hardware.
