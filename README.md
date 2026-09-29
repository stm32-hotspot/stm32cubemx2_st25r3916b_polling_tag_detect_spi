# __Example: *st25r3916b_polling_tag_detect_spi*__

How to use ST25R3916B part API.

It illustrates it by polling NFC tags over SPI and displaying tag detection events on a terminal.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

__Step 1__: Initializes ST25R3916B communication and RFAL stack

__Step 2__: Starts polling for NFC tags

__Step 3__: Detects tag presence, reports it on terminal, and restarts polling

__End of example__: It is an endless example that loops infinitely on steps 2 and 3

You can follow these execution steps in the terminal logs:

```text
[INFO] Step 1: ST25R3916B and RFAL init completed
[INFO] Step 2: Polling field started
[INFO] Step 3: NFC tag detected
```


## __2. Example configuration__

This example demonstrates the following components:

- Part st25r3916b.c/.h
- RFAL middleware integration

In this example, the ST25R3916B component is configured through SPI IO operations.
Once SPI and board-specific NFC settings are initialized, the polling loop can detect nearby NFC tags.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

This section describes the hardware setup principles that apply to any board.

### __3.2. Specific board setups__

<details>
<summary>On STM32C5 series.</summary>
  <summary>On board NUCLEO-C562RE with NFC08A1 expansion board.</summary>

  Ensure the NFC08A1 expansion board is mounted correctly on the NUCLEO-C562RE board,
and that SPI wiring and power are provided by the Arduino connector.

</details>

## __4. Software setup__

To create a functional project, complete the following steps:
- Select the appropriate IoC2 file based on the combination of NUCLEO and NFC expansion boards. For example, use c562re_nfc08a1_st25r3916b_polling_tag_detect_spi.ioc2.
- Open the IoC2 file with STM32CubeMX2.
- Select the preferred toolchain and generate the source code.
- Copy the analogConfigTbl_NFC08A1.c, common.h, demo.h, demo_ce.c, demo_ce.h, demo_polling.c, example.c, example.h, logger.c, main.c, main.h, and nfc_conf.c files into the project folder of the generated code.
- Open the Integrated Development Environment (IDE), add all copied .c and .h files to the project.
- Increase the Stack size to 0x1000
- Add the USE_TRACE=1 to the global variables of the project.
- Compile the project.

## __5. Troubleshooting__

No specific debug tips.


## __6. See Also__

More information about ST25R3916B part driver can be found in the [ST25R3916B documentation](https://www.st.com/en/nfc/st25r3916b.html)

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone.html).


## __7. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
