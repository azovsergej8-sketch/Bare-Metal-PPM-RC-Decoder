# Bare-Metal-PPM-RC-Decoder

Low-latency PPM signal decoder and channel processor for STM32C0 microcontrollers. Developed in C++ with direct register access — no HAL, no middleware. Designed for RC receiver applications
## 🚀 Key Technical Features

### 1. Hardware-Level Signal Capture
* **Non-Blocking PPM Decoding:** Implemented a bare-metal (CMSIS) input capture engine using **Timer 1 (TIM1)** to detect signal edges and measure precise pulse widths.
* **DMA Pipeline (Direct Memory Access):** Configured a circular DMA channel to offload capture data directly to RAM (`raw_timings`) without CPU intervention, preventing interrupted execution loops.
* **Low-Level Peripheral Control:** Programmed alternative pin functions (`PA8`), internal clock trees, and register maps directly (`TIM1->CCMR1`, `DMA->CCR`), bypassing overhead-heavy vendor abstraction libraries (HAL/LL).

### 2. Digital Signal Pipeline & Processing
* **Multi-Channel FSM Processing:** Developed a custom parser to isolate the multi-channel frame using hardware synchronization pause detection (> 2500 µs).
* **Dynamic Exponential Filtering:** Implemented a lightweight digital smoothing filter with channel-specific coefficients ($\alpha = 0.1 \dots 0.4$) to suppress RF jitter and signal noise on flight-critical channels (Throttle, Roll, Pitch, Yaw).
* **Linear Calibration & Mapping:** Designed a normalization module that maps raw hardware timings ($1000 \mu s \dots 2000 \mu s$) into accurate floating-point ranges (`0.0f` to `1.0f` for throttle, `-1.0f` to `1.0f` for control surfaces) suitable for standard PID loops.

### 3. FailSafe & System Robustness
* **Signal Timeout Monitoring:** Integrated an ARM **SysTick** hardware timer to track real-time link health.
* **Automated Emergency Protocol:** Implemented a software FailSafe state-machine that triggers if no valid PPM frame arrives within 500 ms, automatically overriding outputs and forcing control values to a safe neutral/zero state to prevent flyaways.

## 🛠 Hardware Configuration & Environment
| Component / Interface | Hardware Peripherals | Purpose |
| :--- | :--- | :--- |
| **RC Receiver (PPM)** | PA8 (TIM1_CH1 / Input Capture) | Captures 8-channel multiplexed RC remote data |
| **DMA Controller** | DMA Channel 1 (Circular Mode) | Streams pulse measurements to memory without CPU overhead |
| **System Timer** | Core SysTick Exception | Provides precise millisecond tracking for timeout detection |

## 📂 Project Structure
* `main.cpp` — Main control loop, clock configuration, and flight controller execution emulation.
* `PPM_Decoder.h` / `PPM_Decoder.cpp` — Bare-metal peripheral initialization and FSM-driven pulse boundary analysis.
* `SignalFilter.h` / `SignalFilter.cpp` — Software-based exponential signal smoothing and outlier rejection.
* `ChannelMapper.h` / `ChannelMapper.cpp` — Subsystem calibration and execution data conversion into control constraints.
* `Time.h` / `Time.cpp` — Custom SysTick ISR handler and system uptime measurement APIs.

## 📋 How to Run & Verify
1. **Toolchain & Setup:** Open the workspace using **VS Code** with the **ARM GCC Toolchain** or import it directly into **STM32CubeIDE**.
2. **Compilation:** Build the project using the native Makefile or the IDE build system targeting any STM32 core (configured for `STM32C0` register layouts).
3. **Logic Verification:** Use a logic analyzer on pin `PA8` or check the `result` float array using your debugger's Watch Window to inspect active runtime signal streams.

---
**Author:** Sergey Azov,
Candidate for Intern Embedded / CPU Verification role.
