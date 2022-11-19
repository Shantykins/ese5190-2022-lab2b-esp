### TODO:

Create a REPL to let you read and write RP2040 registers from a console. You should be able to:
- select any 32-bit address to read/write (even if not a valid RP2020 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask

For reading and writing through console using register access, we have taken `GPIO0`, the offset for which is `0x004` which is added to the `IO_BANK0_BASE`.

The code for reading/writing any 32-bit value to this address and reading/writing using any of the atomic bit-setting aliases and a 32-bit mask has been combined and attached.

Here, `GPIO0` is being read through register access and then the user input is taken. The value input by the user is then masked with the value read on the register. The register is updated (written) to the new masked value and printed on the console.
